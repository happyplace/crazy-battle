#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"

class TitleScreenLogo
{
public:
    TitleScreenLogo();
    ~TitleScreenLogo();

    void Render();

private:
    TTF_Font* m_fontLarge;
    TTF_Font* m_fontMedium;

    UILabel m_titleLabel;
    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;

    UILabel m_startGame;
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;

    UILabel m_controls;
    UILabel m_license;

    UILabel m_mode;
    UILabel m_modeParameter;
};
