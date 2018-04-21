#pragma once

#include <cstdint>

#include <SDL.h>

struct PlayerStruct
{
    explicit PlayerStruct(int64_t pId) : id(pId), gamePadId(-1) {}
    PlayerStruct() : id(-1), gamePadId(-1) {}
	
	int64_t id;
    int32_t gamePadId;
};

struct GameRules
{
    enum class Mode { Lives, Time, };
    Mode mode;
    int lives;
    float time;
    float deathTime;
    float health;
};
