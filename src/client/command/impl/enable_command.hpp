#pragma once
#include "../command.hpp"

namespace selaura {
    struct enable_command;

    template <>
    struct command_traits<enable_command> {
        static constexpr auto command = hat::fixed_string{ "enable" };
    };

    struct enable_command : command<enable_command> {
        virtual const std::string execute(std::vector<std::string> arguments) override;
    };
};