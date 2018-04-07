#include "PlayerMovementSystem.h"

#include "InputManager.h"

void PlayerMovementSystem::Update()
{
    for (const anax::Entity& entity : getEntities())
    {
        const PlayerComponent playerComp = entity.getComponent<PlayerComponent>();
        TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        SDL_GameController* gameController = InputManager::GetInstance().GetController(playerComp.controllerInstanceId);
        if (gameController)
        {
            float axisLeftX = InputManager::GetControllerAxisWithDeadZone(gameController, SDL_CONTROLLER_AXIS_LEFTX);
            float axisLeftY = InputManager::GetControllerAxisWithDeadZone(gameController, SDL_CONTROLLER_AXIS_LEFTY);

            const float MoveSpeed = 60.0f;
            transformComp.position.x += axisLeftX * MoveSpeed;
            transformComp.position.y += axisLeftY * MoveSpeed;
        }
    }
}
