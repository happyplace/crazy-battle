#pragma once

#include "anax/Component.hpp"

#include "GameManagerDefines.h"

struct PlayerComponent : anax::Component
{
    PlayerComponent() : moveSpeed(500.0f) {}

    PlayerStruct player;
    float moveSpeed;
};
