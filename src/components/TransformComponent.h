#pragma once

#include "anax/Component.hpp"
#include "tinymath2d.h"

struct TransformComponent : anax::Component
{
    TransformComponent()
        : position(0.0f, 0.0f)
        , rotation(0.0f)
        , scale(1.0f, 1.0f)
        , flipHorizontal(false)
        , flipVertical(false)
    {}

    v2 position;
    float rotation;
    v2 scale;
    bool flipHorizontal;
    bool flipVertical;
};
