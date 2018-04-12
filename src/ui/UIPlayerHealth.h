#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"

class UIPlayerHealth
{
public:
    UIPlayerHealth();
    ~UIPlayerHealth();

    void Render();

private:
    TTF_Font* m_font;
    UILabel m_label;

    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
    //SpriteAnimationsAssetPtr m_spriteAnimations;
};
