#pragma once
#include "client.hpp"

alignas (selaura::client) char selaura_buffer[sizeof(selaura::client)];

namespace selaura {
    client& get() {
        return *std::launder(reinterpret_cast<client*>(selaura_buffer));
    }

    client::client() {
        auto start = std::chrono::high_resolution_clock::now();

        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto logger = std::make_shared<spdlog::logger>("client_logger", sink);
        spdlog::set_default_logger(logger);

        spdlog::set_pattern("[%T] [client/%^%l%$] %v");
        spdlog::flush_on(spdlog::level::info);

        this->get<scanner>().init();

        if (this->get<scanner>().invalid_signatures) {
            this->m_running = false;
            return;
        }


        spdlog::info("d: {}", selaura::signature_runtime_value<&IMinecraftGame::update>::value);

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        spdlog::info("Injected [{}ms]", ms);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        this->m_running = false;
    }

    client::~client() {

    }
};