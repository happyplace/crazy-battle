#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "components/PhysicsBodyComponent.h"
#include "components/TransformComponent.h"
#include "AssetLoaderDefines.h"
#include "GameModeData.h"

class GameTimer;

class PlayerAttackInputSystem : public anax::System<anax::Requires<PlayerComponent, PhysicsBodyComponent, TransformComponent>>
{
public:
    explicit PlayerAttackInputSystem(GameModeData& gameDataMode);

    void Update(const GameTimer& gameTimer);

private:
    void LinearAttack(const TransformComponent& transform, const PlayerComponent& player) const;

    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
    SpriteAnimationsAssetPtr m_spriteAnimations;
    GameModeData& m_gameModeData;
};
