#pragma once

namespace bedrock {
	enum class GameType {
        Undefined = -1,
        Survival = 0,
        Creative = 1,
        Adventure = 2,
        Default = 5,
        Spectator = 6,
        WorldDefault = Survival
	};
};