#pragma once
#include <memory>
#include "Packet.hpp"

struct LoopbackPacketSender {
    void send(Packet* packet);
};