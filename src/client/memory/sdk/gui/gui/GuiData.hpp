#pragma once
#include <optional>
#include <string>
#include <vector>

#include "GuiMessage.hpp"

struct GuiData {
    std::byte pad[0x150];
    std::vector<GuiMessage> mGuiMessages;

    inline void displayClientMessage(const std::string& message, std::optional<std::string> a2 = {}, bool a3 = false);
};
