#include "TitleScreenLogo.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "ui/UIRendererHelper.h"

TitleScreenLogo::TitleScreenLogo()
{
    m_fontLarge = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 100);
    m_fontMedium = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 65);
    m_fontSmall = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 55);

    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");
    m_jungle = AssetLoaderHelper::LoadTexture("media/jungle_asset_pack/jungle_sprites.png");
    m_jungleFrames = AssetLoaderHelper::LoadTextureFrames("media/jungle_sprites.json");

    m_titleLabel.SetFont(m_fontLarge);
    m_titleLabel.SetText("Crazy Battle");
    m_titleLabel.SetTextColour( { 0xff, 0x52, 0x52, 0xff });

    m_startGame.SetFont(m_fontMedium);
    m_startGame.SetText("Start Game");

    m_controls.SetFont(m_fontMedium);
    m_controls.SetText("Controls");

    m_mode.SetFont(m_fontMedium);
    m_modeParameter.SetFont(m_fontMedium);

    m_changeMode.SetFont(m_fontSmall);
    m_changeMode.SetText("Change Mode");

    m_changeOption.SetFont(m_fontSmall);
    m_changeOption.SetText("Change Option");
}

void TitleScreenLogo::Render()
{
    float backgroundScale = 3.4f;
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-1.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-2.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-3.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-4.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-5.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);

    m_titleLabel.Render(95, 200);
    UIRendererHelper::RenderTextureFrame(0, 0, "opp_promo_traveler.png", m_texture, m_textureFrames);

    int startGameX = 900;
    int startGameY = 530;
    m_startGame.Render(startGameX, startGameY);
    UIRendererHelper::RenderTextureFrame(startGameX - 73, startGameY + 15, "start_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    int controlsX = 135;
    int controlsY = 530;
    m_controls.Render(controlsX, controlsY);
    UIRendererHelper::RenderTextureFrame(controlsX - 78, controlsY + 15, "lb_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_mode.SetText(GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time ? "Mode: Timed" : "Mode: Lives");
    m_mode.Render(1280 - m_mode.GetWidth() - 20, 0);
    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time)
    {
        std::string parameter = "Time: " + std::to_string(static_cast<int>(GameManager::GetInstance().GetRules().time));
        m_modeParameter.SetText(parameter);
    }
    else
    {
        std::string parameter = "Lives: " + std::to_string(GameManager::GetInstance().GetRules().lives);
        m_modeParameter.SetText(parameter);
    }
    m_modeParameter.Render(1280 - m_modeParameter.GetWidth() - 20, 80);

    m_changeMode.Render(1280 - m_changeOption.GetWidth() - 20, 200);
    UIRendererHelper::RenderTextureFrame(820, 200, "y_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_changeOption.Render(1280 - m_changeOption.GetWidth() - 20, 280);
    UIRendererHelper::RenderTextureFrame(820, 280, "x_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);
}
