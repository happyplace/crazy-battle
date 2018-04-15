#pragma once

#include "anax/Component.hpp"
#include "tinymath2d.h"

struct SineAttackComponent : anax::Component
{
    SineAttackComponent() : direction(0.0f, 0.0f) {}
    v2 direction;
};
