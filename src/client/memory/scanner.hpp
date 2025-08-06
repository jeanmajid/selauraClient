#pragma once
#include <future>
#include <print>
#include <thread>
#include "scan_target.hpp"
#include "libhat/scanner.hpp"
#include "patterns/win/patterns.hpp"

namespace selaura {
    struct scanner {
        template <typename T>
        void resolve_signature() {
            auto result = hat::find_pattern(T::value, ".text");

            constexpr auto fn = scan_target_traits<T>::value;
            signature_runtime_value<fn>::value = reinterpret_cast<std::uintptr_t>(result.get());
        }

        template <typename... Ts>
        void resolve_all_async(std::tuple<Ts...>&) {
            std::vector<std::future<void>> futures;

            (futures.emplace_back(std::async(std::launch::async, [this]() {
                resolve_signature<Ts>();
            })), ...);

            for (auto& fut : futures) fut.get();
        }

        void start_scanning_thread();
        void kill_scanning_thread();
        void safe_kill();
    private:
        std::thread m_scanning_thread;
        signature_types signatures{};
    };
};