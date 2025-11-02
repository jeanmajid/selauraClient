#pragma once
#include <api/mc/client/renderer/Tessellator.hpp>

class ScreenContext {
public:
    std::byte pad_1[0xB8];
    Tessellator* tessellator;
};