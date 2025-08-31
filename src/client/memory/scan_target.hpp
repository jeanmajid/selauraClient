#pragma once
#include <cstdint>

namespace selaura {
    struct game_version {
        int major;
        int minor;
        int patch;

        constexpr bool operator==(const game_version&) const = default;
    };

    enum class scanner_type : std::uint8_t {
        signature,
        offset
    };

    template <auto fn, scanner_type type>
    struct scan_target {};

    template <typename T>
    struct scan_target_traits;

    template <auto fn, scanner_type type>
    struct scan_target_traits<scan_target<fn, type>> {
        static constexpr auto value = fn;
    };

    template <auto fn>
    struct signature_runtime_value {
        inline static std::uintptr_t value = 0;
    };
}
