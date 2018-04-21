#pragma once

#include <unordered_map>
#include <vector>

#include <SDL.h>

#include "GamePad.h"

class InputManager
{
public:
    static InputManager& GetInstance() { SDL_assert(ms_instance); return *ms_instance; }
    static float GetControllerAxisWithDeadZone(SDL_GameController* controller, SDL_GameControllerAxis axis);

    InputManager();
    ~InputManager();

    void Update();

    GamePadPtr GetGamePad(int32_t gamePadId);
    const std::vector<GamePadPtr>& GetAllGamePads() const { return m_gamePads; }

private:
    static InputManager* ms_instance;

    struct GamePadJoystickPair
    {
        int32_t gamePadId;
        SDL_JoystickID instanceId;
    };

    GamePadJoystickPair* GetJoystickPair(SDL_JoystickID instanceId);

    int32_t m_nextGamePadId;
    std::vector<GamePadJoystickPair> m_gamePadJoysticks;
    std::vector<GamePadPtr> m_gamePads;
};
