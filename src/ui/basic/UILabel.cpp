#include "UILabel.h"

#include "CrazyBattle.h"

UILabel::UILabel()
    : m_font(nullptr)
    , m_dirty(true)
    , m_texture(nullptr)
    , m_width(0)
    , m_height(0)
{
}

UILabel::~UILabel()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

void UILabel::SetFont(TTF_Font* font)
{
    if (m_font != font)
    {
        m_font = font;
        m_dirty = true;
    }
}

void UILabel::SetText(const std::string& text)
{
    if (text.compare(m_text) != 0)
    {
        m_text = text;
        m_dirty = true;
    }
}

SDL_Texture* UILabel::GetTexture()
{
    Redraw();
    return m_texture;
}

int UILabel::GetWidth()
{
    Redraw();
    return m_width;
}

int UILabel::GetHeight()
{
    Redraw();
    return m_height;
}

void UILabel::Redraw()
{
    if (!m_dirty || !m_font)
    {
        return;
    }

    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), textColor);
    if (textSurface == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "unable to render text surface SDL_ttf Error: %s", TTF_GetError());
    }
    else
    {
        m_texture = SDL_CreateTextureFromSurface(CrazyBattle::Game().Renderer(), textSurface);
        if (m_texture == nullptr)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from rendered text. SDL Error: %s", SDL_GetError());
        }
        m_width = textSurface->w;
        m_height = textSurface->h;
        SDL_FreeSurface(textSurface);
    }

    m_dirty = false;
}
