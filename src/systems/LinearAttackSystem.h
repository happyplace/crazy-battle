#pragma once

#include "anax/System.hpp"

#include "components/LinearAttackComponent.h"
#include "components/PhysicsBodyComponent.h"

class GameTimer;

class LinearAttackSystem : public anax::System<anax::Requires<LinearAttackComponent, PhysicsBodyComponent>>
{
public:
	void Update(const GameTimer& gameTimer);
};
