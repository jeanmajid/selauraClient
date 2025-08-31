#pragma once
#include "../../mcsdk.hpp"
#include "PacketPriority.hpp"
#include "NetworkPeer.hpp"
#include "../common/SubClientId.hpp"
#include "IPacketHandlerDispatcher.hpp"
#include "Compressibility.hpp"
#include "MinecraftPacketIds.hpp"

class Packet {
public:
    PacketPriority mPriority;
    NetworkPeer::Reliability mReliability;
    SubClientId mSenderSubId;
    bool mIsHandled;
    std::chrono::steady_clock::time_point mReceiveTimepoint;
    const IPacketHandlerDispatcher* mHandler;
    Compressibility mCompressible;
public:
    virtual MCSDK ~Packet() = default;
    virtual MCSDK MinecraftPacketIds getId() const = 0;
    virtual MCSDK std::string getName() const = 0;
};