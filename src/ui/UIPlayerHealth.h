#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"
#include "GameModeData.h"

class UIPlayerHealth
{
public:
    UIPlayerHealth();
    ~UIPlayerHealth();

    void Render(GameModeData& gameModeData);

private:
    TTF_Font* m_font;
    UILabel m_label;

    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
    //SpriteAnimationsAssetPtr m_spriteAnimations;
};
