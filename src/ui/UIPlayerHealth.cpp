#include "UIPlayerHealth.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"

UIPlayerHealth::UIPlayerHealth()
{
    m_font = AssetLoaderHelper::LoadFont("media/helmet2/Helmet-Regular.ttf", 100);
    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    //m_spriteAnimations = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");

    m_label.SetFont(m_font);
    m_label.SetText("100%");
}

void UIPlayerHealth::Render(GameModeData& gameModeData)
{
    m_label.SetText(std::to_string(gameModeData.GetTimeLeft()));

    SDL_Rect renderQuad;
    renderQuad.x = 100;
    renderQuad.y = 0;
    renderQuad.w = m_label.GetWidth();
    renderQuad.h = m_label.GetHeight();
    SDL_RenderCopy(CrazyBattle::Game().Renderer(), m_label.GetTexture(), nullptr, &renderQuad);

    SDL_Rect frameRect;
    for (const TextureFrame& textureFrame : m_textureFrames->frames)
    {
        if (textureFrame.name.compare("icon_orbs_materials_02.png") == 0)
        {
            frameRect.x = textureFrame.x;
            frameRect.y = textureFrame.y;
            frameRect.w = textureFrame.width;
            frameRect.h = textureFrame.height;

            SDL_Rect dstRect;
            dstRect.w = textureFrame.width * 3;
            dstRect.h = textureFrame.height * 3;
            dstRect.x = 0;
            dstRect.y = 0;

            SDL_RenderCopy(CrazyBattle::Game().Renderer(), m_texture->texture, &frameRect, &dstRect);

            break;
        }
    }
}
