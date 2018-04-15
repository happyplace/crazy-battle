#include "UIEndGameScreen.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "GameTimer.h"
#include "ui/UIRendererHelper.h"

SDL_Color UIEndGameScreen::ms_winnerColor = { 0xff, 0xff, 0xff, 0xff };
std::vector<UIEndGameScreen::ScoreCard> UIEndGameScreen::ms_scoreCards;

UIEndGameScreen::UIEndGameScreen()
{
//    m_fontLarge = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 100);
//    m_fontMedium = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 65);
    m_fontSmall = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 55);

    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");
    m_jungle = AssetLoaderHelper::LoadTexture("media/jungle_asset_pack/jungle_sprites.png");
    m_jungleFrames = AssetLoaderHelper::LoadTextureFrames("media/jungle_sprites.json");

    m_titleScreen.SetFont(m_fontSmall);
    m_titleScreen.SetText("Title Screen");

    m_playAgain.SetFont(m_fontSmall);
    m_playAgain.SetText("Play Again");

    m_winner.SetFont(m_fontSmall);
    m_winner.SetText("- Winner -");
}

void UIEndGameScreen::Update(const GameTimer& gameTimer)
{
    float dt = static_cast<float>(gameTimer.DeltaTime());
    TitleScreenLogo::ms_layer2 += dt / 80.0f;
    if (TitleScreenLogo::ms_layer2 > 1.0f)
    {
        TitleScreenLogo::ms_layer2 = 0.0f;
    }

    TitleScreenLogo::ms_layer3 += dt / 60.0f;
    if (TitleScreenLogo::ms_layer3 > 1.0f)
    {
        TitleScreenLogo::ms_layer3 = 0.0f;
    }

    TitleScreenLogo::ms_layer4 += dt / 40.0f;
    if (TitleScreenLogo::ms_layer4 > 1.0f)
    {
        TitleScreenLogo::ms_layer4 = 0.0f;
    }

    TitleScreenLogo::ms_layer5 += dt / 20.0f;
    if (TitleScreenLogo::ms_layer5 > 1.0f)
    {
        TitleScreenLogo::ms_layer5 = 0.0f;
    }
}

void UIEndGameScreen::Render()
{
    const float backgroundScale = 3.4f;
    const int width = static_cast<int>(384 * backgroundScale);

    UIRendererHelper::RenderTextureFrame(0, 0, "plx-1.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);

    UIRendererHelper::RenderTextureFrame(width * TitleScreenLogo::ms_layer2, 0, "plx-2.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(width * (TitleScreenLogo::ms_layer2 - 1), 0, "plx-2.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);

    UIRendererHelper::RenderTextureFrame(width * TitleScreenLogo::ms_layer3, 0, "plx-3.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(width * (TitleScreenLogo::ms_layer3 - 1), 0, "plx-3.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);

    UIRendererHelper::RenderTextureFrame(width * TitleScreenLogo::ms_layer4, 0, "plx-4.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(width * (TitleScreenLogo::ms_layer4 - 1), 0, "plx-4.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);

    UIRendererHelper::RenderTextureFrame(width * TitleScreenLogo::ms_layer5, 0, "plx-5.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(width * (TitleScreenLogo::ms_layer5 - 1), 0, "plx-5.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);

    UIRendererHelper::RenderTextureFrame(40, 600, "back_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);
    m_titleScreen.Render(120, 590);

    UIRendererHelper::RenderTextureFrame(900, 600, "start_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);
    m_playAgain.Render(980, 590);

    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Lives)
    {
        m_winner.Render((1280 / 2.0f) - (m_winner.GetWidth() / 2.0f), 100);
        int width = 10 * 16;
        UIRendererHelper::RenderTextureFrame((1280 / 2.0f) - (width / 2.0f), (720 / 2.0f) - (width / 2.0f),
                                             "icon_traveler.png", m_texture, m_textureFrames, 10.0f, 10.0f,
                                             ms_winnerColor);
    }
    else
    {
        const int yCoord[] = { 50, 190, 325, 450 };
        for (std::size_t i = 0; i < ms_scoreCards.size(); i++)
        {
            m_healthWidget.RenderScoreCard(490, yCoord[i], ms_scoreCards[i].kills, ms_scoreCards[i].deaths, ms_scoreCards[i].color);
        }
    }
}
