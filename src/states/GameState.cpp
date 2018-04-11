#include "GameState.h"

#include "AssetLoaderHelper.h"
#include "GameTimer.h"
#include "InputManager.h"

GameState::GameState()
    : accumulator(0.0)
    , m_playerEntitySpawnerSystem(m_gameModeData)
{
}

void GameState::Init()
{
    m_world.addSystem<PlayerMovementSystem>(m_playerMovementSystem);
    m_world.addSystem<SpriteRendererSystem>(m_spriteRendererSystem);
    m_world.addSystem<AnimateSpriteUpdateSystem>(m_animateSpriteUpdateSystem);
    m_world.addSystem<AnimateSpriteRendererSystem>(m_animateSpriteRendererSystem);
    m_world.addSystem<PhysicsWorldSystem>(m_physicsWorldSystem);
    m_world.addSystem<PlayerEntitySpawnerSystem>(m_playerEntitySpawnerSystem);
    m_world.addSystem<PlayerAnimationSystem>(m_playerAnimationSystem);
    m_world.addSystem<PlayerAttackInputSystem>(m_playerAttackInputSystem);
    m_world.addSystem<LinearAttackSystem>(m_linearAttackSystem);

    m_gameLevelLoader.LoadLevel(m_world, "media/game_level.json");
}

void GameState::DoUpdate(const GameTimer& gameTimer)
{
    m_world.refresh();

    m_playerEntitySpawnerSystem.Update();

    const double PhysicsTimeStep = 1.0/60.0;
    accumulator += gameTimer.DeltaTime();
    while (accumulator >= PhysicsTimeStep)
    {
        m_physicsWorldSystem.Integrate(PhysicsTimeStep);
        accumulator -= PhysicsTimeStep;
    }

    m_playerMovementSystem.Update(gameTimer);
    m_playerAttackInputSystem.Update(gameTimer);
    m_linearAttackSystem.Update(gameTimer);
    m_playerAnimationSystem.Update(gameTimer);
    m_animateSpriteUpdateSystem.Update(gameTimer);
}

void GameState::Render()
{
    m_spriteRendererSystem.Render();
    m_animateSpriteRendererSystem.Render();
}

void GameState::Shutdown()
{
}
