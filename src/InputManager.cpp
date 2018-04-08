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
{
    ms_instance = this;
}

InputManager::~InputManager()
{
    ms_instance = nullptr;
}

void InputManager::GetAllControllerInstanceIds(std::vector<SDL_JoystickID>& outInstanceIds) const
{
    outInstanceIds.clear();
    for (const std::pair<SDL_JoystickID, GameController> gameControllerPair : m_gameControllers)
    {
        outInstanceIds.push_back(gameControllerPair.first);
    }
}

SDL_GameController* InputManager::GetController(SDL_JoystickID instanceId)
{
    GameControllerMap::iterator it = m_gameControllers.find(instanceId);
    if (it != m_gameControllers.end())
    {
        return it->second.gameController;
    }
    return nullptr;
}

void InputManager::Update()
{
    SDL_Event sdlEvents[CrazyBattle::NumOfEventsPerPeek];

    int numOfEvents = SDL_PeepEvents(sdlEvents, CrazyBattle::NumOfEventsPerPeek, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
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
            GameController controller;
            controller.gameController = SDL_GameControllerOpen(controllerIndex);
            SDL_assert(controller.gameController);
            if (controller.gameController)
            {
                SDL_Joystick* controllerJoystick = SDL_GameControllerGetJoystick(controller.gameController);
                controller.instanceId = SDL_JoystickInstanceID(controllerJoystick);
                SDL_assert(controller.instanceId >= 0);
                if (controller.instanceId >= 0)
                {
                    SDL_assert(m_gameControllers.find(controller.instanceId) == m_gameControllers.end());
                    m_gameControllers[controller.instanceId] = controller;
                }
            }
        }
        else if (sdlEvents[i].type == SDL_CONTROLLERDEVICEREMOVED)
        {
            const int32_t controllerInstanceId = sdlEvents[i].cdevice.which;
            GameControllerMap::iterator it = m_gameControllers.find(controllerInstanceId);
            SDL_assert(it != m_gameControllers.end());
            if (it != m_gameControllers.end())
            {
                SDL_GameControllerClose(it->second.gameController);
                m_gameControllers.erase(controllerInstanceId);
            }
        }
    }
}
