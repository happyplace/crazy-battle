#pragma once

#include <cstdint>

#include "anax/Component.hpp"

struct PlayerDamageComponent : anax::Component
{
    enum class DamageType { None, Linear, };

    PlayerDamageComponent()
        : senderPlayerId(-1)
        , receiverPlayerId(-1)
        , damageType(DamageType::None)
    {}

	int64_t senderPlayerId;
	int64_t receiverPlayerId;
    DamageType damageType;
};
