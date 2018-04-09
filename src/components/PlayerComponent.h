#pragma once

#include "anax/Component.hpp"

#include "GameManagerDefines.h"

struct PlayerComponent : anax::Component
{
    PlayerComponent() {}

    PlayerStruct player;
};
