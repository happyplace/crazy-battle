#include "PlayerAttackInputSystem.h"

#include "anax/World.hpp"

#include "InputManager.h"
#include "GameTimer.h"
#include "components/LinearAttackComponent.h"
#include "components/AttackComponent.h"

void PlayerAttackInputSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        const PlayerComponent playerComp = entity.getComponent<PlayerComponent>();
        const PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
        const TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        SDL_GameController* gameController = InputManager::GetInstance().GetController(playerComp.player.controllerInstanceId);
        if (gameController)
        {
            const bool attackPressed = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_X) == 1;
            if (attackPressed)
            {
                LinearAttack(transformComp, playerComp);
            }
        }
    }
}

void PlayerAttackInputSystem::LinearAttack(const TransformComponent& transform, const PlayerComponent& player) const
{
    anax::Entity entity = getWorld().createEntity();
    TransformComponent& attackTransformComp = entity.addComponent<TransformComponent>();
    attackTransformComp.position = transform.position;
    LinearAttackComponent& linearAttackComp = entity.addComponent<LinearAttackComponent>();
    linearAttackComp.direction.x = 1.0f;
    linearAttackComp.direction.y = 0.0f;
    AttackComponent& attackComp = entity.addComponent<AttackComponent>();
    attackComp.ownerPlayerId = player.player.id;
    PhysicsBodyComponent& attackPhysicsBodyComp = entity.addComponent<PhysicsBodyComponent>();
    attackPhysicsBodyComp.size.x = 32.0f;
    attackPhysicsBodyComp.size.y = 32.0f;
    attackPhysicsBodyComp.contactType = PhysicsBodyComponent::ContactType::Bullet;
    entity.activate();
}
