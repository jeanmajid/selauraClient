#ifdef _WIN32
#include <Windows.h>

BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID) {
    return TRUE;
}
#endif

#include <api/imports.hpp>
#include <print>
#include "runtime.hpp"

SELAURA_API void SelauraRuntimeInit(Selaura::RuntimeContext* ctx, std::function<void(Selaura::Runtime*)> load_mods) {
    Selaura::RuntimeInstance = std::make_unique<Selaura::Runtime>(*ctx);
    Selaura::RuntimeInstance->start();

    load_mods(Selaura::RuntimeInstance.get());
}