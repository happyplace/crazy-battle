#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"
#include "AssetLoaderDefines.h"

class GameBackgroundSystem : public anax::System<anax::Requires<PlayerComponent>>
{
public:
    GameBackgroundSystem();

    void Render();

private:
    TextureAssetPtr m_jungle;
    TextureFramesAssetPtr m_jungleFrames;
};
