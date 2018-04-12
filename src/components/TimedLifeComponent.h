#pragma once

#include "anax/Component.hpp"

struct TimedLifeComponent : anax::Component
{
    TimedLifeComponent() : timeLeftToKeepAlive(5.0f) {}
    float timeLeftToKeepAlive;
};
