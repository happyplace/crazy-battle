#include "UIPlayerHealthSystem.h"

#include "anax/World.hpp"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "math.h"

UIPlayerHealthSystem::UIPlayerHealthSystem()
{
    m_font = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 80);
    m_label.SetFont(m_font);
    m_label.SetText("Time: 999");
}

anax::Entity UIPlayerHealthSystem::GetPlayer(int64_t playerId)
{
    for (anax::Entity entity : getEntities())
    {
        const PlayerComponent& playerComp = entity.getComponent<PlayerComponent>();
        if (playerComp.player.id == playerId)
        {
            return entity;
        }
    }
}

void UIPlayerHealthSystem::Render(GameModeData& gameModeData)
{
    if (!gameModeData.IsGameRunning())
    {
        return;
    }

    if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time)
    {
        m_label.SetText("Time: " + std::to_string(static_cast<int>(floorf(gameModeData.GetTimeLeft()))));
        m_label.Render(20, 0);
    }

    const std::vector<HealthPair>& healthPairs = gameModeData.GetHealth();

    const int x_coord[] = { 50, 380, 700, 1000 };
    for (std::size_t i = 0; i < healthPairs.size(); i++)
    {
        const HealthPair& healthPair = healthPairs[i];
        const ColorPair* colorPair = gameModeData.GetColorPair(healthPair.playerId);

        anax::Entity player = GetPlayer(healthPair.playerId);
        const PlayerComponent& playerComp = player.getComponent<PlayerComponent>();
        switch (playerComp.state)
        {
        case PlayerComponent::State::Dead:
            break;
        case PlayerComponent::State::Respawning:
            m_healthWidget.RenderRespawning(x_coord[i], 618, healthPair.health.deathTimer, colorPair->color);
            break;
        case PlayerComponent::State::Idle:
        {
            if (GameManager::GetInstance().GetRules().mode == GameRules::Mode::Time)
            {
                GameModeScore& score = gameModeData.GetScorePair(healthPair.playerId)->score;
                m_healthWidget.RenderTime(x_coord[i], 618, score.kills, score.deaths, healthPair.health.health, colorPair->color);
            }
            else
            {
                m_healthWidget.RenderLives(x_coord[i], 618, healthPair.health.lives, healthPair.health.health, colorPair->color);
            }
        } break;
        }
    }
}
