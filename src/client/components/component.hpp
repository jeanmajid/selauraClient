#pragma once
#include <atomic>
#include <memory>
#include <tuple>

#include "client.hpp"
#include "../memory/scanner.hpp"

namespace selaura {
    struct client;

    struct component : std::enable_shared_from_this<component> {
        virtual ~component() = default;
        std::atomic<bool> m_running = true;
        std::weak_ptr<client> owner;
    };

    using components_t = std::tuple<selaura::scanner>;
};