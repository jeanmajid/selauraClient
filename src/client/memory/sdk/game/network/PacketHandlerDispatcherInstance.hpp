#pragma once
#include "Packet.hpp"
#include <spdlog/spdlog.h>

#include "../../../patcher.hpp"

template <MinecraftPacketIds id>
struct PacketHandlerDispatcherInstance_callbacks;

template <>
struct PacketHandlerDispatcherInstance_callbacks<MinecraftPacketIds::Text> {
    void handle(void* networkIdentifier, void* netEventCallback, const std::shared_ptr<Packet>& packet) {
        auto text_packet = reinterpret_cast<TextPacket*>(packet.get());

        if (text_packet->mMessage.starts_with(".")) {
            auto command = text_packet->mMessage.substr(1);

            auto guiData = selaura::minecraftGame->getPrimaryClientInstance()->guiData;
            selaura::call_original<&GuiData::displayClientMessage>(guiData, std::format("§cWe aren't there yet! But the command was: {}", command), std::nullopt, false);
        } else {
            selaura::call_fn<&PacketHandlerDispatcherInstance_callbacks<MinecraftPacketIds::Text>::handle>(this, networkIdentifier, netEventCallback, packet);
        }
    }
};