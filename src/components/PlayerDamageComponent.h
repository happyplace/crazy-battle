#pragma once

#include <cstdint>

#include "anax/Component.hpp"

struct PlayerDamageComponent : anax::Component
{
	PlayerDamageComponent() : senderPlayerId(-1), receiverPlayerId(-1) {}

	int64_t senderPlayerId;
	int64_t receiverPlayerId;
};
