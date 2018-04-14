#include "GameEndState.h"

#include "CrazyBattle.h"
#include "GameTimer.h"
#include "InputManager.h"

void GameEndState::Init()
{
}

void GameEndState::DoUpdate(const GameTimer& gameTimer)
{
    std::vector<SDL_JoystickID> controllerIds;
    InputManager::GetInstance().GetAllControllerInstanceIds(controllerIds);
    for (SDL_JoystickID controllerId : controllerIds)
    {
        SDL_GameController* gameController = InputManager::GetInstance().GetController(controllerId);
        if (SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_START) == 1)
        {
            CrazyBattle::Game().ChangeState(CrazyBattleState::Game);
        }
        if (SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_BACK) == 1)
        {
            CrazyBattle::Game().ChangeState(CrazyBattleState::MainMenu);
        }
    }

    m_endGameScreen.Update(gameTimer);
}

void GameEndState::Render()
{
    m_endGameScreen.Render();
}

void GameEndState::Shutdown()
{
}
