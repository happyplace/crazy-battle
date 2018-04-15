#pragma once

#include "anax/System.hpp"

#include "components/SineAttackComponent.h"
#include "components/PhysicsBodyComponent.h"

class GameTimer;

class SineAttackSystem : public anax::System<anax::Requires<SineAttackComponent, PhysicsBodyComponent>>
{
public:
	void Update(const GameTimer& gameTimer);
};
