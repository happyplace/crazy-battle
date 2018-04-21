#include "GameEndState.h"

#include "CrazyBattle.h"
#include "GameTimer.h"
#include "InputManager.h"

void GameEndState::Init()
{
}

void GameEndState::DoUpdate(const GameTimer& gameTimer)
{
    for (GamePadPtr gamePad : InputManager::GetInstance().GetAllGamePads())
    {        
        if (gamePad->Start())
        {
            CrazyBattle::Game().ChangeState(CrazyBattleState::Game);
        }
        if (gamePad->Back())
        {
            CrazyBattle::Game().ChangeState(CrazyBattleState::MainMenu);
        }
    }

    m_endGameScreen.Update(gameTimer);
}

void GameEndState::Render()
{
    m_endGameScreen.Render();
}

void GameEndState::Shutdown()
{
}
