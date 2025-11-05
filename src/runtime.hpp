#pragma once
#include <optional>
#include <thread>

#include "context.hpp"
#include <event/event_manager.hpp>

namespace Selaura {
    struct Runtime {
        std::thread::id mThreadId;
        std::optional<std::thread::id> mClientThread;
        std::optional<std::thread::id> mServerThread;

        std::unique_ptr<ClientContext> mClientCtx;
        std::unique_ptr<ServerContext> mServerCtx;

        std::unique_ptr<EventManager> mEventManager;

        Runtime(const RuntimeContext& ctx);
        void start();

        bool mUnload = false;
    };

    inline std::shared_ptr<Runtime> RuntimeInstance;
};