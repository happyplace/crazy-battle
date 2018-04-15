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
            , attackPressTime(0.0)
        {}

        bool attackPressed;
        bool jumpPressed;
        double attackPressTime;
    };

    PlayerComponent() : moveSpeed(500.0f), state(State::Idle) {}
    State state;
    PlayerParams params;
    PlayerStruct player;
    float moveSpeed;
};
