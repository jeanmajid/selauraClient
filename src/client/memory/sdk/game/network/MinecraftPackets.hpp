#pragma once
#include <memory>
#include "Packet.hpp"

struct MinecraftPackets {
    static inline std::shared_ptr<Packet> createPacket(MinecraftPacketIds id);
};
