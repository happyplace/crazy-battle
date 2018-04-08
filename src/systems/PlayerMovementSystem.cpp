#include "PlayerMovementSystem.h"

#include "InputManager.h"
#include "GameTimer.h"

#include "components/AnimatedSpriteComponent.h"

void PlayerMovementSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        const PlayerComponent playerComp = entity.getComponent<PlayerComponent>();
        TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        AnimatedSpriteComponent& animatedSpriteComp = entity.getComponent<AnimatedSpriteComponent>();

        SDL_GameController* gameController = InputManager::GetInstance().GetController(playerComp.controllerInstanceId);
        if (gameController)
        {
            float axisLeftX = InputManager::GetControllerAxisWithDeadZone(gameController, SDL_CONTROLLER_AXIS_LEFTX);
            float axisLeftY = InputManager::GetControllerAxisWithDeadZone(gameController, SDL_CONTROLLER_AXIS_LEFTY);

            const float MoveSpeed = 500.0f * static_cast<float>(gameTimer.DeltaTime());
            transformComp.position.x += axisLeftX * MoveSpeed;
            transformComp.position.y += axisLeftY * MoveSpeed;

            animatedSpriteComp.animationName = fabs(axisLeftX) > 0.01f ? "spr_m_traveler_walk_anim" : "spr_m_traveler_idle_anim";
        }
    }
}
