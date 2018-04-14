#pragma once

#include <SDL.h>

#include "anax/System.hpp"

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"
#include "GameModeData.h"
#include "ui/HealthWidget.h"

#include "components/PlayerComponent.h"

class UIPlayerHealthSystem : public anax::System<anax::Requires<PlayerComponent>>
{
public:
    UIPlayerHealthSystem();

    void Render(GameModeData& gameModeData);

private:
    anax::Entity GetPlayer(int64_t playerId);

    FontAssetPtr m_font;
    UILabel m_label;
    HealthWidget m_healthWidget;
};
