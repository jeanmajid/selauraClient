#pragma once
#include "../../../network/MinecraftPacketIds.hpp"
#include "../../../network/IPacketHandlerDispatcher.hpp"
#include "../../../deps/raknet/PacketPriority.hpp"
#include "../../../network/Compressibility.hpp"
#include "../../../network/NetworkPeer.hpp"
#include <chrono>

struct Packet {
    virtual ~Packet() = default;
    PacketPriority mPriority;
    NetworkPeer::Reliability mReliability;
    uint8_t mClientSubId;
    bool mIsHandled;
    std::chrono::steady_clock::time_point mReceiveTimepoint;
    const IPacketHandlerDispatcher* mHandler;
    Compressibility mCompressible;
};