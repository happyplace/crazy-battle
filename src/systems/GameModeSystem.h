#pragma once

#include <unordered_map>

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "AssetLoaderDefines.h"

class GameTimer;
class GameModeData;

class GameModeSystem : public anax::System<anax::Requires<PlayerComponent>>
{
public:
    explicit GameModeSystem(GameModeData& gameModeData);

    void Update(const GameTimer& gameTimer);

private:
    void onEntityAdded(anax::Entity& entity) override;
    void onEntityRemoved(anax::Entity& entity) override;

    void ShowPlayer(anax::Entity& entity);
    void HidePlayer(anax::Entity& entity);
    void MovePlayerToSpawnPoint(anax::Entity& entity);
    void PlayDeathAnimation(anax::Entity& entity);

    typedef std::unordered_map<uint64_t, anax::Entity> EntityMap;
    EntityMap m_playerEntities;
    GameModeData& m_gameModeData;

    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
    SpriteAnimationsAssetPtr m_animations;
};
