#pragma once

#include <SDL.h>

#include "AssetLoaderDefines.h"
#include "ui/basic/UILabel.h"

class GamepadControlsWidget
{
public:
    GamepadControlsWidget();

    void Render();

private:
    FontAssetPtr m_fontSmall;
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;
    TextureAssetPtr m_controller;
    UILabel m_jump;
    UILabel m_superJump;
    UILabel m_attack;
    UILabel m_sinAttack;
};

class KeyboardControlsWidget
{
public:
    KeyboardControlsWidget();

    void Render();

private:
    FontAssetPtr m_fontSmall;
    UILabel m_header;
    UILabel m_player;
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;
    UILabel m_player1;
    UILabel m_player2;
};

class ControlsScreen
{
public:
    ControlsScreen();

    void SwapShowKeyboard() { m_showKeyboard = !m_showKeyboard; }
    void Render();

private:
    TextureAssetPtr m_button;
    TextureFramesAssetPtr m_buttonFrames;
    GamepadControlsWidget m_gamePad;
    KeyboardControlsWidget m_keyboard;
    UILabel m_BackButton;
    FontAssetPtr m_fontSmall;
    bool m_showKeyboard;
};
