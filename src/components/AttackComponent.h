#pragma once

#include "anax/Component.hpp"

struct AttackComponent : anax::Component
{
    AttackComponent() : ownerPlayerId(-1) {}
    int64_t ownerPlayerId;
};
