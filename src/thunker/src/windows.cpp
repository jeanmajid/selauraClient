#pragma once
#include "thunker/platform.hpp"

#if THUNKER_WINDOWS && THUNKER_ARCH_X64
inline bool thunker::make_memory_writable(void* addr, std::size_t size) {
    DWORD oldProtect;
    BOOL result = VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    return result != 0;
}

inline std::uint8_t* thunker::create_trampoline(void* target, std::size_t size) {
    std::uint8_t* trampoline = (std::uint8_t*)VirtualAlloc(nullptr, size + 14,
        MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!trampoline) return nullptr;

    std::memcpy(trampoline, target, size);

    // Write jump back to target+size at trampoline+size
    std::uint8_t* jmp_addr = trampoline + size;
    std::uint8_t* ret_addr = (std::uint8_t*)target + size;

    jmp_addr[0] = 0x48;
    jmp_addr[1] = 0xB8;          // mov rax, imm64
    *reinterpret_cast<std::uint64_t*>(jmp_addr + 2) = (std::uint64_t)ret_addr;
    jmp_addr[10] = 0xFF;         // jmp rax
    jmp_addr[11] = 0xE0;

    return trampoline;
}

inline void thunker::write_jump(void* src, void* dst) {
    std::uint8_t* p = reinterpret_cast<std::uint8_t*>(src);

    // mov rax, dst
    p[0] = 0x48;
    p[1] = 0xB8;
    *reinterpret_cast<std::uint64_t*>(p + 2) = reinterpret_cast<std::uint64_t>(dst);

    // jmp rax
    p[10] = 0xFF;
    p[11] = 0xE0;

    p[12] = 0x90;
    p[13] = 0x90;
}
#endif