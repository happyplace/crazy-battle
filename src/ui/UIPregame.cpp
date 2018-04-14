#include "UIPregame.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "ui/UIRendererHelper.h"

UIPregame::UIPregame()
{
    m_font = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 65);
    m_texture = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");

    m_joinGame.SetText("Join Game");
    m_joinGame.SetFont(m_font);
    m_startGame.SetText("Start Game");
    m_startGame.SetFont(m_font);
}

void UIPregame::Render(GameModeData& gameModeData)
{
    if (gameModeData.IsGameRunning())
    {
        return;
    }

    m_joinGame.Render(100, 0);
    UIRendererHelper::RenderTextureFrame(20, 10, "start_button.png", m_texture, m_textureFrames, 2.0f, 2.0f);

    m_startGame.Render(100, 80);
    UIRendererHelper::RenderTextureFrame(20, 90, "back_button.png", m_texture, m_textureFrames, 2.0f, 2.0f);
}
