#include "LoopbackPacketSender.hpp"
#include "../../../patcher.hpp"
#include "../../../../client.hpp"
#include "../../../../event/event_types.hpp"

void LoopbackPacketSender::send(Packet* packet) {
    selaura::call_fn<&LoopbackPacketSender::send>(this, packet);
}
