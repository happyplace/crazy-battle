#include "PlayerDamageSystem.h"

#include "GameTimer.h"

PlayerDamageSystem::PlayerDamageSystem(GameModeData& gameModeData)
	: m_gameModeData(gameModeData)
{
}

void PlayerDamageSystem::Update(const GameTimer& gameTimer)
{
    for (anax::Entity entity : getEntities())
    {
        PlayerDamageComponent& playerDamageComp = entity.getComponent<PlayerDamageComponent>();
        m_gameModeData.OnPlayerDamage(playerDamageComp.senderPlayerId, playerDamageComp.receiverPlayerId, playerDamageComp.damageType);
        entity.kill();
    }
}
