#include "GameModeSystem.h"

#include "CrazyBattle.h"
#include "GameTimer.h"
#include "GameModeData.h"
#include "GameManager.h"
#include "components/TransformComponent.h"
#include "components/AnimatedSpriteComponent.h"
#include "components/PhysicsBodyComponent.h"

GameModeSystem::GameModeSystem(GameModeData& gameModeData)
    : m_gameModeData(gameModeData)
{
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
    PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
    physicsBodyComp.SetPosition(300.0f, 0.0f);
}

void GameModeSystem::Update(const GameTimer& gameTimer)
{
    for (HealthPair& healthPair : m_gameModeData.GetHealth())
    {
        anax::Entity& entity = m_playerEntities[healthPair.playerId];
        switch (healthPair.health.state)
        {
        case GameHealth::State::Idle:
            if (healthPair.health.health <= 0.0f)
            {
                if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Lives)
                {
                    healthPair.health.lives--;
                    if (healthPair.health.lives < 0)
                    {
                        healthPair.health.state = GameHealth::State::Dead;
                    }
                    else
                    {
                        healthPair.health.state = GameHealth::State::Respawning;
                        healthPair.health.deathTimer = GameManager::GetInstance().GetRules().deathTime;
                    }
                }
                else
                {
                    healthPair.health.state = GameHealth::State::Respawning;
                    healthPair.health.deathTimer = GameManager::GetInstance().GetRules().deathTime;
                }
            }
            break;
        case GameHealth::State::Respawning:
            healthPair.health.deathTimer -= static_cast<float>(gameTimer.DeltaTime());
            if (healthPair.health.deathTimer <= 0.0f)
            {
                healthPair.health.state = GameHealth::State::Idle;
                healthPair.health.health = GameManager::GetInstance().GetRules().health;
                MovePlayerToSpawnPoint(entity);
            }
            break;
        case GameHealth::State::Dead:
            break;
        }

        if (healthPair.health.state == GameHealth::State::Idle)
        {
            ShowPlayer(entity);
        }
        else
        {
            HidePlayer(entity);
        }
    }

    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time)
    {
        if (m_gameModeData.GetTimeLeft() <= 0.0f)
        {
            CrazyBattle::Game().ChangeState(CrazyBattleState::GameEndState);
        }
    }
}
