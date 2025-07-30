#pragma once
#include <spdlog/spdlog.h>

#include "MinecraftPacketIds.hpp"
#include "packet/TextPacket.hpp"

#include "../../patcher.hpp"
#include "../../../client.hpp"

template <MinecraftPacketIds id, bool Unknown = false>
struct PacketHandlerDispatcherInstance;

template <>
struct PacketHandlerDispatcherInstance<MinecraftPacketIds::Text> {
    void handle(void* networkIdentifier, void* netEventCallback, const std::shared_ptr<Packet>& packet) {
        selaura::call_fn<&PacketHandlerDispatcherInstance<MinecraftPacketIds::Text>::handle>(this, networkIdentifier, netEventCallback, packet);
    }
};