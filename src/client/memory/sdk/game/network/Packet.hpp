#pragma once
#include <cstdint>

enum class MinecraftPacketIds : int {
    Text = 0x9
};

struct PacketHandlerDispatcherInstance {
    virtual ~PacketHandlerDispatcherInstance() = default;
};

enum class PacketPriority : int {
    ImmediatePriority = 0,
    HighPriority = 1,
    MediumPriority = 2,
    LowPriority = 3,
    NumberOfPriorities = 4,
};

enum class Compressibility : int {
    Compressible = 0,
    Incompressible = 1,
};

namespace NetworkPeer {
    enum class Reliability : int {
        Reliable = 0,
        ReliableOrdered = 1,
        Unreliable = 2,
        UnreliableSequenced = 3,
    };
};

struct Packet {
    virtual ~Packet() = default;
    PacketPriority mPriority;
    NetworkPeer::Reliability mReliability;
    uint8_t mClientSubId;
    bool mIsHandled;
    std::chrono::steady_clock::time_point mReceiveTimepoint;
    PacketHandlerDispatcherInstance* mHandler;
    Compressibility mCompressible;
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
    std::string mAuthor;
    std::string mMessage;
    std::vector<std::string> params;
    bool mLocalize = false;
    std::string mXuid;
    std::string mPlatformId;

    TextPacket() = default;
};

static_assert(sizeof(Packet) == 0x30);