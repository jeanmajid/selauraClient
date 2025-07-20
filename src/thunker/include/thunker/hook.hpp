#pragma once
#include <cstddef>
#include <cstdint>
#include <mutex>

#include "common.hpp"
#include "platform.hpp"

namespace thunker {
    struct THUNKER_API hook {
        [[nodiscard]] bool patched() const {
            return m_patched;
        };

        bool attach();
        bool detach();
    private:
        std::uint8_t* m_target{};
        std::uint8_t* m_detour{};
        std::uint8_t* m_trampoline{};
        std::size_t m_patch_size{};

        bool m_patched{};
        std::mutex mtx{};
    };
};