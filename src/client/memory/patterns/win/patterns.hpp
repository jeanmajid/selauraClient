#pragma once
#include "../../scan_target.hpp"
#include <libhat/signature.hpp>

void hi();

namespace selaura {
    template <>
    struct scan_target<&hi, scanner_type::signature> {
        constexpr static auto value = hat::compile_signature<"48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA">();
    };

    using signature_types = std::tuple<
        scan_target<&hi, scanner_type::signature>
    >;
};