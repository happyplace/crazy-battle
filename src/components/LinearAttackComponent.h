#pragma once

#include "anax/Component.hpp"
#include "tinymath2d.h"

struct LinearAttackComponent : anax::Component
{
    LinearAttackComponent() : direction(0.0f, 0.0f) {}
    v2 direction;
};
