#pragma once

#include "anax/Component.hpp"

#include <SDL.h>

struct PlayerComponent : anax::Component
{
    PlayerComponent() : controllerInstanceId(-1) {}

    SDL_JoystickID controllerInstanceId;
};
