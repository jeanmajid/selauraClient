#pragma once

enum class MinecraftPacketIds : int {
    Text = 0x9
};

struct PacketHandlerDispatcherInstance {
    std::byte pad[0x2];
};

struct Packet {
    std::byte pad[0x20];
    PacketHandlerDispatcherInstance* handler;
    std::byte pad2[0x8];
};

enum class TextPacketType : int {
    RAW = 0,
    CHAT = 1,
    TRANSLATION = 2,
    POPUP = 3,
    JUKEBOX_POPUP = 4,
    TIP = 5,
    SYSTEM = 6,
    WHISPER = 7,
    ANNOUNCEMENT = 8,
    JSON_WHISPER = 9,
    JSON = 10,
    JSON_ANNOUNCEMENT = 11
};

struct TextPacket : public Packet {
    TextPacketType mType;
    std::string mName;
    std::string mMessage;
    std::vector<std::string> mParams;
    bool translationNeeded = false;
    std::string xuid;
    std::string platformId;

    TextPacket() = default;
};