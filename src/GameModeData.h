#pragma once

#include <cstdint>
#include <vector>

#include "GameModeDataDefines.h"

class GameTimer;

class GameModeData
{
public:
    GameModeData();

	const std::vector<ScorePair>& GetScores() const { return m_scores; }
    const std::vector<HealthPair>& GetHealth() const { return m_health; }
    std::vector<HealthPair>& GetHealth() { return m_health; }
    HealthPair* GetHealthPair(int64_t playerId);

    void OnPlayerDamage(int64_t senderPlayerId, int64_t receiverPlayerId, DamageType damageType);

	void PlayerAdded(int64_t playerId);
	void PlayerRemoved(int64_t playerId);

    float GetTimeLeft() const { return m_timeLeft; }

    void Update(const GameTimer& gameTimer);

private:
    void OnPlayerKill(int64_t playerIdGotKill, int64_t playerIdDied);
    ScorePair* GetScorePair(int64_t playerId);
    float GetDamage(DamageType damageType) const;

	std::vector<ScorePair> m_scores;
    std::vector<HealthPair> m_health;

    float m_timeLeft;
};
