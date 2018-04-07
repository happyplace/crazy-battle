#include "CrazyBattle.h"

#include <SDL_image.h>
#include "AssetLoaderHelper.h"

CrazyBattle* CrazyBattle::ms_instance = nullptr;

CrazyBattle::CrazyBattle()
    : m_window(nullptr)
    , m_renderer(nullptr)
{
    ms_instance = this;

    m_font = nullptr;
    m_fontTexture = nullptr;
    m_fontTextureW = 0;
    m_fontTextureH = 0;
}

CrazyBattle::~CrazyBattle()
{
    if (m_fontTexture)
    {
        SDL_DestroyTexture(m_fontTexture);
        m_fontTexture = nullptr;
    }

    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    ms_instance = nullptr;
}

bool CrazyBattle::Init(int /*argc*/, char* /*argv*/[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL could not initalize! SDL_ERROR: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("Crazy Battle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "window could not be created SDL_ERROR: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL Error: %s", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize SDL_image Error: %s", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_ttf could not initialize SDL_ttf Error: %s", TTF_GetError());
        return false;
    }

    return true;
}

int CrazyBattle::Run(int argc, char* argv[])
{
    if (!Init(argc, argv))
    {
        return 1;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Linear texture filtering not enabled");
    }

    SDL_SetRenderDrawColor(m_renderer, 0xb1, 0xc5, 0xdf, 0xff);

    const char* fontPath = "media/helmet2/Helmet-Regular.ttf";
    m_font = TTF_OpenFont(fontPath, 100);
    if (m_font == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "failed to load font '%s' SDL_ttf Error: %s", fontPath, TTF_GetError());
    }
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, "Andrew was here!", textColor);
    if (textSurface == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "unable to render text surface SDL_ttf Error: %s", TTF_GetError());
    }
    else
    {
        m_fontTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        if (m_fontTexture == nullptr)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from rendered text. SDL Error: %s", SDL_GetError());
        }
        m_fontTextureW = textSurface->w;
        m_fontTextureH = textSurface->h;
        SDL_FreeSurface(textSurface);
    }

    m_world.addSystem<PlayerMovementSystem>(m_playerMovementSystem);
    m_world.addSystem<SpriteRendererSystem>(m_spriteRendererSystem);

    anax::Entity player = m_world.createEntity();
    TransformComponent& playerTransformComp = player.addComponent<TransformComponent>();
    playerTransformComp.scale.x = 5.0f;
    playerTransformComp.scale.y = 5.0f;
    player.addComponent<SpriteComponent>();
    player.addComponent<TextureComponent>().texture = AssetLoaderHelper::LoadTexture("media/opp2/test2.png");
    player.activate();

    bool quitGame = false;
    while (!quitGame)
    {
        SDL_PumpEvents();

        SDL_RenderClear(m_renderer);

        m_world.refresh();

        m_playerMovementSystem.Update();

        m_spriteRendererSystem.Render();

        SDL_Rect renderQuad;
        renderQuad.x = 0;
        renderQuad.y = 0;
        renderQuad.w = m_fontTextureW;
        renderQuad.h = m_fontTextureH;
        SDL_RenderCopy(m_renderer, m_fontTexture, nullptr, &renderQuad);

        SDL_RenderPresent(m_renderer);

        const int numOfEventsPerPeek = 100;
        SDL_Event sdlEvents[numOfEventsPerPeek];

        // Using SDL_GETEVENT to remove all the events
        const int numOfEvents = SDL_PeepEvents(sdlEvents, numOfEventsPerPeek, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
        if (numOfEvents < 0)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_PeepEvents failed SDL_ERROR: %s", SDL_GetError());
        }

        for (int i = 0; i < numOfEvents; i++)
        {
            if (sdlEvents[i].type == SDL_QUIT)
            {
                quitGame = true;
            }
        }
    }

    return 0;
}
