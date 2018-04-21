#include "GamePad.h"

#include "InputManager.h"

GamePad::GamePad(int32_t id, SDL_GameController* gameController)
    : m_id(id)
    , m_inputType(InputType::Joystick)
    , m_gameController(gameController)
{
}

GamePad::GamePad(int32_t id, const KeyboardConfig& keyboardConfig)
    : m_id(id)
    , m_inputType(InputType::Keyboard)
    , m_gameController(nullptr)
    , m_keyboardConfig(keyboardConfig)
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.attack] == 1;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.jump] == 1;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.back] == 1;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.start] == 1;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        float pos = state[m_keyboardConfig.moveX_pos] == 1 ? 1.0f : 0.0f;
        float neg = state[m_keyboardConfig.moveX_neg] == 1 ? -1.0f : 0.0f;
        return pos + neg;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.btnB] == 1;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.btnLeftShoulder] == 1;
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
    else
    {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return state[m_keyboardConfig.btnY] == 1;
    }
    return false;
}
