#pragma once

#include "anax/System.hpp"

#include "components/PlayerDamageComponent.h"
#include "GameModeData.h"

class GameTimer;

class PlayerDamageSystem : public anax::System<anax::Requires<PlayerDamageComponent>>
{
public:
	explicit PlayerDamageSystem(GameModeData& gameModeData);

	void Update(const GameTimer& gameTimer);

private:
	GameModeData& m_gameModeData;
};
