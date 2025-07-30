#pragma once
#include <tuple>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>

#include "impl/disable_command.hpp"
#include "impl/enable_command.hpp"

namespace selaura {
    struct command_handler {
        using default_commands_t = std::tuple<
            enable_command,
            disable_command
        >;

        inline std::string execute(std::string_view command_str) {
            std::istringstream stream(std::string{command_str});
            std::string verb;
            stream >> verb;

            if (verb.empty())
                return "§cNo command entered.";

            std::vector<std::string> args;
            for (std::string arg; stream >> arg;)
                args.emplace_back(std::move(arg));

            return std::apply([&](auto&... cmds) -> std::string {
                std::string result = "§cUnknown command: " + verb;
                (..., (
                    [&] {
                        using T = std::decay_t<decltype(cmds)>;
                        constexpr auto name = std::string_view{ command_traits<T>::command.c_str() };

                        if (verb == name)
                            result = cmds.execute(args);
                    }()
                ));
                return result;
            }, default_commands);
        }

    private:
        default_commands_t default_commands;
    };
};