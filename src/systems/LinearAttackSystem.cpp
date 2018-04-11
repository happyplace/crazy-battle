#include "LinearAttackSystem.h"

#include "GameTimer.h"

void LinearAttackSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity entity : getEntities())
    {
        const LinearAttackComponent& linearAttackComp = entity.getComponent<LinearAttackComponent>();
        PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

        if (physicsBodyComp.params.body)
        {
            b2Vec2 linearVelocity(0.0f, 0.0f);
            const float MoveSpeed = 1000.0f * static_cast<float>(gameTimer.DeltaTime());
            linearVelocity.x = MoveSpeed * linearAttackComp.direction.x;
            linearVelocity.y = MoveSpeed * linearAttackComp.direction.y;
            physicsBodyComp.params.body->SetLinearVelocity(linearVelocity);
        }
    }
}
