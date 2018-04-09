#include "GameModeData.h"

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
}

void GameModeData::PlayerRemoved(int64_t playerId)
{
	for (std::size_t i = 0; i < m_scores.size(); i++)
	{
        if (m_scores[i].playerId == playerId)
		{
            m_scores.erase(m_scores.begin() + i);
			return;
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
}
