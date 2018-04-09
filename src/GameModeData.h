#pragma once

#include <cstdint>
#include <vector>

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

class GameModeData
{
public:
	const std::vector<ScorePair>& GetScores() const { return m_scores; }

	void OnPlayerKill(int64_t playerIdGotKill, int64_t playerIdDied);
	void PlayerAdded(int64_t playerId);
	void PlayerRemoved(int64_t playerId);

private:
	ScorePair* GetScorePair(int64_t playerId);

	std::vector<ScorePair> m_scores;
};
