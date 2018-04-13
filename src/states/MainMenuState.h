#pragma once

#include "State.h"
#include "ui/TitleScreenLogo.h"

class MainMenuState : public State
{
public:
    void Init() override;
    void DoUpdate(const GameTimer& gameTimer) override;
    void Render() override;
    void Shutdown() override;

private:
    TitleScreenLogo m_titleScreenLogo;
};
