#pragma once

#include "anax/System.hpp"

#include "components/TimedLifeComponent.h"

class GameTimer;

class TimedLifeSystem : public anax::System<anax::Requires<TimedLifeComponent>>
{
public:
	void Update(const GameTimer& gameTimer);
};
