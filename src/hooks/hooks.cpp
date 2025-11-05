#include "hooks.hpp"
#include <safetyhook.hpp>
#include <print>

#include <../runtime.hpp>
#include "memory.hpp"

#include <api/mc/world/Minecraft.hpp>
#include <api/mc/client/ClientInstance.hpp>
#include <api/mc/client/gui/ScreenView.hpp>

#include <event/events.hpp>

#include <api/mc/client/renderer/LevelRenderer.hpp>
#include "spdlog/sinks/basic_file_sink-inl.h"

SafetyHookInline Minecraft_$ctor_hk;
SafetyHookInline ClientInstance_$ctor_hk;
SafetyHookInline ScreenView_setupAndRender_hk;
SafetyHookInline LevelRenderer_renderLevel_hk;

Minecraft *Minecraft::$ctor(void *app, void *gameCallbacks, void *allowList, void *permissionsFile,
                            void *filePathManager, void *maxPlayerIdleTime, void *eventing, void *network,
                            void *packetSender, void *clientSubId, void *simTimer, void *realTimer,
                            void *contentTierManager, void *serverMetrics) {
    auto rt = Minecraft_$ctor_hk.thiscall<Minecraft *>(this, app, gameCallbacks, allowList, permissionsFile,
                                                       filePathManager, maxPlayerIdleTime, eventing, network,
                                                       packetSender, clientSubId, simTimer, realTimer,
                                                       contentTierManager, serverMetrics);

    if (Selaura::RuntimeInstance->mClientCtx->mMinecraft == nullptr) {
        Selaura::RuntimeInstance->mClientCtx->mMinecraft = rt;
        Selaura::RuntimeInstance->mClientThread = std::this_thread::get_id();
    } else {
        Selaura::RuntimeInstance->mServerCtx->mMinecraft = rt;
        Selaura::RuntimeInstance->mServerThread = std::this_thread::get_id();
    }
    return rt;
};

void *ClientInstance::$ctor(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9) {
    auto rt = ClientInstance_$ctor_hk.thiscall<void *>(this, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    Selaura::RuntimeInstance->mClientCtx->mClientInstance = this;
    return rt;
}

void ScreenView::setupAndRender_hk(MinecraftUIRenderContext *ctx) {
    Selaura::SetupAndRenderEvent<Selaura::EventPhase::Pre> before_ev{};
    before_ev.mScreenView = this;
    before_ev.mCtx = ctx;

    Selaura::RuntimeInstance->mEventManager->post(before_ev);

    ScreenView_setupAndRender_hk.thiscall<void>(this, ctx);

    Selaura::SetupAndRenderEvent<Selaura::EventPhase::Post> after_ev{};
    after_ev.mScreenView = this;
    after_ev.mCtx = ctx;

    Selaura::RuntimeInstance->mEventManager->post(after_ev);
}

void LevelRenderer::renderLevel_hk(ScreenContext *screenContext, void *renderObj) {
    Selaura::RenderLevelEvent<Selaura::EventPhase::Pre> before_ev{};
    before_ev.mScreenContext = screenContext;

    Selaura::RuntimeInstance->mEventManager->post(before_ev);

    LevelRenderer_renderLevel_hk.thiscall<void>(this, screenContext, renderObj);

    Selaura::RenderLevelEvent<Selaura::EventPhase::Post> after_ev{};
    after_ev.mScreenContext = screenContext;
    Selaura::RuntimeInstance->mEventManager->post(after_ev);
}

void Selaura::InitHooks() {
    Minecraft_$ctor_hk = safetyhook::create_inline(
        FindSignature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B D8 4C 8B F2">(),
        abi::mpf_to_fn(&Minecraft::$ctor)
    );

    // ClientInstance_$ctor_hk = safetyhook::create_inline(
    //     find_signature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2">(),
    //     abi::mpf_to_fn(&ClientInstance::$ctor)
    // );

    ScreenView_setupAndRender_hk = safetyhook::create_inline(
        FindSignature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA">(),
        abi::mpf_to_fn(&ScreenView::setupAndRender_hk)
    );

    LevelRenderer_renderLevel_hk = safetyhook::create_inline(
        FindSignature<"48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E8 4C 8B E2 4C 8B F9">(),
        abi::mpf_to_fn(&LevelRenderer::renderLevel_hk)
    );
}
