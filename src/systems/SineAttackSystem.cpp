#include "SineAttackSystem.h"

#include "GameTimer.h"

void SineAttackSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity entity : getEntities())
    {
        const SineAttackComponent& sineAttackComp = entity.getComponent<SineAttackComponent>();
        PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

        if (physicsBodyComp.params.body)
        {
            b2Vec2 linearVelocity(0.0f, 0.0f);
            const float MoveSpeed = 500.0f * static_cast<float>(gameTimer.DeltaTime());
            linearVelocity.x = MoveSpeed * sineAttackComp.direction.x;
            linearVelocity.y = MoveSpeed * sineAttackComp.direction.y;
            physicsBodyComp.params.body->SetLinearVelocity(linearVelocity);
        }
    }
}
