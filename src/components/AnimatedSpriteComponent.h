#pragma once

#include <string>

#include "anax/Component.hpp"

#include "AssetLoaderDefines.h"

struct AnimatedSpriteComponent : anax::Component
{
    AnimatedSpriteComponent()
        : colour({ 0xff, 0xff, 0xff, 0xff })
        , enabled(true)
    {}

    struct AnimationParams
    {
        AnimationParams() : timeOnFrame(0.0f), frame(0) {}
        std::string prevAnimationName;
        float timeOnFrame;
        int frame;
    };

    std::string animationName;
    SpriteAnimationsAssetPtr spriteAnimationsAsset;
    AnimationParams animationParams;
    SDL_Color colour;
    bool enabled;
};
