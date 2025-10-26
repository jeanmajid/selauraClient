#pragma once
#include "event_manager.hpp"

#include <api/mc/client/gui/ScreenView.hpp>
#include <api/mc/client/renderer/MinecraftUIRenderContext.hpp>

namespace selaura {
    struct SetupAndRenderEvent : cancelable_event {
        ScreenView* mScreenView;
        MinecraftUIRenderContext* mCtx;
    };

    struct BeforeSetupAndRenderEvent : SetupAndRenderEvent {};
    struct AfterSetupAndRenderEvent : SetupAndRenderEvent {};
};