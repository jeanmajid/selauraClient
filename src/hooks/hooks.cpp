#include "hooks.hpp"
#include <safetyhook.hpp>
#include <libhat/scanner.hpp>
#include <print>

#include <loader/runtime.hpp>


#include <api/mc/world/Minecraft.hpp>
#include <api/mc/client/ClientInstance.hpp>
#include <api/mc/client/gui/ScreenView.hpp>

#include <event/events.hpp>

namespace selaura {
    template <hat::fixed_string str>
    void* find_signature() {
        auto signature = hat::compile_signature<str>();
        return reinterpret_cast<void*>(hat::find_pattern(signature, ".text").get());
    }
    namespace abi {
        template <typename T>
        constexpr void* mpf_to_fn(T member_fn) noexcept {
            static_assert(std::is_member_function_pointer_v<T>,
                          "mpf_to_fn expects a member function pointer");

#if defined(_MSC_VER)
            union {
                T mfptr;
                void* addr;
            } u{};
            u.mfptr = member_fn;
            return u.addr;
#else
            return reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(&member_fn));
#endif
        }

    }
}

SafetyHookInline Minecraft_$ctor_hk;
SafetyHookInline ClientInstance_$ctor_hk;
SafetyHookInline ScreenView_setupAndRender_hk;

Minecraft* Minecraft::$ctor(void *app, void *gameCallbacks, void *allowList, void *permissionsFile, void *filePathManager, void *maxPlayerIdleTime, void *eventing, void *network, void *packetSender, void *clientSubId, void *simTimer, void *realTimer, void *contentTierManager, void *serverMetrics) {
    auto rt = Minecraft_$ctor_hk.thiscall<Minecraft*>(this, app, gameCallbacks, allowList, permissionsFile, filePathManager, maxPlayerIdleTime, eventing, network, packetSender, clientSubId, simTimer, realTimer, contentTierManager, serverMetrics);

    if (selaura::runtime_instance->client_ctx->mMinecraft == nullptr) {
        selaura::runtime_instance->client_ctx->mMinecraft = rt;
        selaura::runtime_instance->mc_client_thread = std::this_thread::get_id();
    } else {
        selaura::runtime_instance->server_ctx->mMinecraft = rt;
        selaura::runtime_instance->mc_server_thread = std::this_thread::get_id();
    }
    return rt;
};

void* ClientInstance::$ctor(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9) {
    auto rt = ClientInstance_$ctor_hk.thiscall<void*>(this, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    selaura::runtime_instance->client_ctx->mClientInstance = this;
    return rt;
}

void ScreenView::setupAndRender_hk(MinecraftUIRenderContext *ctx) {
    selaura::BeforeSetupAndRenderEvent before_ev{};
    before_ev.mScreenView = this;
    before_ev.mCtx = ctx;

    selaura::runtime_instance->event_manager->post(before_ev);

    return ScreenView_setupAndRender_hk.thiscall<void>(this, ctx);

    selaura::AfterSetupAndRenderEvent after_ev{};
    after_ev.mScreenView = this;
    after_ev.mCtx = ctx;

    selaura::runtime_instance->event_manager->post(after_ev);
}


void selaura::init_hooks() {
    Minecraft_$ctor_hk = safetyhook::create_inline(
        find_signature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4D 8B E1 49 8B D8 4C 8B EA">(),
        abi::mpf_to_fn(&Minecraft::$ctor)
    );

    ClientInstance_$ctor_hk = safetyhook::create_inline(
        find_signature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2">(),
        abi::mpf_to_fn(&ClientInstance::$ctor)
    );

    ScreenView_setupAndRender_hk = safetyhook::create_inline(
        find_signature<"48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA">(),
        abi::mpf_to_fn(&ScreenView::setupAndRender_hk)
    );
}