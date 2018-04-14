#pragma once

#include "anax/Component.hpp"

#include "GameManagerDefines.h"

struct PlayerComponent : anax::Component
{
    enum class State
    {
        Idle,
        Respawning,
        Dead,
    };

    struct PlayerParams
    {
        PlayerParams()
            : attackPressed(false)
            , jumpPressed(false)
        {}

        bool attackPressed;
        bool jumpPressed;
    };

    PlayerComponent() : moveSpeed(500.0f), state(State::Idle) {}
    State state;
    PlayerParams params;
    PlayerStruct player;
    float moveSpeed;
};
