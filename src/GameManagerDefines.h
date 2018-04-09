#pragma once

#include <cstdint>

#include <SDL.h>

struct PlayerStruct
{
	explicit PlayerStruct(int64_t pId) : id(pId), controllerInstanceId(-1) {}
	PlayerStruct() : id(-1), controllerInstanceId(-1) {}
	
	int64_t id;
	SDL_JoystickID controllerInstanceId;
};
