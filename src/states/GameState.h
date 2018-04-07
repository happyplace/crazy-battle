#pragma once

#include "State.h"
#include "systems/PlayerMovementSystem.h"
#include "systems/SpriteRendererSystem.h"

class GameState : public State
{
public:
    void Init() override;
    void DoUpdate(const GameTimer& gameTimer) override;
    void Render() override;
    void Shutdown() override;

private:
    PlayerMovementSystem m_playerMovementSystem;
    SpriteRendererSystem m_spriteRendererSystem;
};
