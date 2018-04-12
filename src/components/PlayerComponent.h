#pragma once

#include "anax/Component.hpp"

#include "GameManagerDefines.h"

struct PlayerComponent : anax::Component
{
    struct PlayerParams
    {
        PlayerParams()
            : attackPressed(false)
            , jumpPressed(false)
        {}

        bool attackPressed;
        bool jumpPressed;
    };

    PlayerComponent() : moveSpeed(500.0f) {}

    PlayerParams params;
    PlayerStruct player;
    float moveSpeed;
};
