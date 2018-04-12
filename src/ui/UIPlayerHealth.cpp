#include "UIPlayerHealth.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"

UIPlayerHealth::UIPlayerHealth()
{
    const char* fontPath = "media/helmet2/Helmet-Regular.ttf";
    m_font = TTF_OpenFont(fontPath, 100);
    if (m_font == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "failed to load font '%s' SDL_ttf Error: %s", fontPath, TTF_GetError());
    }

    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    //m_spriteAnimations = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");

    m_label.SetFont(m_font);
    m_label.SetText("100%");
}

UIPlayerHealth::~UIPlayerHealth()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

void UIPlayerHealth::Render()
{
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
