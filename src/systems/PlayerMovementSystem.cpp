﻿#include "PlayerMovementSystem.h"

#include "InputManager.h"
#include "GameTimer.h"

void PlayerMovementSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
        PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

        bool jumpPressed = false;

        SDL_GameController* gameController = InputManager::GetInstance().GetController(playerComp.player.controllerInstanceId);
        if (gameController)
        {
            b2Vec2 linearVelocity = physicsBodyComp.params.body->GetLinearVelocity();
            const float axisLeftX = InputManager::GetControllerAxisWithDeadZone(gameController, SDL_CONTROLLER_AXIS_LEFTX);
            const float MoveSpeed = playerComp.moveSpeed * static_cast<float>(gameTimer.DeltaTime());
            linearVelocity.x = MoveSpeed * axisLeftX;
            physicsBodyComp.params.body->SetLinearVelocity(linearVelocity);

            jumpPressed = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_A) == 1;
            if ((jumpPressed && !playerComp.params.jumpPressed) && fabs(linearVelocity.y) < 0.1f)
            {
                physicsBodyComp.params.body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -65.0f), true);
            }
        }

        playerComp.params.jumpPressed = jumpPressed;
    }
}
