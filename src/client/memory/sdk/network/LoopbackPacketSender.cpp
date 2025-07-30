#include "LoopbackPacketSender.hpp"
#include "../../patcher.hpp"
#include "../../../client.hpp"
#include "../../../event/event_types.hpp"

#include "packet/TextPacket.hpp"

void LoopbackPacketSender::send_hk(Packet* packet) {
    selaura::PacketSent_event event{ packet };
    auto& ev = selaura::get()->get<selaura::event_manager>();
    ev.dispatch<selaura::PacketSent_event>(event);

    if (packet->getId() == MinecraftPacketIds::Text) {
        auto text_packet = reinterpret_cast<TextPacket*>(packet);
        auto guiData = selaura::minecraftGame->getPrimaryClientInstance()->guiData;

        if (text_packet->mMessage.starts_with(".")) {
            auto command = text_packet->mMessage.substr(1);
            auto& command_handler = selaura::get()->get<selaura::command_handler>();

            return selaura::call_original<&GuiData::displayClientMessage>(guiData, command_handler.execute(command), std::nullopt, false);
        }
    }

    return selaura::call_fn<&LoopbackPacketSender::send_hk>(this, packet);
}
