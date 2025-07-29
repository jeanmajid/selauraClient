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
        auto text_packet = reinterpret_cast<TextPacket*>(packet.get());

        if (text_packet->mMessage.starts_with(".")) {
            auto command = text_packet->mMessage.substr(1);

            auto guiData = selaura::minecraftGame->getPrimaryClientInstance()->guiData;
            selaura::call_original<&GuiData::displayClientMessage>(guiData, std::format("§cWe aren't there yet! But the command was: {}", command), std::nullopt, false);
        } else {
            selaura::call_fn<&PacketHandlerDispatcherInstance<MinecraftPacketIds::Text>::handle>(this, networkIdentifier, netEventCallback, packet);
        }
    }
};