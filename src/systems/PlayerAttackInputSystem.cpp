#include "PlayerAttackInputSystem.h"

#include "anax/World.hpp"

#include "InputManager.h"
#include "GameTimer.h"
#include "components/LinearAttackComponent.h"
#include "components/AttackComponent.h"
#include "AssetLoaderHelper.h"
#include "components/TextureComponent.h"
#include "components/AnimatedSpriteComponent.h"
#include "components/ChildComponent.h"
#include "components/SpriteComponent.h"
#include "components/TimedLifeComponent.h"

PlayerAttackInputSystem::PlayerAttackInputSystem()
{
    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    m_spriteAnimations = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");
}

void PlayerAttackInputSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
        const PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
        const TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        bool attackPressed = false;

        SDL_GameController* gameController = InputManager::GetInstance().GetController(playerComp.player.controllerInstanceId);
        if (gameController)
        {
            attackPressed = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_X) == 1;
            if (attackPressed && !playerComp.params.attackPressed)
            {
                LinearAttack(transformComp, playerComp);
            }
        }

        playerComp.params.attackPressed = attackPressed;
    }
}

void PlayerAttackInputSystem::LinearAttack(const TransformComponent& transform, const PlayerComponent& player) const
{
    anax::Entity entity = getWorld().createEntity();
    TransformComponent& attackTransformComp = entity.addComponent<TransformComponent>();
    attackTransformComp.position = transform.position;
    LinearAttackComponent& linearAttackComp = entity.addComponent<LinearAttackComponent>();
    linearAttackComp.direction.x = transform.flipHorizontal ? -1.0f : 1.0f;
    linearAttackComp.direction.y = 0.0f;
    AttackComponent& attackComp = entity.addComponent<AttackComponent>();
    attackComp.ownerPlayerId = player.player.id;
    PhysicsBodyComponent& attackPhysicsBodyComp = entity.addComponent<PhysicsBodyComponent>();
    attackPhysicsBodyComp.size.x = 32.0f;
    attackPhysicsBodyComp.size.y = 32.0f;
    attackPhysicsBodyComp.contactType = PhysicsBodyComponent::ContactType::Bullet;
    SpriteComponent& attackSpriteComp = entity.addComponent<SpriteComponent>();
    attackSpriteComp.frameName = "icon_orbs_materials_09.png";
    TextureComponent& attackTextureComp = entity.addComponent<TextureComponent>();
    attackTextureComp.texture = m_texture;
    attackTextureComp.textureFrames = m_textureFrames;
    TimedLifeComponent& attackTimedLifeComp = entity.addComponent<TimedLifeComponent>();
    attackTimedLifeComp.timeLeftToKeepAlive = 1.0f;
    entity.activate();

    anax::Entity secondaryEntity = getWorld().createEntity();
    TransformComponent& secondaryTransformComp = secondaryEntity.addComponent<TransformComponent>();
    secondaryTransformComp.position = transform.position;
    TextureComponent& secondaryTextureComp = secondaryEntity.addComponent<TextureComponent>();
    secondaryTextureComp.texture = m_texture;
    secondaryTextureComp.textureFrames = m_textureFrames;
    AnimatedSpriteComponent& secondarySpriteComp = secondaryEntity.addComponent<AnimatedSpriteComponent>();
    secondarySpriteComp.spriteAnimationsAsset = m_spriteAnimations;
    secondarySpriteComp.animationName = "fx_bling_anim";
    ChildComponent& secondaryChildComp = secondaryEntity.addComponent<ChildComponent>();
    secondaryChildComp.parentEntity = entity;
    secondaryEntity.activate();
}
