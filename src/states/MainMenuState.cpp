#include "MainMenuState.h"

#include "CrazyBattle.h"
#include "GameTimer.h"
#include "InputManager.h"
#include "math.h"

void MainMenuState::Init()
{
    m_screen = Screen::Title;
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
        if (SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_B) == 1)
        {
            m_screen = Screen::Title;
        }
        if (m_screen == Screen::Title)
        {
            if (SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1)
            {
                m_screen = Screen::Controls;
            }
            ButtonState& state = GetButttonState(controllerId);
            bool yPressed = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_Y) == 1;
            if (yPressed && !state.y)
            {
                GameManager::GetInstance().GetRules().mode =
                        GameManager::GetInstance().GetRules().mode == GameRules::Mode::Lives ?
                            GameRules::Mode::Time :
                            GameRules::Mode::Lives;
            }
            state.y = yPressed;
            bool xPressed = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_X) == 1;
            if (xPressed && !state.x)
            {
                if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Lives)
                {
                    int lives = GameManager::GetInstance().GetRules().lives;
                    switch (lives)
                    {
                    case 3:
                        lives = 5;
                        break;
                    case 5:
                        lives = 10;
                        break;
                    case 10:
                        lives = 3;
                        break;
                    default:
                        lives = 3;
                        break;
                    }
                    GameManager::GetInstance().GetRules().lives = lives;
                }
                else
                {
                    int roundTime = static_cast<int>(round(GameManager::GetInstance().GetRules().time));
                    switch (roundTime)
                    {
                    case 60:
                        roundTime = 120;
                        break;
                    case 120:
                        roundTime = 30;
                        break;
                    case 30:
                        roundTime = 60;
                        break;
                    default:
                        roundTime = 60;
                        break;
                    }
                    GameManager::GetInstance().GetRules().time = static_cast<float>(roundTime);
                }
            }
            state.x = xPressed;
        }
    }
}

void MainMenuState::Render()
{
    switch (m_screen)
    {
    case Screen::Title:
        m_titleScreenLogo.Render();
        break;
    case Screen::Controls:
        m_controlsScreen.Render();
        break;
    }
}

void MainMenuState::Shutdown()
{
}

MainMenuState::ButtonState& MainMenuState::GetButttonState(SDL_JoystickID id)
{
    for (ButtonState& buttonState : m_buttonState)
    {
        if (buttonState.joyId == id)
        {
            return buttonState;
        }
    }
    ButtonState state;
    state.joyId = id;
    m_buttonState.push_back(state);
    return m_buttonState[m_buttonState.size() - 1];
}
