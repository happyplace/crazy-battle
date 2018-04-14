#include "UILabel.h"

#include "CrazyBattle.h"

UILabel::UILabel()
    : m_font(nullptr)
    , m_dirty(true)
    , m_texture(nullptr)
    , m_width(0)
    , m_height(0)
    , m_textColor({ 255, 255, 255, 255 })
    , m_shadow(nullptr)
    , m_hasShadow(true)
    , m_lineWrap(-1)
{
}

UILabel::~UILabel()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    if (m_shadow)
    {
        SDL_DestroyTexture(m_shadow);
        m_shadow = nullptr;
    }
}

void UILabel::SetFont(FontAssetPtr font)
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

void UILabel::SetTextColour(const SDL_Color& colour)
{
    if (colour.r != m_textColor.r ||
        colour.g != m_textColor.g ||
        colour.b != m_textColor.b ||
        colour.a != m_textColor.a)
    {
        m_textColor = colour;
        m_dirty = true;
    }
}

void UILabel::SetLineWrap(int lineWrap)
{
    if (lineWrap != m_lineWrap)
    {
        m_lineWrap = lineWrap;
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

    if (m_shadow)
    {
        SDL_DestroyTexture(m_shadow);
        m_shadow = nullptr;
    }

    SDL_Surface* textSurface = nullptr;
    if (m_lineWrap > 0)
        textSurface = TTF_RenderText_Blended_Wrapped(m_font->font, m_text.c_str(), m_textColor, static_cast<Uint32>(m_lineWrap));
    else
        textSurface = TTF_RenderText_Solid(m_font->font, m_text.c_str(), m_textColor);
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

    if (m_lineWrap > 0)
        textSurface = TTF_RenderText_Blended_Wrapped(m_font->font, m_text.c_str(), {0x00, 0x00, 0x00, 0xff}, static_cast<Uint32>(m_lineWrap));
    else
        textSurface = TTF_RenderText_Solid(m_font->font, m_text.c_str(), {0x00, 0x00, 0x00, 0xff});
    if (textSurface == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "unable to render text surface SDL_ttf Error: %s", TTF_GetError());
    }
    else
    {
        m_shadow = SDL_CreateTextureFromSurface(CrazyBattle::Game().Renderer(), textSurface);
        if (m_shadow == nullptr)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from rendered text. SDL Error: %s", SDL_GetError());
        }
        m_width = textSurface->w;
        m_height = textSurface->h;
        SDL_FreeSurface(textSurface);
    }

    m_dirty = false;
}

void UILabel::Render(int x, int y)
{
    Redraw();
    SDL_Rect renderQuad;
    renderQuad.w = m_width;
    renderQuad.h = m_height;

    if (m_hasShadow)
    {
        renderQuad.x = x + 5;
        renderQuad.y = y + 5;
        SDL_RenderCopy(CrazyBattle::Game().Renderer(), m_shadow, nullptr, &renderQuad);
    }

    renderQuad.x = x;
    renderQuad.y = y;
    SDL_RenderCopy(CrazyBattle::Game().Renderer(), m_texture, nullptr, &renderQuad);

}
