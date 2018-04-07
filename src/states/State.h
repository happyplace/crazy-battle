#pragma once

#include "anax/World.hpp"

class GameTimer;

class State
{
public:
    virtual ~State() {}

    void Update(const GameTimer& gameTimer)
    {
        m_world.refresh();
        DoUpdate(gameTimer);
    }

    virtual void Init() = 0;
    virtual void DoUpdate(const GameTimer& gameTimer) = 0;
    virtual void Render() = 0;
    virtual void Shutdown() = 0;

protected:
    anax::World m_world;
};
