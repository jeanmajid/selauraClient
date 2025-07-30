#pragma once
#include <exception>
#include <memory>
#include <tuple>
#include <print>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "event/event_manager.hpp"
#include "feature/feature_manager.hpp"
#include "command/command_handler.hpp"
#include "memory/signatures.hpp"

#include "memory/sdk/game/MinecraftGame.hpp"

namespace selaura {
    template <typename T, typename... Ts>
    concept one_of = (std::same_as<T, Ts> || ...);

    template <typename... subsystems_t>
    struct client_base : std::enable_shared_from_this<client_base<subsystems_t...>> {
        using subsystems_tuple_t = std::tuple<subsystems_t...>;

        client_base() : subsystems{} {}

        template <typename T>
        requires one_of<T, subsystems_t...>
        constexpr T& get() {
            return std::get<T>(subsystems);
        }

    private:
        subsystems_tuple_t subsystems;
    };


    struct client : public client_base<selaura::event_manager, selaura::feature_manager, selaura::command_handler> {
        void init();
        void unload();
    };

    inline std::shared_ptr<client>& get() {
        static std::shared_ptr<client> instance = std::make_shared<client>();
        return instance;
    }

    inline MinecraftGame* minecraftGame;
};