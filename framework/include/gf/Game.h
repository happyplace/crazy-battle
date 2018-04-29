#pragma once

#include <SDL.h>

#include "FrameworkExport.h"

namespace gf
{
    class Game
    {
    public:
        FRAMEWORKDLL Game();
        FRAMEWORKDLL virtual ~Game();

        FRAMEWORKDLL int Run(int argc, char** argv);

        FRAMEWORKDLL void QuitGame();

    protected:
        FRAMEWORKDLL virtual void OnInit() = 0;
        FRAMEWORKDLL virtual void OnDestroy() = 0;

    private:
        void Init();
        void Destroy();

        bool m_quitGame;
    };
}
