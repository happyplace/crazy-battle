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
#include "components/SineAttackComponent.h"

PlayerAttackInputSystem::PlayerAttackInputSystem(GameModeData& gameModeData)
    : m_gameModeData(gameModeData)
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

        if (playerComp.state == PlayerComponent::State::Idle && m_gameModeData.IsGameRunning())
        {
            GamePadPtr gamePad = InputManager::GetInstance().GetGamePad(playerComp.player.gamePadId);
            if (gamePad)
            {
                attackPressed = gamePad->Attack();
                if (!playerComp.params.attackPressed && attackPressed)
                {
                    playerComp.params.attackPressTime = gameTimer.TotalTime();
                }

                if (!attackPressed && playerComp.params.attackPressed)
                {
                    double secondsHeld = gameTimer.TotalTime() - playerComp.params.attackPressTime;
                    if (secondsHeld >= 0.5)
                        SineAttack(transformComp, playerComp);
                    else
                        LinearAttack(transformComp, playerComp);
                }
            }
        }

        playerComp.params.attackPressed = attackPressed;
    }
}

void PlayerAttackInputSystem::LinearAttack(const TransformComponent& transform, const PlayerComponent& player) const
{
    ColorPair* colorPair = m_gameModeData.GetColorPair(player.player.id);

    v2 position = transform.position;
    position.x += 40.0f;
    position.y += 40.0f;

    anax::Entity entity = getWorld().createEntity();
    TransformComponent& attackTransformComp = entity.addComponent<TransformComponent>();
    attackTransformComp.position = position;
    LinearAttackComponent& linearAttackComp = entity.addComponent<LinearAttackComponent>();
    linearAttackComp.direction.x = transform.flipHorizontal ? -1.0f : 1.0f;
    linearAttackComp.direction.y = 0.0f;
    AttackComponent& attackComp = entity.addComponent<AttackComponent>();
    attackComp.ownerPlayerId = player.player.id;
    PhysicsBodyComponent& attackPhysicsBodyComp = entity.addComponent<PhysicsBodyComponent>();
    attackPhysicsBodyComp.size.x = 32.0f;
    attackPhysicsBodyComp.size.y = 32.0f;
    attackPhysicsBodyComp.contactType = PhysicsBodyComponent::ContactType::Bullet;
    attackPhysicsBodyComp.category = colorPair->category;
    attackPhysicsBodyComp.hasGravity = false;
    SpriteComponent& attackSpriteComp = entity.addComponent<SpriteComponent>();
    attackSpriteComp.frameName = "icon_orbs_materials_09.png";
    attackSpriteComp.colour = m_gameModeData.GetColorPair(player.player.id)->color;
    TextureComponent& attackTextureComp = entity.addComponent<TextureComponent>();
    attackTextureComp.texture = m_texture;
    attackTextureComp.textureFrames = m_textureFrames;
    TimedLifeComponent& attackTimedLifeComp = entity.addComponent<TimedLifeComponent>();
    attackTimedLifeComp.timeLeftToKeepAlive = 1.0f;
    entity.activate();

    anax::Entity secondaryEntity = getWorld().createEntity();
    TransformComponent& secondaryTransformComp = secondaryEntity.addComponent<TransformComponent>();
    secondaryTransformComp.position = position;
    TextureComponent& secondaryTextureComp = secondaryEntity.addComponent<TextureComponent>();
    secondaryTextureComp.texture = m_texture;
    secondaryTextureComp.textureFrames = m_textureFrames;
    AnimatedSpriteComponent& secondarySpriteComp = secondaryEntity.addComponent<AnimatedSpriteComponent>();
    secondarySpriteComp.spriteAnimationsAsset = m_spriteAnimations;
    secondarySpriteComp.animationName = "fx_bling_anim";
    secondarySpriteComp.colour = m_gameModeData.GetColorPair(player.player.id)->color;
    ChildComponent& secondaryChildComp = secondaryEntity.addComponent<ChildComponent>();
    secondaryChildComp.parentEntity = entity;
    secondaryEntity.activate();
}

void PlayerAttackInputSystem::SineAttack(const TransformComponent& transform, const PlayerComponent& player) const
{
    ColorPair* colorPair = m_gameModeData.GetColorPair(player.player.id);

    v2 position = transform.position;
    position.x += 40.0f;
    position.y += 40.0f;

    anax::Entity entity = getWorld().createEntity();
    TransformComponent& attackTransformComp = entity.addComponent<TransformComponent>();
    attackTransformComp.position = position;
    attackTransformComp.flipHorizontal = transform.flipHorizontal;
    SineAttackComponent& sineAttackComp = entity.addComponent<SineAttackComponent>();
    sineAttackComp.direction.x = transform.flipHorizontal ? -1.0f : 1.0f;
    sineAttackComp.direction.y = 0.0f;
    AttackComponent& attackComp = entity.addComponent<AttackComponent>();
    attackComp.ownerPlayerId = player.player.id;
    PhysicsBodyComponent& attackPhysicsBodyComp = entity.addComponent<PhysicsBodyComponent>();
    attackPhysicsBodyComp.size.x = 60.0f;
    attackPhysicsBodyComp.size.y = 48.0f;
    attackPhysicsBodyComp.offset.x = -20.0f;
    attackPhysicsBodyComp.offset.y = -30.0f;
    attackPhysicsBodyComp.contactType = PhysicsBodyComponent::ContactType::Bullet;
    attackPhysicsBodyComp.category = colorPair->category;
    attackPhysicsBodyComp.hasGravity = false;
    TextureComponent& secondaryTextureComp = entity.addComponent<TextureComponent>();
    secondaryTextureComp.texture = m_texture;
    secondaryTextureComp.textureFrames = m_textureFrames;
    AnimatedSpriteComponent& secondarySpriteComp = entity.addComponent<AnimatedSpriteComponent>();
    secondarySpriteComp.spriteAnimationsAsset = m_spriteAnimations;
    secondarySpriteComp.animationName = "spr_wasp_idle_anim";
    secondarySpriteComp.colour = m_gameModeData.GetColorPair(player.player.id)->color;
    entity.addComponent<TimedLifeComponent>().timeLeftToKeepAlive = 4.0f;
    entity.activate();
}
