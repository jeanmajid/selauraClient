#pragma once
#include "../../scan_target.hpp"
#include <libhat/signature.hpp>

void hi();

namespace selaura {
    template <>
    struct scan_target<&hi, scanner_type::signature> { // MinecraftGame::update
        constexpr static hat::fixed_string signature = "? ? ? FC ? ? ? A9 ? ? ? 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D1 ? ? ? D5 F3 03 00 AA ? ? ? F9 ? ? ? F8 ? ? ? F9 ? ? ? 95";
        constexpr static auto value = hat::compile_signature<signature>();
    };

    using signature_types = std::tuple<
        scan_target<&hi, scanner_type::signature>
    >;
};