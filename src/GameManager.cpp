#include "GameManager.h"

#include "InputManager.h"

GameManager* GameManager::ms_instance = nullptr;

GameManager::GameManager()
	: m_nextPlayerId(0)
{
	ms_instance = this;

    m_gameRules.mode = GameRules::Mode::Time;
    m_gameRules.lives = 5;
    m_gameRules.time = 60.0f;
    m_gameRules.deathTime = 3.0f;
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

PlayerStruct* GameManager::GetPlayerAssignedToControllerId(int32_t controllerId)
{
    for (PlayerStruct& player : m_players)
	{
        if (player.gamePadId == controllerId)
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
        if (inputManager.GetGamePad(player.gamePadId) == nullptr)
		{
            player.gamePadId = -1;
		}
	}

    for (GamePadPtr gamePad : inputManager.GetAllGamePads())
	{
        if (gamePad->Start())
		{
            if (GetPlayerAssignedToControllerId(gamePad->GetId()) == nullptr)
			{
				PlayerStruct* player = CreatePlayer();
                player->gamePadId = gamePad->GetId();
			}
		}
	}
}
