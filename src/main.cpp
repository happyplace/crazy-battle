#include "CrazyBattle.h"

#include <iostream>

#if __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    SetProcessDPIAware();

    return CrazyBattle().Run(__argc, __argv);
}
#else
int main(int argc, char* argv[])
{
    return CrazyBattle().Run(argc, argv);
}
#endif // __WIN32__
