#include "GameState.h"

#include "AssetLoaderHelper.h"
#include "GameTimer.h"
#include "InputManager.h"

GameState::GameState()
    : accumulator(0.0)
    , m_playerEntitySpawnerSystem(m_gameModeData)
    , m_gameModeSystem(m_gameModeData)
    , m_playerDamageSystem(m_gameModeData)
    , m_playerAttackInputSystem(m_gameModeData)
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
    m_world.addSystem<ChildTransformSystem>(m_childTransformSystem);
    m_world.addSystem<TimedLifeSystem>(m_timedLifeSystem);
    m_world.addSystem<GameModeSystem>(m_gameModeSystem);
    m_world.addSystem<PlayerDamageSystem>(m_playerDamageSystem);
    m_world.addSystem<GameBackgroundSystem>(m_gameBackgroundSystem);
    m_world.addSystem<UIPlayerHealthSystem>(m_uiPlayerHealthSystem);
    m_world.addSystem<SineAttackSystem>(m_sineAttackSystem);

    m_gameLevelLoader.LoadLevel(m_world, "media/game_level.json");
}

void GameState::DoUpdate(const GameTimer& gameTimer)
{
    m_world.refresh();
    m_gameModeData.Update(gameTimer);

    m_playerEntitySpawnerSystem.Update();
    m_world.refresh();

    const double PhysicsTimeStep = 1.0/60.0;
    accumulator += gameTimer.DeltaTime();
    while (accumulator >= PhysicsTimeStep)
    {
        m_physicsWorldSystem.Integrate(PhysicsTimeStep);
        m_world.refresh();
        accumulator -= PhysicsTimeStep;
    }

    m_playerDamageSystem.Update(gameTimer);
    m_world.refresh();

    m_gameModeSystem.Update(gameTimer);
    m_world.refresh();
    m_playerMovementSystem.Update(gameTimer);
    m_world.refresh();
    m_playerAttackInputSystem.Update(gameTimer);
    m_world.refresh();
    m_linearAttackSystem.Update(gameTimer);
    m_world.refresh();
    m_sineAttackSystem.Update(gameTimer);
    m_world.refresh();
    m_playerAnimationSystem.Update(gameTimer);
    m_world.refresh();
    m_animateSpriteUpdateSystem.Update(gameTimer);
    m_world.refresh();
    m_timedLifeSystem.Update(gameTimer);
    m_world.refresh();
    m_childTransformSystem.Update();
    m_world.refresh();
}

void GameState::Render()
{
    m_gameBackgroundSystem.Render();
    m_world.refresh();
    m_spriteRendererSystem.Render();
    m_world.refresh();
    m_animateSpriteRendererSystem.Render();
    m_world.refresh();

    m_uiPlayerHealthSystem.Render(m_gameModeData);
    m_world.refresh();
    m_uiPregame.Render(m_gameModeData);
    m_world.refresh();
}

void GameState::Shutdown()
{
}
