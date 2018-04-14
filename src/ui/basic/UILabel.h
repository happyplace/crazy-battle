#pragma once

#include <string>

#include <SDL.h>

#include "AssetLoaderDefines.h"

class UILabel
{
public:
    explicit UILabel();
    ~UILabel();

    void SetFont(FontAssetPtr font);
    void SetText(const std::string& text);
    void SetTextColour(const SDL_Color& colour);
    void setHasShadow(bool value) { m_hasShadow = value; }
    void SetLineWrap(int lineWrap);

    void Render(int x, int y);

    SDL_Texture* GetTexture();
    int GetWidth();
    int GetHeight();

private:
    void Redraw();

    FontAssetPtr m_font;
    std::string m_text;
    bool m_dirty;
    SDL_Texture* m_texture;
    SDL_Texture* m_shadow;
    int m_width;
    int m_height;
    SDL_Color m_textColor;
    bool m_hasShadow;
    int m_lineWrap;
};
