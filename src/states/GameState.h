#pragma once

#include "State.h"
#include "systems/PlayerMovementSystem.h"
#include "systems/SpriteRendererSystem.h"
#include "systems/AnimateSpriteUpdateSystem.h"
#include "systems/AnimateSpriteRendererSystem.h"
#include "systems/PhysicsWorldSystem.h"
#include "systems/PlayerEntitySpawnerSystem.h"
#include "systems/PlayerAnimationSystem.h"
#include "GameModeData.h"

class GameState : public State
{
public:
    GameState();

    void Init() override;
    void DoUpdate(const GameTimer& gameTimer) override;
    void Render() override;
    void Shutdown() override;

private:
    PlayerMovementSystem m_playerMovementSystem;
    SpriteRendererSystem m_spriteRendererSystem;
    AnimateSpriteUpdateSystem m_animateSpriteUpdateSystem;
    AnimateSpriteRendererSystem m_animateSpriteRendererSystem;
    PhysicsWorldSystem m_physicsWorldSystem;
    PlayerEntitySpawnerSystem m_playerEntitySpawnerSystem;
    PlayerAnimationSystem m_playerAnimationSystem;
    double accumulator;
    GameModeData m_gameModeData;
};
