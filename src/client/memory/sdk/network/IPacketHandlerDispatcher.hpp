#pragma once
#include <memory>

struct Packet;

struct IPacketHandlerDispatcher {
    virtual ~IPacketHandlerDispatcher() = default;
    virtual void handle(void* networkIdentifier, void* netEventCallback, std::shared_ptr<Packet>&) const = 0;
};
