#pragma once

#include <string>

#include "anax/Component.hpp"

struct SpriteComponent : anax::Component
{
    std::string frameName;
};
