#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "components/PhysicsBodyComponent.h"
#include "components/TransformComponent.h"
#include "components/AnimatedSpriteComponent.h"

class GameTimer;

class PlayerAnimationSystem : public anax::System<anax::Requires<
        PlayerComponent,
        PhysicsBodyComponent,
        TransformComponent,
        AnimatedSpriteComponent>>
{
public:
    void Update(const GameTimer& gameTimer);
};
