#pragma once

#include <SDL.h>

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
    GameHealth()
        : lives(-1)
        , health(100.0f)
        , deathTimer(0.0f)
    {}

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

struct ColorPair
{
    ColorPair()
        : playerId(-1)
        , category(0x0000)
    {}

    int64_t playerId;
    SDL_Color color;
    short category;
};
