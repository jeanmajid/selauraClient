#pragma once

struct Packet {
    std::byte pad[0x1];
    int id;
};