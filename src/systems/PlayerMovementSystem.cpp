#include "PlayerMovementSystem.h"

#include "InputManager.h"
#include "GameTimer.h"

//#include "components/AnimatedSpriteComponent.h"
//#include "components/TransformComponent.h"

void PlayerMovementSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        const PlayerComponent playerComp = entity.getComponent<PlayerComponent>();
        PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

        SDL_GameController* gameController = InputManager::GetInstance().GetController(playerComp.player.controllerInstanceId);
        if (gameController)
        {
            b2Vec2 linearVelocity = physicsBodyComp.params.body->GetLinearVelocity();
            const float axisLeftX = InputManager::GetControllerAxisWithDeadZone(gameController, SDL_CONTROLLER_AXIS_LEFTX);
            const float MoveSpeed = 500.0f * static_cast<float>(gameTimer.DeltaTime());
            linearVelocity.x = MoveSpeed * axisLeftX;
            physicsBodyComp.params.body->SetLinearVelocity(linearVelocity);

//            const bool jumpPressed = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_A) == 1;
//            if (jumpPressed && fabs(linearVelocity.y) < 0.1f)
//            {
//                physicsBodyComp.params.body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -130.0f), true);
//            }

            //TransformComponent& transformComp = entity.getComponent<TransformComponent>();

//            const float TurnThreshold = 0.2f;
//            if (linearVelocity.x < -TurnThreshold)
//            {
//                transformComp.flipHorizontal = true;
//            }
//            else if (linearVelocity.x > TurnThreshold)
//            {
//                transformComp.flipHorizontal = false;
//            }

            //AnimatedSpriteComponent& animatedSpriteComp = entity.getComponent<AnimatedSpriteComponent>();
            //animatedSpriteComp.animationName = fabs(axisLeftX) > 0.01f ? "spr_m_traveler_walk_anim" : "spr_m_traveler_idle_anim";
        }
    }
}
