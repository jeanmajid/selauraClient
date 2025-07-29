#pragma once
#include "../memory/sdk/world/BaseLightTextureImageBuilder.hpp"
#include "../memory/sdk/renderer/screen/MinecraftUIRenderContext.hpp"
#include "../memory/sdk/client/renderer/rendergraph/Packet.hpp"
#include <gsl/gsl>

namespace selaura {
    struct cancellable_event {
        void cancel() {
            this->cancelled = true;
        }

        bool cancelled;
    };

    struct BaseLightTextureImageBuilder_event {
        bool mNightvisionActive;
        float mNightvisionScale;
    };

    struct RenderCustom_event {
        gsl::not_null<CustomRenderComponent*> component;
    };

    struct RenderItemInHandDescription_event {
        glm::vec3 color;
        float alpha;
    };

    struct getTimeOfDay_event {
        int time;
        float overriden_time;
    };

    struct PacketRecieved_event {
        Packet* packet;
    };

    struct PacketSent_event {
        Packet* packet;
    };
};