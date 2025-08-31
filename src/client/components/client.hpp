#pragma once
#include "component.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace selaura {
    struct client {
        client();
        ~client();

        template <typename T>
        constexpr auto& get() {
            return std::get<T>(m_components);
        }

        std::atomic<bool> m_running = true;
    private:
        selaura::components_t m_components{};
    };

    client& get();

    template <typename T>
    constexpr auto get() {
        return selaura::get().get<T>();
    }
};

extern char selaura_buffer[sizeof(selaura::client)];