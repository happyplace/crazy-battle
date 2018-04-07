#pragma once

#include <SDL.h>
#include <SDL_image.h>

class CrazyBattle
{
public:
    static CrazyBattle& Game() { return *ms_instance; }

    CrazyBattle();
    ~CrazyBattle();

    int Run(int argc, char* argv[]);

    SDL_Window* Window() { return m_window; }
    SDL_Renderer* Renderer() { return m_renderer; }

private:
    bool Init(int argc, char* argv[]);

    static CrazyBattle* ms_instance;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};
