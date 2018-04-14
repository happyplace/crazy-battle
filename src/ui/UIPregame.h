#pragma once

#include <SDL.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"
#include "GameModeData.h"

class UIPregame
{
public:
    UIPregame();

    void Render(GameModeData& gameModeData);

private:
    FontAssetPtr m_font;
    UILabel m_joinGame;
    UILabel m_startGame;
    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
};
