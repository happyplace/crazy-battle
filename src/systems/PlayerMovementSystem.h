#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "components/TransformComponent.h"

class GameTimer;

class PlayerMovementSystem : public anax::System<anax::Requires<PlayerComponent, TransformComponent>>
{
public:
    void Update(const GameTimer& gameTimer);
};
