#include "GamePad.h"

#include "InputManager.h"

GamePad::GamePad(int32_t id, SDL_GameController* gameController)
    : m_id(id)
    , m_inputType(InputType::Joystick)
    , m_gameController(gameController)
{
}

bool GamePad::Attack() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_X) == 1;
        }
    }
    return false;
}

bool GamePad::Jump() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_A) == 1;
        }
    }
    return false;
}

bool GamePad::Back() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_BACK) == 1;
        }
    }
    return false;
}

bool GamePad::Start() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_START) == 1;
        }
    }
    return false;
}

float GamePad::MoveX() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return InputManager::GetControllerAxisWithDeadZone(m_gameController, SDL_CONTROLLER_AXIS_LEFTX);
        }
    }
    return 0.0f;
}

bool GamePad::BtnB() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_B) == 1;
        }
    }
    return false;
}

bool GamePad::BtnLeftShoulder() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1;
        }
    }
    return false;
}

bool GamePad::BtnY() const
{
    if (m_inputType == InputType::Joystick)
    {
        SDL_assert(m_gameController);
        if (m_gameController)
        {
            return SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_Y) == 1;
        }
    }
    return false;
}
