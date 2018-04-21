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
