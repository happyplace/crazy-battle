#pragma once

#include <string>

#include <SDL.h>
#include "anax/Component.hpp"

struct SpriteComponent : anax::Component
{
    SpriteComponent() : colour({ 0xff, 0xff, 0xff, 0xff }) {}

    std::string frameName;
    SDL_Color colour;
};
