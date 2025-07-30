#include "disable_command.hpp"

#include <format>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "../../client.hpp"

namespace selaura {
    const std::string disable_command::execute(std::vector<std::string> arguments) {
        if (arguments.empty())
            return "§cIncorrect syntax: .disable [module_name ...]";

        auto& feature_manager = selaura::get()->get<selaura::feature_manager>();
        std::vector<std::string> disabled_modules;

        feature_manager.for_each([&]<typename T>(std::shared_ptr<T>& f) {
            const std::string_view name = selaura::feature_traits<T>::name;

            auto it = std::ranges::find_if(arguments, [&](const std::string& arg) {
                return arg.size() == name.size() &&
                    std::equal(arg.begin(), arg.end(), name.begin(), name.end(),
                        [](char a, char b) {
                            return std::tolower(static_cast<unsigned char>(a)) ==
                                   std::tolower(static_cast<unsigned char>(b));
                        });
            });

            if (it != arguments.end()) {
                f->set_enabled(false);
                disabled_modules.emplace_back(name);
            }
        });

        if (disabled_modules.empty()) {
            return "§cNo matching modules found to disable.";
        }

        std::string joined;
        for (size_t i = 0; i < disabled_modules.size(); ++i) {
            joined += disabled_modules[i];
            if (i + 1 < disabled_modules.size()) {
                joined += ", ";
            }
        }

        return std::format("§aSuccessfully disabled modules: {}", joined);
    }
}
