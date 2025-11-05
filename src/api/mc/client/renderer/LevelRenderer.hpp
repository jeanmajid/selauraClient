#pragma once
#include <api/mc/client/renderer/ScreenContext.hpp>

class LevelRenderer {
public:
    void renderLevel(ScreenContext* screenContext, void* renderObj);
    void renderLevel_hk(ScreenContext* screenContext, void* renderObj);
};
