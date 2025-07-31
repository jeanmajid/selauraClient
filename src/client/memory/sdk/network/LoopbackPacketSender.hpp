#pragma once
#include "Packet.hpp"

struct LoopbackPacketSender {
    void send_hk(Packet* packet);
};