#include "PlayerAnimationSystem.h"

#include "GameTimer.h"

void PlayerAnimationSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        const PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
        const PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
        TransformComponent& transformComp = entity.getComponent<TransformComponent>();
        AnimatedSpriteComponent& animatedSpriteComp = entity.getComponent<AnimatedSpriteComponent>();

        const b2Vec2& linearVelocity = physicsBodyComp.params.body->GetLinearVelocity();

        const float MoveSpeed = playerComp.moveSpeed * static_cast<float>(gameTimer.DeltaTime());
        float speedX = static_cast<float>(fabs(linearVelocity.x));
        if (linearVelocity.y > 0.1f)
        {
            animatedSpriteComp.animationName = "spr_m_traveler_jump_3down_anim";
        }
        else if (linearVelocity.y < -0.1f)
        {
            animatedSpriteComp.animationName = "spr_m_traveler_jump_1up_anim";
        }
        else if (speedX > (MoveSpeed * 0.7f))
        {
            animatedSpriteComp.animationName = "spr_m_traveler_run_anim";
        }
        else if (speedX > 0.1f)
        {
            animatedSpriteComp.animationName = "spr_m_traveler_walk_anim";
        }
        else
        {
            animatedSpriteComp.animationName = "spr_m_traveler_idle_anim";
        }

        const float TurnThreshold = 0.2f;
        if (linearVelocity.x < -TurnThreshold)
        {
            transformComp.flipHorizontal = true;
        }
        else if (linearVelocity.x > TurnThreshold)
        {
            transformComp.flipHorizontal = false;
        }
    }
}
