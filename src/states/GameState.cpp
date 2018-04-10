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

    anax::Entity floor = m_world.createEntity();
    TransformComponent& floorTransformComp = floor.addComponent<TransformComponent>();
    floorTransformComp.position.x = 0.0f;
    floorTransformComp.position.y = 600.0f;
    PhysicsBodyComponent& floorPhysicsBodyComp = floor.addComponent<PhysicsBodyComponent>();
    floorPhysicsBodyComp.isStatic = true;
    floorPhysicsBodyComp.size = b2Vec2(600.0f, 64.0f);
    floorPhysicsBodyComp.hasGravity = false;
    floorPhysicsBodyComp.offset = b2Vec2_zero;
    floorPhysicsBodyComp.groupIndex = 0;
    floorPhysicsBodyComp.isBullet = false;
    floorPhysicsBodyComp.canRotate = false;
    floorPhysicsBodyComp.bodyType = PhysicsBodyComponent::BodyType::Box;
    floor.activate();
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
