#pragma once
#include <cstddef>
#include <string>

class GuiMessage {
public:
    GuiMessage() = default;
    std::byte pad[0x8];
    std::string mMessage;
    std::byte pad2[0x24];
    std::string mTTSMessage;
    std::string mUsername;
    std::string mFullString;
    std::byte pad3[0x24];
    std::string xuid;
    std::byte pad4[0xA];
};