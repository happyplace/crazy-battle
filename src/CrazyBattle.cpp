#include "CrazyBattle.h"

CrazyBattle* CrazyBattle::ms_instance = nullptr;

CrazyBattle::CrazyBattle()
    : m_window(nullptr)
    , m_renderer(nullptr)
{
    ms_instance = this;
}

CrazyBattle::~CrazyBattle()
{
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

    bool quitGame = false;
    while (!quitGame)
    {
        SDL_PumpEvents();

        SDL_RenderClear(m_renderer);

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
