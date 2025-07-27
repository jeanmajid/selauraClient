#pragma once
#include <optional>
#include <string>

struct GuiData {
    inline void displayClientMessage(const std::string& message, std::optional<std::string> a2 = {}, bool a3 = false);
};