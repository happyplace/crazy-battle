#include "GameState.h"

#include "AssetLoaderHelper.h"
#include "GameTimer.h"
#include "InputManager.h"

GameState::GameState()
    : accumulator(0.0)
{
}

void GameState::Init()
{
    m_world.addSystem<PlayerMovementSystem>(m_playerMovementSystem);
    m_world.addSystem<SpriteRendererSystem>(m_spriteRendererSystem);
    m_world.addSystem<AnimateSpriteUpdateSystem>(m_animateSpriteUpdateSystem);
    m_world.addSystem<AnimateSpriteRendererSystem>(m_animateSpriteRendererSystem);
    m_world.addSystem<PhysicsWorldSystem>(m_physicsWorldSystem);

    anax::Entity player = m_world.createEntity();
    TransformComponent& playerTransformComp = player.addComponent<TransformComponent>();
    playerTransformComp.scale.x = 2.0f;
    playerTransformComp.scale.y = 2.0f;
    AnimatedSpriteComponent& playerAnimatedSpriteComp = player.addComponent<AnimatedSpriteComponent>();
    playerAnimatedSpriteComp.animationName = "spr_m_traveler_idle_anim";
    playerAnimatedSpriteComp.spriteAnimationsAsset = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");
    TextureComponent& playerTextureComp = player.addComponent<TextureComponent>();
    playerTextureComp.texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    playerTextureComp.textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    std::vector<SDL_JoystickID> joystickIds;
    InputManager::GetInstance().GetAllControllerInstanceIds(joystickIds);
    player.addComponent<PlayerComponent>().player.controllerInstanceId = joystickIds.empty() ? -1 : joystickIds[0];
    PhysicsBodyComponent& playerPhysicsBodyComp = player.addComponent<PhysicsBodyComponent>();
    playerPhysicsBodyComp.isStatic = false;
    playerPhysicsBodyComp.size = b2Vec2(64.0f, 64.0f);
    playerPhysicsBodyComp.hasGravity = true;
    playerPhysicsBodyComp.offset = b2Vec2_zero;
    playerPhysicsBodyComp.groupIndex = 0;
    playerPhysicsBodyComp.isBullet = true;
    playerPhysicsBodyComp.canRotate = false;
    playerPhysicsBodyComp.bodyType = PhysicsBodyComponent::BodyType::Box;
    player.activate();

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

    const double PhysicsTimeStep = 1.0/60.0;
    accumulator += gameTimer.DeltaTime();
    while (accumulator >= PhysicsTimeStep)
    {
        m_physicsWorldSystem.Integrate(PhysicsTimeStep);
        accumulator -= PhysicsTimeStep;
    }

    m_playerMovementSystem.Update(gameTimer);
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
