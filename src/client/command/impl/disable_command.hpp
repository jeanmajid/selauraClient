#pragma once
#include "../command.hpp"

namespace selaura {
    struct disable_command;

    template <>
    struct command_traits<disable_command> {
        static constexpr auto command = hat::fixed_string{ "disable" };
    };

    struct disable_command : command<disable_command> {
        virtual const std::string execute(std::vector<std::string> arguments) override;
    };
};