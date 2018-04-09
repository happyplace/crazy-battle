#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "components/PhysicsBodyComponent.h"

class GameTimer;

class PlayerMovementSystem : public anax::System<anax::Requires<PlayerComponent, PhysicsBodyComponent>>
{
public:
    void Update(const GameTimer& gameTimer);
};
