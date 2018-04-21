#include "PlayerMovementSystem.h"

#include "InputManager.h"
#include "GameTimer.h"

void PlayerMovementSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
        PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

        bool jumpPressed = false;

        GamePadPtr gamePad = InputManager::GetInstance().GetGamePad(playerComp.player.gamePadId);
        if (gamePad)
        {
            b2Vec2 linearVelocity = physicsBodyComp.params.body->GetLinearVelocity();
            const float axisLeftX = gamePad->MoveX();
            const float MoveSpeed = playerComp.moveSpeed * static_cast<float>(gameTimer.DeltaTime());
            linearVelocity.x = MoveSpeed * axisLeftX;
            physicsBodyComp.params.body->SetLinearVelocity(linearVelocity);

            jumpPressed = gamePad->Jump();
            if ((jumpPressed && !playerComp.params.jumpPressed) && fabs(linearVelocity.y) < 0.1f)
            {
                physicsBodyComp.params.body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -65.0f), true);
            }
        }

        playerComp.params.jumpPressed = jumpPressed;
    }
}
