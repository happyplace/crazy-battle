#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "components/PhysicsBodyComponent.h"
#include "components/TransformComponent.h"

class GameTimer;

class PlayerAttackInputSystem : public anax::System<anax::Requires<PlayerComponent, PhysicsBodyComponent, TransformComponent>>
{
public:
    void Update(const GameTimer& gameTimer);

private:
    void LinearAttack(const TransformComponent& transform, const PlayerComponent& player) const;
};
