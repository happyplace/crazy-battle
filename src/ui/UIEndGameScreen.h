#pragma once

#include <SDL.h>
#include <vector>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"
#include "ui/TitleScreenLogo.h"
#include "ui/HealthWidget.h"

class GameTimer;

class UIEndGameScreen
{
public:
    struct ScoreCard
    {
        SDL_Color color;
        int kills;
        int deaths;
    };

    static SDL_Color ms_winnerColor;
    static std::vector<ScoreCard> ms_scoreCards;

    UIEndGameScreen();

    void Update(const GameTimer& gameTimer);
    void Render();

private:
    FontAssetPtr m_fontSmall;
    UILabel m_winner;
    TextureAssetPtr m_texture;
    TextureFramesAssetPtr m_textureFrames;
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;
    UILabel m_titleScreen;
    UILabel m_playAgain;
    TextureAssetPtr m_jungle;
    TextureFramesAssetPtr m_jungleFrames;
    HealthWidget m_healthWidget;
};
