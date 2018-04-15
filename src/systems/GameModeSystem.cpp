#include "GameModeSystem.h"

#include "anax/World.hpp"

#include "CrazyBattle.h"
#include "GameTimer.h"
#include "GameModeData.h"
#include "GameManager.h"
#include "components/TransformComponent.h"
#include "components/AnimatedSpriteComponent.h"
#include "components/PhysicsBodyComponent.h"
#include "components/TextureComponent.h"
#include "components/TimedLifeComponent.h"
#include "AssetLoaderHelper.h"

GameModeSystem::GameModeSystem(GameModeData& gameModeData)
    : m_gameModeData(gameModeData)
{
    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    m_animations = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");
}

void GameModeSystem::onEntityAdded(anax::Entity &entity)
{
    const PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
    m_playerEntities[playerComp.player.id] = entity;
}

void GameModeSystem::onEntityRemoved(anax::Entity &entity)
{
    const PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
    m_playerEntities.erase(playerComp.player.id);
}

void GameModeSystem::ShowPlayer(anax::Entity &entity)
{
    entity.getComponent<AnimatedSpriteComponent>().enabled = true;
    PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
    physicsBodyComp.params.body->SetActive(true);
}

void GameModeSystem::HidePlayer(anax::Entity &entity)
{
    entity.getComponent<AnimatedSpriteComponent>().enabled = false;
    PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
    physicsBodyComp.params.body->SetActive(false);
}

void GameModeSystem::MovePlayerToSpawnPoint(anax::Entity &entity)
{
    float spawnX = 300.0f;
    float spawnY = 0.0f;

    PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
    physicsBodyComp.SetPosition(spawnX, spawnY);
    TransformComponent& transformComp = entity.getComponent<TransformComponent>();
    transformComp.position.x = spawnX;
    transformComp.position.y = spawnY;
}

void GameModeSystem::Update(const GameTimer& gameTimer)
{
    for (HealthPair& healthPair : m_gameModeData.GetHealth())
    {
        anax::Entity& entity = m_playerEntities[healthPair.playerId];
        if (!entity.isValid())
        {
            continue;
        }

        PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
        switch (playerComp.state)
        {
        case PlayerComponent::State::Idle:
            if (healthPair.health.health <= 0.0f)
            {
                if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Lives)
                {
                    healthPair.health.lives--;
                    if (healthPair.health.lives < 0)
                    {
                        playerComp.state = PlayerComponent::State::Dead;
                        PlayDeathAnimation(entity);
                    }
                    else
                    {
                        playerComp.state = PlayerComponent::State::Respawning;
                        healthPair.health.deathTimer = GameManager::GetInstance().GetRules().deathTime;
                        PlayDeathAnimation(entity);
                    }
                }
                else
                {
                    playerComp.state = PlayerComponent::State::Respawning;
                    healthPair.health.deathTimer = GameManager::GetInstance().GetRules().deathTime;
                }
            }
            break;
        case PlayerComponent::State::Respawning:
            healthPair.health.deathTimer -= static_cast<float>(gameTimer.DeltaTime());
            if (healthPair.health.deathTimer <= 0.0f)
            {
                playerComp.state = PlayerComponent::State::Idle;
                healthPair.health.health = GameManager::GetInstance().GetRules().health;
                MovePlayerToSpawnPoint(entity);
            }
            break;
        case PlayerComponent::State::Dead:
            break;
        }

        if (playerComp.state == PlayerComponent::State::Idle)
        {
            ShowPlayer(entity);
        }
        else
        {
            HidePlayer(entity);
        }
    }

    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time && m_gameModeData.IsGameRunning())
    {
        if (m_gameModeData.GetTimeLeft() <= 0.0f)
        {
            CrazyBattle::Game().ChangeState(CrazyBattleState::GameEndState);
        }
    }
}

void GameModeSystem::PlayDeathAnimation(anax::Entity &entity)
{
    TransformComponent& transformComp = entity.getComponent<TransformComponent>();

    anax::Entity deathEntity = getWorld().createEntity();
    TransformComponent& deathTransformComp = deathEntity.addComponent<TransformComponent>();
    deathTransformComp.position = transformComp.position;
    deathTransformComp.scale.x = 3.0f;
    deathTransformComp.scale.y = 3.0f;
    TextureComponent& bulletHitTextureComp = deathEntity.addComponent<TextureComponent>();
    bulletHitTextureComp.texture = m_texture;
    bulletHitTextureComp.textureFrames = m_textureFrames;
    AnimatedSpriteComponent& deathAnimatedSpriteComp = deathEntity.addComponent<AnimatedSpriteComponent>();
    deathAnimatedSpriteComp.spriteAnimationsAsset = m_animations;
    deathAnimatedSpriteComp.animationName = "fx_explosion_r_anim";
    deathEntity.addComponent<TimedLifeComponent>().timeLeftToKeepAlive = 0.45f;
    deathEntity.activate();
}
