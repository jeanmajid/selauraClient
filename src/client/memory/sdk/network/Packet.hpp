#pragma once
#include "MinecraftPacketIds.hpp"
#include "IPacketHandlerDispatcher.hpp"
#include "../deps/raknet/PacketPriority.hpp"
#include "Compressibility.hpp"
#include "NetworkPeer.hpp"
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

    MinecraftPacketIds getId();
};
