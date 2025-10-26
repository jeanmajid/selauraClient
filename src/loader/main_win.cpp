#include "main_win.hpp"

#include <filesystem>
#include <print>
#include <thread>

#include <winrt/windows.applicationmodel.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.storage.h>

#include "runtime.hpp"

std::thread::id mc_thread_id;
HANDLE mc_thread_handle = NULL;

DWORD WINAPI SelauraLoaderProc() {
    AllocConsole();

    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Selaura Client Console");

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    std::println("[Selaura Plugin Loader] Thread ID: {}, Thread Handle: {}", mc_thread_id, mc_thread_handle);
    std::println("[Selaura Plugin Loader] Press Numpad1 to End");

    SuspendThread(mc_thread_handle);

    auto* ctx = new selaura::runtime_context;
    ctx->thread_id = mc_thread_id;

    const winrt::Windows::ApplicationModel::Package pkg = winrt::Windows::ApplicationModel::Package::Current();
    ctx->version_major = pkg.Id().Version().Major;
    ctx->version_minor = pkg.Id().Version().Minor;
    ctx->version_build = pkg.Id().Version().Build;
    ctx->version_revision = pkg.Id().Version().Revision;

    selaura::runtime_instance = std::make_shared<selaura::runtime>(*ctx);
    selaura::runtime_instance->start();

    ResumeThread(mc_thread_handle);

    auto winrt_folder = winrt::Windows::Storage::ApplicationData::Current().RoamingFolder();
    std::filesystem::path mods_folder = std::filesystem::path(winrt::to_string(winrt_folder.Path())) / "Selaura" / "mods";

    if (!std::filesystem::exists(mods_folder)) {
        std::filesystem::create_directory(mods_folder);
    }

    int plugins_loaded = 0;

    using init_fn = void(*)(selaura::runtime*);
    std::vector<init_fn> init_fn_list = {};
    for (const auto& entry : std::filesystem::directory_iterator(mods_folder)) {
        if (!entry.is_regular_file())
            continue;

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
        fn(selaura::runtime_instance.get());
    }

    while (true) {
        Sleep(10);

        if (GetAsyncKeyState(VK_NUMPAD1) || selaura::runtime_instance->unload) break;
    }

    fclose(fp);
    FreeConsole();

    ExitProcess(0);
    return 0;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) {

    if (fdwReason == DLL_PROCESS_ATTACH) {
        mc_thread_id = std::this_thread::get_id();
        mc_thread_handle = OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());

        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)SelauraLoaderProc, nullptr, 0, nullptr);
    }

    return TRUE;
}