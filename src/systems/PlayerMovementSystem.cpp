#include "PlayerMovementSystem.h"

void PlayerMovementSystem::Update()
{
    for (const anax::Entity& entity : getEntities())
    {
        const PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
    }
}
