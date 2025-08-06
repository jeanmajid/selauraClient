#pragma once

#ifdef SELAURA_WINDOWS
#include <chrono>
#include <thread>
#include <print>
#include <Windows.h>

#include "selaura.hpp"

DWORD WINAPI start(LPVOID lpParam) {
//#ifdef _DEBUG
    AllocConsole();

    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Selaura Client Console");

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);
//#endif

    auto client = std::make_shared<selaura::client>();
    client->init();

    while (client->m_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    client->~client();
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)start, hModule, 0, nullptr);
    }

    else if (dwReason == DLL_PROCESS_DETACH) std::println("Ejected");
    return TRUE;
}
#endif