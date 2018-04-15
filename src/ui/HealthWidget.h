#pragma once

#include <SDL.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"

class HealthWidget
{
public:
    HealthWidget();

    void RenderRespawning(int x, int y, float time, SDL_Color color);
    void RenderLives(int x, int y, int lives, float health, SDL_Color color);
    void RenderTime(int x, int y, int kills, int deaths, float health, SDL_Color color);
    void RenderDead(int x, int y, SDL_Color color);
    void RenderScoreCard(int x, int y, int kills, int deaths, SDL_Color color);

private:
    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
    UILabel m_lives;
    UILabel m_health;
    UILabel m_time;
    FontAssetPtr m_font;
    FontAssetPtr m_fontLarge;
    UILabel m_dead;
};
