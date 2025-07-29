#pragma once

namespace NetworkPeer {
    enum class Reliability : int {
        Reliable = 0,
        ReliableOrdered = 1,
        Unreliable = 2,
        UnreliableSequenced = 3,
    };
};