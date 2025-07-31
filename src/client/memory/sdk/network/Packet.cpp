#include "Packet.hpp"
#include "../../patcher.hpp"

MinecraftPacketIds Packet::getId() {
    return selaura::call_virtual<MinecraftPacketIds>(this, 1);
}