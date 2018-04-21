#include "ControlsScreen.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "ui/UIRendererHelper.h"

GamepadControlsWidget::GamepadControlsWidget()
{
    m_fontSmall = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 55);

    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");

    m_controller = AssetLoaderHelper::LoadTexture("media/Common_Controller.png");

    m_superJump.SetFont(m_fontSmall);
    m_superJump.SetText("(hold) Super Jump");
    m_jump.SetFont(m_fontSmall);
    m_jump.SetText("Jump");
    m_attack.SetFont(m_fontSmall);
    m_attack.SetText("Attack");
    m_sinAttack.SetFont(m_fontSmall);
    m_sinAttack.SetText("(hold) Sine Attack");
}

void GamepadControlsWidget::Render()
{
    float scale = 0.35f;
    UIRendererHelper::RenderTextureFrame(
                (1280.0f / 2.0f) - ((m_controller->width * scale) / 2.0f),
                (720.0f / 2.0f) - ((m_controller->height * scale) / 2.0f),
                "", m_controller, nullptr, scale, scale);

    m_jump.Render(800, 90);
    UIRendererHelper::RenderTextureFrame(720, 90, "a_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_attack.Render(100, 20);
    UIRendererHelper::RenderTextureFrame(25, 20, "x_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_sinAttack.Render(100, 90);
    UIRendererHelper::RenderTextureFrame(25, 90, "x_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);
}

KeyboardControlsWidget::KeyboardControlsWidget()
{
    m_fontSmall = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 55);
    m_header.SetFont(m_fontSmall);
    m_header.SetText("Two Players can use the Keyboard at the same time");
    m_player.SetFont(m_fontSmall);
    m_player.SetText("Left: Right: Attack: Jump:");
    m_player.SetLineWrap(250);
    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");
    m_player1.SetFont(m_fontSmall);
    m_player1.SetText("Control 1:");
    m_player2.SetFont(m_fontSmall);
    m_player2.SetText("Control 2:");
}

void KeyboardControlsWidget::Render()
{
    m_header.Render(0,0);

    int player1X = 60;
    int player1Y = 200;
    m_player1.Render(player1X, player1Y - 100);
    m_player.Render(player1X, player1Y);
    UIRendererHelper::RenderTextureFrame(player1X + 200, player1Y + 10, "keyboard_a.png", m_button, m_buttonFrames, 6.0f, 6.0f);
    UIRendererHelper::RenderTextureFrame(player1X + 200, player1Y + 75, "keyboard_d.png", m_button, m_buttonFrames, 6.0f, 6.0f);
    UIRendererHelper::RenderTextureFrame(player1X + 200, player1Y + 135, "keyboard_o.png", m_button, m_buttonFrames, 6.0f, 6.0f);
    UIRendererHelper::RenderTextureFrame(player1X + 200, player1Y + 200, "keyboard_p.png", m_button, m_buttonFrames, 6.0f, 6.0f);

    int player2X = 900;
    int player2Y = 200;
    m_player2.Render(player2X, player2Y - 100);
    m_player.Render(player2X, player2Y);
    UIRendererHelper::RenderTextureFrame(player2X + 200, player2Y + 10, "keyboard_left.png", m_button, m_buttonFrames, 6.0f, 6.0f);
    UIRendererHelper::RenderTextureFrame(player2X + 200, player2Y + 75, "keyboard_right.png", m_button, m_buttonFrames, 6.0f, 6.0f);
    UIRendererHelper::RenderTextureFrame(player2X + 200, player2Y + 135, "keyboard_ins.png", m_button, m_buttonFrames, 6.0f, 6.0f);
    UIRendererHelper::RenderTextureFrame(player2X + 200, player2Y + 200, "keyboard_del.png", m_button, m_buttonFrames, 6.0f, 6.0f);
}

ControlsScreen::ControlsScreen()
    : m_showKeyboard(false)
{
    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");
    m_fontSmall = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 55);
    m_BackButton.SetFont(m_fontSmall);
    m_BackButton.SetText("Return");
}

void ControlsScreen::Render()
{
    SDL_SetRenderDrawColor(CrazyBattle::Game().Renderer(), 0x00, 0x00, 0x00, 0xff);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 1280;
    rect.h = 720;
    SDL_RenderFillRect(CrazyBattle::Game().Renderer(), &rect);

    m_BackButton.SetText(m_showKeyboard ? "Keyboard" : "Gamepad");
    int offsetX = m_showKeyboard ? 75 : 75;
    m_BackButton.Render(1280 - m_BackButton.GetWidth() - 40, 720 - m_BackButton.GetHeight() - 40 - 80);
    UIRendererHelper::RenderTextureFrame(1000 - offsetX, 720 - m_BackButton.GetHeight() - 40 - 80, "y_button.png",
                                         m_button, m_buttonFrames, 2.0f, 2.0f);
    UIRendererHelper::RenderTextureFrame(1000 - 160 - offsetX, 720 - m_BackButton.GetHeight() - 40 - 80, "keyboard_k.png",
                                         m_button, m_buttonFrames, 10.0f, 10.0f);
    UIRendererHelper::RenderTextureFrame(1000 - 160 - 80 - offsetX, 720 - m_BackButton.GetHeight() - 40 - 80, "keyboard_7.png",
                                         m_button, m_buttonFrames, 10.0f, 10.0f);

    m_BackButton.SetText("Return");
    m_BackButton.Render(1280 - m_BackButton.GetWidth() - 40, 720 - m_BackButton.GetHeight() - 40);
    UIRendererHelper::RenderTextureFrame(1000, 720 - m_BackButton.GetHeight() - 40, "b_button.png",
                                         m_button, m_buttonFrames, 2.0f, 2.0f);
    UIRendererHelper::RenderTextureFrame(1000 - 160, 720 - m_BackButton.GetHeight() - 40, "keyboard_j.png",
                                         m_button, m_buttonFrames, 10.0f, 10.0f);
    UIRendererHelper::RenderTextureFrame(1000 - 160 - 80, 720 - m_BackButton.GetHeight() - 40, "keyboard_9.png",
                                         m_button, m_buttonFrames, 10.0f, 10.0f);

    if (m_showKeyboard)
        m_gamePad.Render();
    else
        m_keyboard.Render();
}
