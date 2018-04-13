#include "MainMenuState.h"

#include "CrazyBattle.h"
#include "GameTimer.h"
#include "InputManager.h"

void MainMenuState::Init()
{
}

void MainMenuState::DoUpdate(const GameTimer& gameTimer)
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
    }
}

void MainMenuState::Render()
{
    m_titleScreenLogo.Render();
}

void MainMenuState::Shutdown()
{
}
