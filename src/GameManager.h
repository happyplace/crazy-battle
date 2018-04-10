#pragma once

#include <vector>

#include "GameManagerDefines.h"

class GameManager
{
public:
	static GameManager& GetInstance() { SDL_assert(ms_instance); &ms_instance; }

	GameManager();
	~GameManager();

	const std::vector<PlayerStruct>& GetPlayers() const { return m_players; }
	const PlayerStruct* GetPlayer(int64_t playerId) const;

	void Update();

private:
	static GameManager* ms_instance;

	PlayerStruct* GetPlayerAssignedToControllerId(SDL_JoystickID controllerId);
	PlayerStruct* CreatePlayer();

	int64_t m_nextPlayerId;
	std::vector<PlayerStruct> m_players;
};