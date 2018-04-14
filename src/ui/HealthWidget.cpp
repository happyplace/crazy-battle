#include "HealthWidget.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "ui/UIRendererHelper.h"
#include "math.h"

HealthWidget::HealthWidget()
{
    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");

    m_font = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 50);
    m_fontLarge = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 75);

    m_lives.SetFont(m_font);
    m_health.SetFont(m_font);
    m_time.SetFont(m_font);
}

void HealthWidget::RenderLives(int x, int y, int lives, float health, SDL_Color color)
{
    UIRendererHelper::RenderTextureFrame(x, y, "icon_traveler.png", m_texture, m_textureFrames, 4.0f, 4.0f, color);
    UIRendererHelper::RenderTextureFrame(x + 75, y + 5, "icon_traveler.png", m_texture, m_textureFrames, 2.0f, 2.0f);
    m_lives.SetText("x " + std::to_string(lives));
    m_lives.Render(x + 115, y - 10);
    m_health.SetText("HP: " + std::to_string(static_cast<int>(floor(health))));
    m_health.Render(x + 75, y + 30);
}

void HealthWidget::RenderRespawning(int x, int y, float time, SDL_Color color)
{
    UIRendererHelper::RenderTextureFrame(x, y, "icon_traveler.png", m_texture, m_textureFrames, 4.0f, 4.0f, color);
    m_time.SetText("Time: " + std::to_string(static_cast<int>(floor(time))));
    m_time.Render(x + 70, y + 0);
}

void HealthWidget::RenderTime(int x, int y, int kills, int deaths, float health, SDL_Color color)
{
    UIRendererHelper::RenderTextureFrame(x, y, "icon_traveler.png", m_texture, m_textureFrames, 4.0f, 4.0f, color);
    m_lives.SetText("K: " + std::to_string(kills) + "  D: " + std::to_string(deaths));
    m_lives.Render(x + 75, y - 10);
    m_health.SetText("HP: " + std::to_string(static_cast<int>(floor(health))));
    m_health.Render(x + 75, y + 30);
}
