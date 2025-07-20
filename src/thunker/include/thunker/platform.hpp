#pragma once
#include "common.hpp"

#if THUNKER_WINDOWS && THUNKER_ARCH_X64
#include <Windows.h>
#include <Psapi.h>
#endif

namespace thunker {
    inline bool make_memory_writable(void* addr, std::size_t size);
    inline std::uint8_t* create_trampoline(void* target, std::size_t size);
    inline void write_jump(void* src, void* dst);
};