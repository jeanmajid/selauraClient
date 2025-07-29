#include "LoopbackPacketSender.hpp"
#include "../../patcher.hpp"
#include "../../../client.hpp"
#include "../../../event/event_types.hpp"

void LoopbackPacketSender::send_hk(Packet* packet) {
    selaura::PacketSent_event event{ packet };
    auto& ev = selaura::get()->get<selaura::event_manager>();
    ev.dispatch<selaura::PacketSent_event>(event);

    selaura::call_fn<&LoopbackPacketSender::send_hk>(packet);
}
