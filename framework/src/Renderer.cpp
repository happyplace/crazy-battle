#include "gf/Renderer.h"

#include <SDL.h>

using namespace gf;

Renderer* Renderer::ms_instance = nullptr;

Renderer& Renderer::GetInstance()
{
    SDL_assert(ms_instance);
    return *ms_instance;
}

void Renderer::CreateInstance()
{
    SDL_assert(!ms_instance);
    ms_instance = new Renderer();
}

void Renderer::DestroyInstance()
{
    SDL_assert(ms_instance);
    delete ms_instance;
}

Renderer::Renderer()
    : m_window(nullptr)
    , m_renderer(nullptr)
{
}

Renderer::~Renderer()
{
    Destroy();
}

bool Renderer::Init()
{
    m_window = SDL_CreateWindow("Game Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1920, 1080, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "window could not be created SDL_error: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL Error: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Renderer::Destroy()
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
}
