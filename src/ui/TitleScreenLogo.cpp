#include "TitleScreenLogo.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "ui/UIRendererHelper.h"

TitleScreenLogo::TitleScreenLogo()
{
    const char* fontPath = "media/helmet2/Helmet-Regular.ttf";
    m_fontLarge = TTF_OpenFont(fontPath, 100);
    if (m_fontLarge == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "failed to load font '%s' SDL_ttf Error: %s", fontPath, TTF_GetError());
    }

    m_fontMedium = TTF_OpenFont(fontPath, 65);
    if (m_fontMedium == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "failed to load font '%s' SDL_ttf Error: %s", fontPath, TTF_GetError());
    }

    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");

    m_titleLabel.SetFont(m_fontLarge);
    m_titleLabel.SetText("Crazy Battle");

    m_startGame.SetFont(m_fontMedium);
    m_startGame.SetText("Start Game");

    m_controls.SetFont(m_fontMedium);
    m_controls.SetText("Controls");

    m_license.SetFont(m_fontMedium);
    m_license.SetText("License");

    m_mode.SetFont(m_fontMedium);
    m_modeParameter.SetFont(m_fontMedium);
}

TitleScreenLogo::~TitleScreenLogo()
{
    if (m_fontLarge)
    {
        TTF_CloseFont(m_fontLarge);
        m_fontLarge = nullptr;
    }

    if (m_fontMedium)
    {
        TTF_CloseFont(m_fontMedium);
        m_fontMedium = nullptr;
    }
}

void TitleScreenLogo::Render()
{
    m_titleLabel.Render(95, 200);
    UIRendererHelper::RenderTextureFrame(0, 0, "opp_promo_traveler.png", m_texture, m_textureFrames);

    int startGameX = 770;
    int startGameY = 530;
    m_startGame.Render(startGameX, startGameY);
    UIRendererHelper::RenderTextureFrame(startGameX - 73, startGameY + 15, "start_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_controls.Render(98, 385);
    UIRendererHelper::RenderTextureFrame(20, 400, "lb_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_license.Render(98, 470);
    UIRendererHelper::RenderTextureFrame(20, 485, "rb_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

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
}
