#pragma once
#include <thread>

#include <spdlog/spdlog.h>
#include <safetyhook.hpp>

#include "../api/stt.hpp"
#include "../memory/scan_target.hpp"

namespace selaura {

    /* the recode plan:
     struct selaura::patch<&IMinecraftGame::update> {
        static void detour() {
            spdlog::info("update called");
        };
     };
     */

};