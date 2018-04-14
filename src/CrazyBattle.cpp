#include "CrazyBattle.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameTimer.h"
#include "states/GameState.h"
#include "states/MainMenuState.h"
#include "states/GameEndState.h"

CrazyBattle* CrazyBattle::ms_instance = nullptr;
const int CrazyBattle::NumOfEventsPerPeek = 100;

CrazyBattle::CrazyBattle()
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_currentState(CrazyBattleState::None)
    , m_nextState(CrazyBattleState::None)
    , m_state(nullptr)
{
    ms_instance = this;
}

CrazyBattle::~CrazyBattle()
{
    if (m_state != nullptr)
    {
        m_state->Shutdown();
        delete m_state;
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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL could not initalize! SDL_ERROR: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("Crazy Battle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
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

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "nearest pixel sampling not enabled");
    }

    ChangeState(CrazyBattleState::GameEndState);

    GameTimer gameTimer;

    gameTimer.Reset();

    bool quitGame = false;
    while (!quitGame)
    {
        SDL_PumpEvents();
        gameTimer.Tick();
        m_inputManager.Update();
        m_gameManager.Update();

        SDL_SetRenderDrawColor(m_renderer, 0xb1, 0xc5, 0xdf, 0xff);
        SDL_RenderClear(m_renderer);

        CheckAndChangeState();

        if (m_currentState != CrazyBattleState::None)
        {
            m_state->Update(gameTimer);
            m_state->Render();
        }

        SDL_RenderPresent(m_renderer);

        CheckEvents(quitGame);
    }

    return 0;
}

void CrazyBattle::CheckAndChangeState()
{
    if (m_nextState != CrazyBattleState::None && m_nextState != m_currentState)
    {
        if (m_state != nullptr)
        {
            m_state->Shutdown();
            delete m_state;
        }

        switch (m_nextState)
        {
        case CrazyBattleState::Game:
            m_state = new GameState();
            break;
        case CrazyBattleState::MainMenu:
            m_state = new MainMenuState();
            break;
        case CrazyBattleState::GameEndState:
            m_state = new GameEndState();
            break;
        default:
            SDL_assert(false);
            m_state = nullptr;
            m_currentState = CrazyBattleState::None;
            break;
        }

        if (m_state)
        {
            m_state->Init();
            m_currentState = m_nextState;
        }
    }
    m_nextState = CrazyBattleState::None;
}

void CrazyBattle::CheckEvents(bool &quitGame)
{
    SDL_Event sdlEvents[NumOfEventsPerPeek];

    // Using SDL_GETEVENT to remove all the events
    const int numOfEvents = SDL_PeepEvents(sdlEvents, NumOfEventsPerPeek, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
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
