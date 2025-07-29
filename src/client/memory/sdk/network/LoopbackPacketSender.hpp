#pragma once
#include "../client/renderer/rendergraph/Packet.hpp"

struct LoopbackPacketSender {
    void send_hk(Packet* packet);
};