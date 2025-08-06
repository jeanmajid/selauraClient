#pragma once
#include "../../scan_target.hpp"
#include <libhat/signature.hpp>

void hi();

namespace selaura {
    template <>
    struct scan_target<&hi, scanner_type::signature> {
        constexpr static auto value = hat::compile_signature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 8B F1">();
    };

    using signature_types = std::tuple<
        scan_target<&hi, scanner_type::signature>
    >;
};