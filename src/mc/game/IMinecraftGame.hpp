#pragma once
#include "../mcsdk.hpp"

class IMinecraftGame {
public:
    virtual MCSDK void initialize(int, char**) = 0;
    virtual MCSDK ~IMinecraftGame() = default;
    virtual MCSDK void update() = 0;
};