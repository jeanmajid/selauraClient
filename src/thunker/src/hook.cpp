#include "thunker/hook.hpp"

bool THUNKER_API thunker::hook::attach() {
    std::lock_guard lock(mtx);

    m_trampoline = thunker::create_trampoline(m_target, m_patch_size);

    thunker::write_jump(m_target, m_detour);

    m_patched = true;
    return true;
}

bool THUNKER_API thunker::hook::detach() {
    std::lock_guard lock(mtx);

    std::memcpy(m_target, m_trampoline, m_patch_size);
    std::free(m_trampoline);
    m_trampoline = nullptr;

    m_patched = false;
    return true;
}