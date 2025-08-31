#include "handle.hpp"
#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
#endif

namespace selaura {
    std::shared_ptr<handle> get_handle(std::string_view name) {
        void* ptr;
        std::span<std::byte> bytes;

#ifdef SELAURA_WINDOWS
        auto win_handle = GetModuleHandleA(name.data());
        ptr = reinterpret_cast<void*>(win_handle);

        MODULEINFO info;
        if (!GetModuleInformation(GetCurrentProcess(), win_handle, &info, sizeof(info))) std::terminate();

        bytes = {
            reinterpret_cast<std::byte*>(info.lpBaseOfDll),
            info.SizeOfImage
        };
#endif

        return std::make_shared<handle>(ptr, bytes);
    }
};