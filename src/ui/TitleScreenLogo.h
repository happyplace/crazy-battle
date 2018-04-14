#pragma once

#include <SDL.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"

class GameTimer;

class TitleScreenLogo
{
public:
    TitleScreenLogo();

    void Render();

private:
    FontAssetPtr m_fontLarge;
    FontAssetPtr m_fontMedium;
    FontAssetPtr m_fontSmall;

    UILabel m_titleLabel;
    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;

    UILabel m_startGame;
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;

    UILabel m_controls;

    UILabel m_mode;
    UILabel m_modeParameter;

    UILabel m_changeMode;
    UILabel m_changeOption;

    TextureAssetPtr m_jungle;
    TextureFramesAssetPtr m_jungleFrames;
};
