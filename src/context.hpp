#pragma once
#include <thread>

#include <api/mc/world/Minecraft.hpp>
#include <api/mc/client/ClientInstance.hpp>

namespace Selaura {
    struct SharedContext {
        Minecraft* mMinecraft;
    };

    struct ClientContext : SharedContext {
        ClientInstance* mClientInstance;
    };

    struct ServerContext : SharedContext {};

    struct RuntimeContext {
        std::thread::id thread_id;
        int version_major;
        int version_minor;
        int version_build;
        int version_revision;

        ClientContext* client_ctx;
        ServerContext* server_ctx;
    };
};