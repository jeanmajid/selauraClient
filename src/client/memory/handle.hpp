#pragma once
#include <cstddef>
#include <memory>
#include <span>
#include <string_view>

namespace selaura {
    struct handle {
        void* ptr{};
        std::span<std::byte> bytes;
    };

    std::shared_ptr<handle> get_handle(std::string_view name);
};