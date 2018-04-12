#pragma once

#include "State.h"
#include "GameModeData.h"
#include "GameLevelLoader.h"

#include "systems/PlayerMovementSystem.h"
#include "systems/SpriteRendererSystem.h"
#include "systems/AnimateSpriteUpdateSystem.h"
#include "systems/AnimateSpriteRendererSystem.h"
#include "systems/PhysicsWorldSystem.h"
#include "systems/PlayerEntitySpawnerSystem.h"
#include "systems/PlayerAnimationSystem.h"
#include "systems/PlayerAttackInputSystem.h"
#include "systems/LinearAttackSystem.h"
#include "systems/ChildTransformSystem.h"
#include "systems/TimedLifeSystem.h"

#include "ui/UIPlayerHealth.h"

class GameState : public State
{
public:
    GameState();

    void Init() override;
    void DoUpdate(const GameTimer& gameTimer) override;
    void Render() override;
    void Shutdown() override;

private:
    double accumulator;
    GameModeData m_gameModeData;
    GameLevelLoader m_gameLevelLoader;

    PlayerMovementSystem m_playerMovementSystem;
    SpriteRendererSystem m_spriteRendererSystem;
    AnimateSpriteUpdateSystem m_animateSpriteUpdateSystem;
    AnimateSpriteRendererSystem m_animateSpriteRendererSystem;
    PhysicsWorldSystem m_physicsWorldSystem;
    PlayerEntitySpawnerSystem m_playerEntitySpawnerSystem;
    PlayerAnimationSystem m_playerAnimationSystem;
    PlayerAttackInputSystem m_playerAttackInputSystem;
    LinearAttackSystem m_linearAttackSystem;
    ChildTransformSystem m_childTransformSystem;
    TimedLifeSystem m_timedLifeSystem;

    UIPlayerHealth m_uiPlayerHealth;
};
