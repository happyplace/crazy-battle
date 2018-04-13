#pragma once

#include <cstdint>

#include "anax/Component.hpp"

#include "GameModeDataDefines.h"

struct PlayerDamageComponent : anax::Component
{
    PlayerDamageComponent()
        : senderPlayerId(-1)
        , receiverPlayerId(-1)
        , damageType(DamageType::None)
    {}

    int64_t senderPlayerId;
    int64_t receiverPlayerId;
    DamageType damageType;
};
