#pragma once

#include "State.h"
#include "ui/UIEndGameScreen.h"

class GameEndState : public State
{
public:
    void Init() override;
    void DoUpdate(const GameTimer& gameTimer) override;
    void Render() override;
    void Shutdown() override;

private:
    UIEndGameScreen m_endGameScreen;
};
