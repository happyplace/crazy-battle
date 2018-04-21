#include "InputManager.h"

#include "tinymath2d.h"

#include "CrazyBattle.h"

InputManager* InputManager::ms_instance = nullptr;

float InputManager::GetControllerAxisWithDeadZone(SDL_GameController* controller, SDL_GameControllerAxis axis)
{
    const float DeadZone = 0.2f;
    int16_t value = SDL_GameControllerGetAxis(controller, axis);
    if (value < 0)
        return clamp((value / 32768.0f) + DeadZone, -1.0f, 0.0f) / (1.0f - DeadZone);
    else
        return clamp((value / 32767.0f) - DeadZone, 0.0f, 1.0f) / (1.0f - DeadZone);
}

InputManager::InputManager()
    : m_nextGamePadId(0)
{
    ms_instance = this;

    KeyboardConfig keyboardConfig;
    keyboardConfig.attack = SDL_SCANCODE_O;
    keyboardConfig.jump = SDL_SCANCODE_P;
    keyboardConfig.back = SDL_SCANCODE_RSHIFT;
    keyboardConfig.start = SDL_SCANCODE_RETURN;
    keyboardConfig.btnB = SDL_SCANCODE_J;
    keyboardConfig.btnLeftShoulder = SDL_SCANCODE_L;
    keyboardConfig.btnY = SDL_SCANCODE_K;
    keyboardConfig.moveX_pos = SDL_SCANCODE_D;
    keyboardConfig.moveX_neg = SDL_SCANCODE_A;
    GamePadPtr keyboard0(new GamePad(m_nextGamePadId++, keyboardConfig));
    m_gamePads.push_back(keyboard0);

    keyboardConfig.attack = SDL_SCANCODE_KP_0;
    keyboardConfig.jump = SDL_SCANCODE_KP_PERIOD;
    keyboardConfig.back = SDL_SCANCODE_KP_PLUS;
    keyboardConfig.start = SDL_SCANCODE_KP_ENTER;
    keyboardConfig.btnB = SDL_SCANCODE_KP_9;
    keyboardConfig.btnLeftShoulder = SDL_SCANCODE_KP_8;
    keyboardConfig.btnY = SDL_SCANCODE_KP_7;
    keyboardConfig.moveX_pos = SDL_SCANCODE_RIGHT;
    keyboardConfig.moveX_neg = SDL_SCANCODE_LEFT;
    GamePadPtr keyboard1(new GamePad(m_nextGamePadId++, keyboardConfig));
    m_gamePads.push_back(keyboard1);
}

InputManager::~InputManager()
{
    ms_instance = nullptr;
}

InputManager::GamePadJoystickPair* InputManager::GetJoystickPair(SDL_JoystickID instanceId)
{
    for (GamePadJoystickPair& pair : m_gamePadJoysticks)
    {
        if (pair.instanceId == instanceId)
        {
            return &pair;
        }
    }
    return nullptr;
}

void InputManager::Update()
{
    SDL_Event sdlEvents[NUM_OF_EVENTS_PER_PEEK];

    int numOfEvents = SDL_PeepEvents(sdlEvents, NUM_OF_EVENTS_PER_PEEK, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    if (numOfEvents < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_PeepEvents failed with SDL Error: %s", SDL_GetError());
        return;
    }

    for (int i = 0; i < numOfEvents; i++)
    {
        if (sdlEvents[i].type == SDL_CONTROLLERDEVICEADDED)
        {
            const int32_t controllerIndex = sdlEvents[i].cdevice.which;
            SDL_GameController* gameController = SDL_GameControllerOpen(controllerIndex);
            SDL_assert(gameController);
            if (gameController)
            {
                SDL_Joystick* controllerJoystick = SDL_GameControllerGetJoystick(gameController);
                SDL_JoystickID instanceId = SDL_JoystickInstanceID(controllerJoystick);
                SDL_assert(instanceId >= 0);
                if (instanceId >= 0)
                {
                    SDL_assert(GetJoystickPair(instanceId) == nullptr);

                    GamePadPtr gamePad(new GamePad(m_nextGamePadId++, gameController));

                    GamePadJoystickPair pair;
                    pair.instanceId = instanceId;
                    pair.gamePadId = gamePad->GetId();
                    m_gamePadJoysticks.push_back(pair);

                    m_gamePads.push_back(gamePad);
                }
            }
        }
        else if (sdlEvents[i].type == SDL_CONTROLLERDEVICEREMOVED)
        {
            const int32_t controllerInstanceId = sdlEvents[i].cdevice.which;
            for (std::size_t k = 0; k < m_gamePadJoysticks.size(); k++)
            {
                if (m_gamePadJoysticks[k].instanceId == controllerInstanceId)
                {
                    for (std::size_t i = 0; i < m_gamePads.size(); i++)
                    {
                        if (m_gamePads[i]->GetId() == m_gamePadJoysticks[k].gamePadId)
                        {
                            m_gamePads.erase(m_gamePads.begin() + i);
                            break;
                        }
                    }
                    m_gamePadJoysticks.erase(m_gamePadJoysticks.begin() + k);
                    break;
                }
            }
        }
    }
}

GamePadPtr InputManager::GetGamePad(int32_t gamePadId)
{
    for (GamePadPtr gamePad : m_gamePads)
    {
        if (gamePad->GetId() == gamePadId)
        {
            return gamePad;
        }
    }
    return nullptr;
}
