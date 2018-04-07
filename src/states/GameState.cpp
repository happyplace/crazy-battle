#include "GameState.h"

#include "AssetLoaderHelper.h"
#include "GameTimer.h"
#include "InputManager.h"

void GameState::Init()
{
    m_world.addSystem<PlayerMovementSystem>(m_playerMovementSystem);
    m_world.addSystem<SpriteRendererSystem>(m_spriteRendererSystem);

    anax::Entity player = m_world.createEntity();
    TransformComponent& playerTransformComp = player.addComponent<TransformComponent>();
    playerTransformComp.scale.x = 5.0f;
    playerTransformComp.scale.y = 5.0f;
    player.addComponent<SpriteComponent>();
    player.addComponent<TextureComponent>().texture = AssetLoaderHelper::LoadTexture("media/opp2/test.png");
    std::vector<SDL_JoystickID> joystickIds;
    InputManager::GetInstance().GetAllControllerInstanceIds(joystickIds);
    player.addComponent<PlayerComponent>().controllerInstanceId = joystickIds.empty() ? -1 : joystickIds[0];
    player.activate();
}

void GameState::DoUpdate(const GameTimer& gameTimer)
{
    m_world.refresh();

    m_playerMovementSystem.Update(gameTimer);
}

void GameState::Render()
{
    m_spriteRendererSystem.Render();
}

void GameState::Shutdown()
{
}
