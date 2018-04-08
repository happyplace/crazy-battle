#include "GameState.h"

#include "AssetLoaderHelper.h"
#include "GameTimer.h"
#include "InputManager.h"

void GameState::Init()
{
    m_world.addSystem<PlayerMovementSystem>(m_playerMovementSystem);
    m_world.addSystem<SpriteRendererSystem>(m_spriteRendererSystem);
    m_world.addSystem<AnimateSpriteUpdateSystem>(m_animateSpriteUpdateSystem);
    m_world.addSystem<AnimateSpriteRendererSystem>(m_animateSpriteRendererSystem);

    anax::Entity player = m_world.createEntity();
    TransformComponent& playerTransformComp = player.addComponent<TransformComponent>();
    playerTransformComp.scale.x = 5.0f;
    playerTransformComp.scale.y = 5.0f;
    AnimatedSpriteComponent& playerAnimatedSpriteComp = player.addComponent<AnimatedSpriteComponent>();
    playerAnimatedSpriteComp.animationName = "spr_m_traveler_idle_anim";
    playerAnimatedSpriteComp.spriteAnimationsAsset = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");
    TextureComponent& playerTextureComp = player.addComponent<TextureComponent>();
    playerTextureComp.texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    playerTextureComp.textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    std::vector<SDL_JoystickID> joystickIds;
    InputManager::GetInstance().GetAllControllerInstanceIds(joystickIds);
    player.addComponent<PlayerComponent>().controllerInstanceId = joystickIds.empty() ? -1 : joystickIds[0];

    player.activate();
}

void GameState::DoUpdate(const GameTimer& gameTimer)
{
    m_world.refresh();

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
