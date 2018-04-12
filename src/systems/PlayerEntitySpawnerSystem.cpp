#include "PlayerEntitySpawnerSystem.h"

#include "anax/World.hpp"

#include "GameManager.h"
#include "AssetLoaderHelper.h"
#include "components/TransformComponent.h"
#include "components/AnimatedSpriteComponent.h"
#include "components/TextureComponent.h"
#include "components/PhysicsBodyComponent.h"

PlayerEntitySpawnerSystem::PlayerEntitySpawnerSystem(GameModeData& gameModeData)
	: m_gameModeData(gameModeData)
	, m_initSystem(false)
{
}

void PlayerEntitySpawnerSystem::Init()
{
	m_playerTexture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
	m_playerFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
	m_playerAnimations = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");
}

void PlayerEntitySpawnerSystem::CreatePlayer(const PlayerStruct& player)
{
	anax::Entity playerEntity = getWorld().createEntity();
    
    TransformComponent& transformComp = playerEntity.addComponent<TransformComponent>();
    transformComp.position.x = 300.0f;
    transformComp.scale.x = 2.0f;
    transformComp.scale.y = 2.0f;

    AnimatedSpriteComponent& animatedSpriteComp = playerEntity.addComponent<AnimatedSpriteComponent>();
    animatedSpriteComp.spriteAnimationsAsset = m_playerAnimations;

    TextureComponent& textureComp = playerEntity.addComponent<TextureComponent>();
    textureComp.texture = m_playerTexture;
    textureComp.textureFrames = m_playerFrames;

    PlayerComponent& playerComp = playerEntity.addComponent<PlayerComponent>();
    playerComp.player = player;

    PhysicsBodyComponent& physicsBodyComp = playerEntity.addComponent<PhysicsBodyComponent>();
    physicsBodyComp.isStatic = false;
    physicsBodyComp.size = b2Vec2(37.0f, 57.0f);
    physicsBodyComp.hasGravity = true;
    physicsBodyComp.offset = b2Vec2(-25.0f, -13.0f);
    physicsBodyComp.groupIndex = 0;
    physicsBodyComp.isBullet = true;
    physicsBodyComp.canRotate = false;
    physicsBodyComp.bodyType = PhysicsBodyComponent::BodyType::Box;
    physicsBodyComp.contactType = PhysicsBodyComponent::ContactType::Player;

    playerEntity.activate();
}

void PlayerEntitySpawnerSystem::Update()
{
	if (!m_initSystem)
	{
		Init();
		m_initSystem = true;
	}

	const std::vector<PlayerStruct>& players = GameManager::GetInstance().GetPlayers();
	for (const PlayerStruct& player : players)
	{
		bool playerHasEntity = false;
		for (const anax::Entity entity : getEntities())
		{
			if (entity.getComponent<PlayerComponent>().player.id == player.id)
			{
				playerHasEntity = true;
				break;
			}
		}
		if (!playerHasEntity)
		{
			CreatePlayer(player);
		}
	}

    for (anax::Entity entity : getEntities())
	{
		PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
		const PlayerStruct* player = GameManager::GetInstance().GetPlayer(playerComp.player.id);
		if (player == nullptr)
		{
            entity.kill();
		}
		else
		{
            playerComp.player.controllerInstanceId = player->controllerInstanceId;
		}
	}
}

void PlayerEntitySpawnerSystem::onEntityAdded(anax::Entity& entity)
{
	m_gameModeData.PlayerAdded(entity.getComponent<PlayerComponent>().player.id);
}

void PlayerEntitySpawnerSystem::onEntityRemoved(anax::Entity& entity)
{
	m_gameModeData.PlayerRemoved(entity.getComponent<PlayerComponent>().player.id);
}
