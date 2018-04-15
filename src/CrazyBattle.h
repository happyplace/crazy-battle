#pragma once

#include <vector>

#include <SDL.h>

#include "InputManager.h"
#include "GameManager.h"

enum class CrazyBattleState
{
    None,
    Game,
    MainMenu,
    GameEndState,
};

#define NUM_OF_EVENTS_PER_PEEK 100

class State;

class CrazyBattle
{
public:
    static CrazyBattle& Game() { return *ms_instance; }

    CrazyBattle();
    ~CrazyBattle();

    int Run(int argc, char* argv[]);
    void ChangeState(CrazyBattleState state) { m_nextState = state; }

    SDL_Window* Window() { return m_window; }
    SDL_Renderer* Renderer() { return m_renderer; }

private:
    bool Init(int argc, char* argv[]);
    void CheckEvents(bool& quitGame);
    void CheckAndChangeState();

    static CrazyBattle* ms_instance;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputManager m_inputManager;
    GameManager m_gameManager;

    CrazyBattleState m_currentState;
    CrazyBattleState m_nextState;
    State* m_state;
};
