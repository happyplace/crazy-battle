#pragma once

#include <SDL.h>

#include "FrameworkExport.h"

namespace gf
{
    class Game
    {
    public:
        static const int kNumOfEventsPerPeek = 100;

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
        void CheckEvents();

        bool m_quitGame;
    };
}
