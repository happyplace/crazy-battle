#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class UILabel
{
public:
    explicit UILabel();
    ~UILabel();

    void SetFont(TTF_Font* font);
    void SetText(const std::string& text);

    SDL_Texture* GetTexture();
    int GetWidth();
    int GetHeight();

private:
    void Redraw();

    TTF_Font* m_font;
    std::string m_text;
    bool m_dirty;
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
};
