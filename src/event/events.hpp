#pragma once
#include "event_manager.hpp"

#include <api/mc/client/gui/ScreenView.hpp>
#include <api/mc/client/renderer/MinecraftUIRenderContext.hpp>

namespace Selaura {
    template <EventPhase Phase>
    struct SetupAndRenderEvent : Event {
        ScreenView* mScreenView;
        MinecraftUIRenderContext* mCtx;
    };

    template <EventPhase Phase>
    struct RenderLevelEvent : Event {
        ScreenContext* mScreenContext;
    };
};