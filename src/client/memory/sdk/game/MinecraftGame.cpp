#include "MinecraftGame.hpp"

#include <map>

#include "../../patcher.hpp"
#include "../../../client.hpp"

void MinecraftGame::update_hk() {
    selaura::minecraftGame = this;
    return selaura::call_fn<&MinecraftGame::update_hk>(this);
}

ClientInstance* MinecraftGame::getPrimaryClientInstance() {
    return clientInstance_map->at(0).get();
}