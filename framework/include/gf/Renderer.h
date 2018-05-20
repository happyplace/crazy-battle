#pragma once

#include "FrameworkExport.h"

struct SDL_Window;
struct SDL_Renderer;

namespace gf
{
    class Renderer
    {
    public:
        FRAMEWORKDLL static Renderer& GetInstance();
        static void CreateInstance();
        static void DestroyInstance();

        bool Init();
        void Destroy();

        SDL_Window* GetWindow() { return m_window; }
        SDL_Renderer* GetRenderer() { return m_renderer; }

    private:
        static Renderer* ms_instance;

        Renderer();
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
    };
}
