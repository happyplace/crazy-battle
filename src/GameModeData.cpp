#include "GameModeData.h"

#include "GameManager.h"
#include "GameTimer.h"

GameModeData::GameModeData()
{
   m_timeLeft = GameManager::GetInstance().GetRules().time;
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
}

void GameModeData::PlayerRemoved(int64_t playerId)
{
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
    m_timeLeft -= static_cast<float>(gameTimer.DeltaTime());
}
