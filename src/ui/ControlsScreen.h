#pragma once

#include <SDL.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"

class ControlsScreen
{
public:
    ControlsScreen();

    void Render();

private:
    FontAssetPtr m_fontSmall;
    UILabel m_BackButton;
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;
    TextureAssetPtr m_controller;
    UILabel m_jump;
    UILabel m_superJump;
    UILabel m_attack;
    UILabel m_sinAttack;
};
