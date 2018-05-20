#include "gf/Game.h"

#include <SDL.h>

#include "gf/Renderer.h"

using namespace gf;

Game::Game()
    : m_quitGame(false)
{
}

Game::~Game()
{
}

void Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL could not initalize! SDL_ERROR: %s", SDL_GetError());
        QuitGame();
        return;
    }

    Renderer::CreateInstance();

    if (!Renderer::GetInstance().Init())
    {
        QuitGame();
        return;
    }

    OnInit();
}

void Game::Destroy()
{
    Renderer::GetInstance().Destroy();
    
    Renderer::DestroyInstance();

    SDL_Quit();

    OnDestroy();
}

void Game::QuitGame()
{
    m_quitGame = true;
}

void Game::CheckEvents()
{
    SDL_Event sdlEvents[kNumOfEventsPerPeek];

    const int numOfEvents = SDL_PeepEvents(sdlEvents, kNumOfEventsPerPeek, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    if (numOfEvents < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_PeepEvents faile SDL_ERROR: %s", SDL_GetError());
    }

    for (int i = 0; i < numOfEvents; i++)
    {
        if (sdlEvents[i].type == SDL_QUIT)
        {
            QuitGame();
        }
    }
}

int Game::Run(int argc, char** argv)
{
    Init();

    while (!m_quitGame)
    {
        SDL_PumpEvents();

        SDL_Renderer* renderer = Renderer::GetInstance().GetRenderer();

        SDL_SetRenderDrawColor(renderer, 0xb1, 0xc5, 0xdf, 0xff);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        CheckEvents();
    }

    Destroy();

    return 0;
}
