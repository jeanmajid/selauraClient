#pragma once
#include <memory>
#include "../client/renderer/rendergraph/Packet.hpp"

struct MinecraftPackets {
    static inline std::shared_ptr<Packet> createPacket(MinecraftPacketIds id);
};
