#pragma once
#include <future>
#include <print>
#include <thread>

#include <libhat/scanner.hpp>
#include <spdlog/spdlog.h>

#include "handle.hpp"
#include "scan_target.hpp"

#ifdef SELAURA_WINDOWS
#include "patterns/win/patterns.hpp"
#elif SELAURA_LINUX
#elif SELAURA_ANDROID
#include "patterns/android/patterns.hpp"
#endif

template <typename T>
constexpr std::string_view extract_type_name(std::string_view full) {
    auto start = full.find('<') + 1;
    auto end = full.rfind('>');
    return full.substr(start, end - start);
}

template <typename T>
constexpr std::string_view type_name() {
#if defined(__clang__) || defined(__GNUC__)
    constexpr std::string_view func = __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
    constexpr std::string_view func = __FUNCSIG__;
#else
    return "unknown";
#endif
    return extract_type_name<T>(func);
}

namespace selaura {
    struct scanner {
        template <typename T>
        void resolve_signature() {
            auto result = hat::find_pattern(this->game_handle->bytes, T::value);

            constexpr auto fn = scan_target_traits<T>::value;
            signature_runtime_value<fn>::value = reinterpret_cast<std::uintptr_t>(result.get());

            if (signature_runtime_value<fn>::value == 0) {
                spdlog::error("Invalid signature for function, gracefully ejecting!");
                spdlog::error("Broken signature was: {}", T::signature.c_str());
                this->invalid_signatures = true;
            }
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
        void init();

        bool invalid_signatures = false;
    private:
        std::thread m_scanning_thread;
        signature_types signatures{};
        std::shared_ptr<handle> game_handle;
    };
};