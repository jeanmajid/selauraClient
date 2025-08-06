#pragma once
#include "../../mcsdk.hpp"

class Packet;

class IPacketHandlerDispatcher {
public:
    virtual MCSDK ~IPacketHandlerDispatcher() = default;
    virtual MCSDK void handle(const void* networkIdentifier, void* netEventCallback, std::shared_ptr<Packet>&) const = 0;
};
