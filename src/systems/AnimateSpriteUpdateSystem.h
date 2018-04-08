#pragma once

#include "anax/System.hpp"

#include "components/AnimatedSpriteComponent.h"

class GameTimer;

class AnimateSpriteUpdateSystem : public anax::System<anax::Requires<AnimatedSpriteComponent>>
{
public:
    void Update(const GameTimer& gameTimer);
};
