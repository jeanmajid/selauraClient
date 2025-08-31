#pragma once
#include "../../scan_target.hpp"
#include <libhat/signature.hpp>
#include <spdlog/spdlog.h>

#include "../../mc/game/IMinecraftGame.hpp"

namespace selaura {
    template <>
    struct scan_target<&IMinecraftGame::update, scanner_type::signature> {
        constexpr static hat::fixed_string signature = "48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 F8 F6";
        constexpr static auto value = hat::compile_signature<signature>();
    };

    using signature_types = std::tuple<
        scan_target<&IMinecraftGame::update, scanner_type::signature>
    >;
};