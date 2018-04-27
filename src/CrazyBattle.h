#pragma once

#include "gf/Game.h"

class CrazyBattle : public gf::Game
{
protected:
    void OnInit() override;
    void OnDestroy() override;
};
