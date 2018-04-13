#pragma once

struct GameModeScore
{
    GameModeScore() : kills(0), deaths(0) {}
    int kills;
    int deaths;
};

struct ScorePair
{
    ScorePair() : playerId(0) {}
    int64_t playerId;
    GameModeScore score;
};

enum class DamageType
{
    None,
    Linear,
};

struct GameHealth
{
    enum class State
    {
        Idle,
        Respawning,
        Dead,
    };

    GameHealth()
        : state(State::Idle)
        , lives(-1)
        , health(100.0f)
        , deathTimer(0.0f)
    {}

    State state;
    int lives;
    float health;
    float deathTimer;
};

struct HealthPair
{
    HealthPair()
        : playerId(-1)
    {}

    int64_t playerId;
    GameHealth health;
};
