#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <libhat/fixed_string.hpp>

namespace selaura {
    template <typename T>
    struct command_traits {
        static constexpr auto command = hat::fixed_string { "unknown" };
    };

    template <typename T>
    struct command {
        virtual ~command() = default;
        using details = command_traits<T>;

        virtual const std::string execute(std::vector<std::string> arguments) = 0;
    };
};