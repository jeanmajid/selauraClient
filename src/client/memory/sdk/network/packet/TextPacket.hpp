#pragma once
#include "../../client/renderer/rendergraph/Packet.hpp"
#include "TextPacketType.hpp"

struct TextPacket : public Packet {
    TextPacketType mType;
    std::string mAuthor;
    std::string mMessage;
    std::vector<std::string> params;
    bool mLocalize = false;
    std::string mXuid;
    std::string mPlatformId;

    TextPacket() = default;
};