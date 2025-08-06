#pragma once
#include <atomic>
#include <chrono>
#include <memory>
#include <print>
#include <thread>
#include <tuple>

#include "memory/scanner.hpp"

namespace selaura {
    using client_components = std::tuple<scanner>;

    struct client : std::enable_shared_from_this<client> {
        ~client();
        void init();

        template <typename T>
        constexpr auto& get() {
            return std::get<T>(m_components);
        }

        std::atomic<bool> m_running = true;
    private:
        client_components m_components{};
    };

    std::shared_ptr<client>& get();
};