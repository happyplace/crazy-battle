#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "AssetLoaderDefines.h"
#include "GameModeData.h"

struct PlayerStruct;

class PlayerEntitySpawnerSystem : public anax::System<anax::Requires<PlayerComponent>>
{
public:
	explicit PlayerEntitySpawnerSystem(GameModeData& gameModeData);

	void Update();

private:
	void Init();
	void CreatePlayer(const PlayerStruct& player);
    void onEntityAdded(anax::Entity& entity) override;
    void onEntityRemoved(anax::Entity& entity) override;

	GameModeData& m_gameModeData;
	bool m_initSystem;
	TextureAssetPtr m_playerTexture;
	TextureFramesAssetPtr m_playerFrames;
	SpriteAnimationsAssetPtr m_playerAnimations;
};
