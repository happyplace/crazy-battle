#pragma once

#include <string>

#include "anax/Component.hpp"

#include "AssetLoaderDefines.h"

struct AnimatedSpriteComponent : anax::Component
{
    struct AnimationParams
    {
        AnimationParams() : timeOnFrame(0.0f), frame(0) {}
        float timeOnFrame;
        int frame;
    };

    std::string animationName;
    SpriteAnimationsAssetPtr spriteAnimationsAsset;
    AnimationParams animationParams;
};
