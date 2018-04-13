#include "GameManager.h"

#include "InputManager.h"

GameManager* GameManager::ms_instance = nullptr;

GameManager::GameManager()
	: m_nextPlayerId(0)
{
	ms_instance = this;

    m_gameRules.mode = GameRules::Mode::Time;
    m_gameRules.lives = 3;
    m_gameRules.time = 60.0f;
    m_gameRules.deathTime = 5.0f;
    m_gameRules.health = 125.0f;
}

GameManager::~GameManager()
{
	ms_instance = nullptr;
}

PlayerStruct* GameManager::CreatePlayer()
{
	m_players.push_back(PlayerStruct(m_nextPlayerId++));
    return &m_players.back();
}

PlayerStruct* GameManager::GetPlayerAssignedToControllerId(SDL_JoystickID controllerId)
{
    for (PlayerStruct& player : m_players)
	{
		if (player.controllerInstanceId == controllerId)
		{
            return &player;
		}
	}
	return nullptr;
}

const PlayerStruct* GameManager::GetPlayer(int64_t playerId) const
{
	for (const PlayerStruct& player : m_players)
	{
		if (player.id == playerId)
		{
            return &player;
		}
	}
	return nullptr;
}

void GameManager::Update()
{
	InputManager& inputManager = InputManager::GetInstance();

	for (PlayerStruct& player : m_players)
	{
		if (inputManager.GetController(player.controllerInstanceId) == nullptr)
		{
			player.controllerInstanceId = -1;
		}
	}

	std::vector<SDL_JoystickID> controllerIds;
	inputManager.GetAllControllerInstanceIds(controllerIds);
	for (SDL_JoystickID controllerId : controllerIds)
	{
		SDL_GameController* gameController = inputManager.GetController(controllerId);
		if (SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_START) == 1)
		{
			if (GetPlayerAssignedToControllerId(controllerId) == nullptr)
			{
				PlayerStruct* player = CreatePlayer();
                player->controllerInstanceId = controllerId;
			}
		}
	}
}
