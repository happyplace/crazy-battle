#pragma once

#include "FrameworkExport.h"

namespace gf
{
    class GameMode
    {
    public:
        GameMode();
        virtual ~GameMode() {}

        void Init();
        void Update();
        void Destroy();

        //virtual void OnInit() = 0;
        //virtual void OnUpdate() = 0;
        //virtual void OnDestroy() = 0;
    };
}
