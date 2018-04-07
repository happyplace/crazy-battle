#pragma once

#include <unordered_map>
#include <vector>

#include <SDL.h>

class InputManager
{
public:
    static InputManager& GetInstance() { SDL_assert(ms_instance); &ms_instance; }
    static float GetControllerAxisWithDeadZone(SDL_GameController* controller, SDL_GameControllerAxis axis);

    InputManager();
    ~InputManager();

    void Update();
    SDL_GameController* GetController(SDL_JoystickID instanceId);
    void GetAllControllerInstanceIds(std::vector<SDL_JoystickID>& outInstanceIds) const;

private:
    static InputManager* ms_instance;

    struct GameController
    {
        SDL_GameController* gameController;
        SDL_JoystickID instanceId;
    };
    typedef std::unordered_map<SDL_JoystickID, GameController> GameControllerMap;
    GameControllerMap m_gameControllers;
};
