#pragma once
#include <cstddef>
#include <map>
#include <memory>

#include "ClientInstance.hpp"

struct MinecraftGame {
    std::byte pad[0x8F8];
    std::map<unsigned char, std::shared_ptr<ClientInstance>>* clientInstance_map;

    void update_hk();
    ClientInstance* getPrimaryClientInstance();
};
