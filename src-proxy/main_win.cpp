#include "main_win.hpp"

#include <filesystem>
#include <functional>
#include <print>
#include <thread>
#include <shlobj_core.h>

#include <winrt/windows.applicationmodel.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.storage.h>

#include <runtime.hpp>

std::thread::id mc_thread_id;
HANDLE mc_thread_handle = nullptr;

DWORD WINAPI SelauraRuntimeLoaderProc() {
    AllocConsole();

    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Selaura Client Console");

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    std::println("[Selaura Runtime Loader] Thread ID: {}, Thread Handle: {}", mc_thread_id, mc_thread_handle);
    std::println("[Selaura Runtime Loader] Press Numpad1 to End");

    PWSTR appDataPath = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &appDataPath))) {
        throw std::runtime_error("Failed to get AppData path");
    }

    std::filesystem::path folder = appDataPath;
    CoTaskMemFree(appDataPath);

    folder /= R"(Minecraft Bedrock\Users\Shared\games\com.mojang\Selaura)";


    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            SetConsoleMode(hOut, mode | 0x0004);
        }
    }

    const auto runtime_path = folder / "selaura_runtime.dll";
    if (!std::filesystem::exists(runtime_path)) {
        std::println("\x1b[91m[Selaura Runtime Loader] ERROR: '{}' not found. The runtime is required.\x1b[0m",
                     runtime_path.string());
    } else {
        std::function<void(selaura::runtime*)> load_mods = [=](selaura::runtime* rt) {
            // To load mods we need LoadLibrary, and other Windows-specific
            // functions, and this will be called in the runtime. However,
            // due to the goal of cross-platform, the function must be
            // created here, and then further passed to the runtime as an
            // argument in the Init function.
            std::filesystem::path mods_folder = folder/ "mods";

            if (!std::filesystem::exists(mods_folder)) {
                std::filesystem::create_directory(mods_folder);
                return;
            }

            int plugins_loaded = 0;

            using init_fn = void(*)(selaura::runtime*);
            std::vector<init_fn> init_fn_list = {};

            for (const auto& entry : std::filesystem::directory_iterator(mods_folder)) {
                if (!entry.is_regular_file()) continue;
                const auto& path = entry.path();
                if (path.extension() == ".dll") {
                    HMODULE mod = LoadLibraryExW(entry.path().c_str(), nullptr, DONT_RESOLVE_DLL_REFERENCES);
                    if (mod) {
                        FreeLibrary(mod);
                        mod = LoadLibraryW(entry.path().c_str());
                    }

                    auto init = reinterpret_cast<init_fn>(GetProcAddress(mod, "SelauraPluginInit"));
                    init_fn_list.push_back(init);

                    if (mod) {
                        plugins_loaded++;
                        std::println("[Selaura Plugin Loader] Loaded: {}", path.filename().string());
                    } else {
                        std::println("[Selaura Plugin Loader] Failed to load: {} (Error {})",
                                     path.filename().string(), GetLastError());
                    }
                }
            }

            std::println("[Selaura Plugin Loader] Loaded {} plugin(s).", plugins_loaded);

            for (auto fn : init_fn_list) {
                fn(rt);
            }
        };

        SuspendThread(mc_thread_handle);

        auto* ctx = new selaura::runtime_context;
        ctx->thread_id = mc_thread_id;

        DWORD handle = 0;
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(nullptr, path, MAX_PATH);

        DWORD size = GetFileVersionInfoSizeW(path, &handle);
        if (size) {
            std::string buffer(size, '\0');
            if (GetFileVersionInfoW(path, handle, size, buffer.data())) {
                VS_FIXEDFILEINFO* file_info = nullptr;
                UINT len = 0;
                if (VerQueryValueW(buffer.data(), L"\\", reinterpret_cast<LPVOID*>(&file_info), &len) && file_info) {
                    ctx->version_major = HIWORD(file_info->dwFileVersionMS);
                    ctx->version_minor = LOWORD(file_info->dwFileVersionMS);
                    ctx->version_build = HIWORD(file_info->dwFileVersionLS);
                    ctx->version_revision = LOWORD(file_info->dwFileVersionLS);
                }
            }
        }

        HMODULE mod = LoadLibraryExW((folder / "selaura_runtime.dll").c_str(), nullptr, 0);
        using runtime_init_fn = void(*)(selaura::runtime_context*, std::function<void(selaura::runtime*)>);
        auto runtime_init = reinterpret_cast<runtime_init_fn>(GetProcAddress(mod, "SelauraRuntimeInit"));
        runtime_init(ctx, load_mods);

        ResumeThread(mc_thread_handle);
    }

    while (true) {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD1)) break;
    }

    fclose(fp);
    FreeConsole();

    ExitProcess(0);

    return 0;
}

BOOL APIENTRY DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        proxy::init_runtime();
        mc_thread_id = std::this_thread::get_id();
        mc_thread_handle = OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());

        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)SelauraRuntimeLoaderProc, nullptr, 0, nullptr);
    }

    return TRUE;
}
