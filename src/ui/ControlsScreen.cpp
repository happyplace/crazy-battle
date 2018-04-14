#include "ControlsScreen.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"
#include "ui/UIRendererHelper.h"

ControlsScreen::ControlsScreen()
{
    m_fontSmall = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 55);

    m_button = AssetLoaderHelper::LoadTexture("media/button_sprites.png");
    m_buttonFrames = AssetLoaderHelper::LoadTextureFrames("media/button_sprites.json");

    m_BackButton.SetFont(m_fontSmall);
    m_BackButton.SetText("Return");

    m_controller = AssetLoaderHelper::LoadTexture("media/Common_Controller.png");

    m_superJump.SetFont(m_fontSmall);
    m_superJump.SetText("(hold) Super Jump");
    m_jump.SetFont(m_fontSmall);
    m_jump.SetText("Jump");
    m_attack.SetFont(m_fontSmall);
    m_attack.SetText("Attack");
    m_sinAttack.SetFont(m_fontSmall);
    m_sinAttack.SetText("Sin Attack");
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

    m_BackButton.Render(1280 - m_BackButton.GetWidth() - 40, 720 - m_BackButton.GetHeight() - 40);
    UIRendererHelper::RenderTextureFrame(1000, 720 - m_BackButton.GetHeight() - 40, "b_button.png",
                                         m_button, m_buttonFrames, 2.0f, 2.0f);

    float scale = 0.35f;
    UIRendererHelper::RenderTextureFrame(
                (1280.0f / 2.0f) - ((m_controller->width * scale) / 2.0f),
                (720.0f / 2.0f) - ((m_controller->height * scale) / 2.0f),
                "", m_controller, nullptr, scale, scale);

    m_superJump.Render(800, 20);
    UIRendererHelper::RenderTextureFrame(720, 20, "a_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_jump.Render(800, 90);
    UIRendererHelper::RenderTextureFrame(720, 90, "a_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_attack.Render(100, 20);
    UIRendererHelper::RenderTextureFrame(25, 20, "x_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);

    m_sinAttack.Render(100, 90);
    UIRendererHelper::RenderTextureFrame(25, 90, "x_button.png", m_button, m_buttonFrames, 2.0f, 2.0f);
}
