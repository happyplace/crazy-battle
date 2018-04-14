#pragma once

#include <vector>

#include "State.h"
#include "ui/TitleScreenLogo.h"
#include "ui/ControlsScreen.h"

class MainMenuState : public State
{
public:
    void Init() override;
    void DoUpdate(const GameTimer& gameTimer) override;
    void Render() override;
    void Shutdown() override;

private:
    enum class Screen { Title, Controls, };
    struct ButtonState
    {
        ButtonState() : joyId(-1), y(false), x(false) {}
        SDL_JoystickID joyId;
        bool y;
        bool x;
    };
    ButtonState& GetButttonState(SDL_JoystickID id);
    std::vector<ButtonState> m_buttonState;

    TitleScreenLogo m_titleScreenLogo;
    ControlsScreen m_controlsScreen;
    Screen m_screen;
};
