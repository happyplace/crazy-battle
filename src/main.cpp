#include <iostream>

#include "CrazyBattle.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    SetProcessDPIAware();
    return CrazyBattle().Run(__argc, __argv);
}
