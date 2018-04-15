#include "GameModeData.h"

#include "GameManager.h"
#include "GameTimer.h"
#include "InputManager.h"

GameModeData::GameModeData()
    : m_isGameRunning(false)
    , m_timeLeft(0.0f)
{
    m_colors.resize(4);
    m_colors[0].playerId = -1;
    m_colors[0].color = { 0xff, 0xff, 0xff, 0xff };
    m_colors[0].category = 0x1;
    m_colors[1].playerId = -1;
    m_colors[1].color = { 0xff, 0x01, 0xc8, 0xff };
    m_colors[1].category = 0x2;
    m_colors[2].playerId = -1;
    m_colors[2].color = { 0x41, 0xff, 0x01, 0xff };
    m_colors[2].category = 0x4;
    m_colors[3].playerId = -1;
    m_colors[3].color = { 0x03, 0xb3, 0xff, 0xff };
    m_colors[3].category = 0x8;
}

void GameModeData::OnPlayerKill(int64_t playerIdGotKill, int64_t playerIdDied)
{
    if (playerIdGotKill == playerIdDied)
    {
        if (ScorePair* score = GetScorePair(playerIdGotKill))
        {
            score->score.deaths += 2;
        }
    }
    else
    {
        if (ScorePair* score = GetScorePair(playerIdGotKill))
        {
            score->score.kills++;
        }

        if (ScorePair* score = GetScorePair(playerIdDied))
        {
            score->score.deaths++;
        }
    }
}

void GameModeData::PlayerAdded(int64_t playerId)
{
	if (GetScorePair(playerId) == nullptr)
	{
		ScorePair pair;
		pair.playerId = playerId;
		m_scores.push_back(pair);
	}

    if (GetHealthPair(playerId) == nullptr)
    {
        HealthPair pair;
        pair.playerId = playerId;
        pair.health.health = GameManager::GetInstance().GetRules().health;
        pair.health.lives = GameManager::GetInstance().GetRules().lives;
        m_health.push_back(pair);
    }

    for (ColorPair& colorPair : m_colors)
    {
        if (colorPair.playerId == -1)
        {
            colorPair.playerId = playerId;
            break;
        }
    }
}

void GameModeData::PlayerRemoved(int64_t playerId)
{
    for (ColorPair& colorPair : m_colors)
    {
        if (colorPair.playerId == playerId)
        {
            colorPair.playerId = -1;
            break;
        }
    }

	for (std::size_t i = 0; i < m_scores.size(); i++)
	{
        if (m_scores[i].playerId == playerId)
		{
            m_scores.erase(m_scores.begin() + i);
            break;
		}
	}

    for (std::size_t i = 0; i < m_health.size(); i++)
    {
        if (m_health[i].playerId == playerId)
        {
            m_health.erase(m_health.begin() + i);
            break;
        }
    }
}

ScorePair* GameModeData::GetScorePair(int64_t playerId)
{
	for (ScorePair& scorePair : m_scores)
	{
		if (scorePair.playerId == playerId)
            return &scorePair;
	}
    return nullptr;
}

HealthPair* GameModeData::GetHealthPair(int64_t playerId)
{
    for (HealthPair& healthPair : m_health)
    {
        if (healthPair.playerId == playerId)
            return &healthPair;
    }
    return nullptr;
}

ColorPair* GameModeData::GetColorPair(int64_t playerId)
{
    for (ColorPair& colorPair : m_colors)
    {
        if (colorPair.playerId == playerId)
            return &colorPair;
    }
    return nullptr;
}

float GameModeData::GetDamage(DamageType damageType) const
{
    switch(damageType)
    {
    case DamageType::Linear:
        return 25.0f;
    default:
        return 0.0f;
    }
}

void GameModeData::OnPlayerDamage(int64_t senderPlayerId, int64_t receiverPlayerId, DamageType damageType)
{
    HealthPair* receiverPair = GetHealthPair(receiverPlayerId);
    if (receiverPair)
    {
        receiverPair->health.health -= GetDamage(damageType);
        if (receiverPair->health.health <= 0)
        {
            OnPlayerKill(senderPlayerId, receiverPlayerId);
        }
    }
}

void GameModeData::Update(const GameTimer& gameTimer)
{
    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time)
    {
        m_timeLeft -= static_cast<float>(gameTimer.DeltaTime());
    }

    if (!m_isGameRunning)
    {
        std::vector<SDL_JoystickID> controllerIds;
        InputManager::GetInstance().GetAllControllerInstanceIds(controllerIds);
        for (SDL_JoystickID controllerId : controllerIds)
        {
            SDL_GameController* gameController = InputManager::GetInstance().GetController(controllerId);
            if (SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_BACK) == 1 && m_health.size() > 1)
            {
                StartGame();
            }
        }
    }
}

void GameModeData::StartGame()
{
    m_isGameRunning = true;
    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time)
    {
        m_timeLeft = GameManager::GetInstance().GetRules().time;
    }
}
