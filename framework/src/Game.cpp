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

int Game::Run(int argc, char** argv)
{
    Init();

    SDL_Event e;
    while (!m_quitGame)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                QuitGame();
            }
        }

        SDL_UpdateWindowSurface(Renderer::GetInstance().GetWindow());
    }

    Destroy();

    return 0;
}
