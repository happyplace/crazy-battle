#pragma once

#include <memory>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

struct TextureAsset
{
    ~TextureAsset()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    SDL_Texture* texture;
    int width;
    int height;

private:
    TextureAsset() : texture(nullptr), width(0), height(0) {}

    friend class AssetLoaderHelper;
};

struct TextureFrame
{
    std::string name;
    int x;
    int y;
    int width;
    int height;
};

struct TextureFramesAsset
{
    std::vector<TextureFrame> frames;

private:
    TextureFramesAsset() {}

    friend class AssetLoaderHelper;
};

struct SpriteAnimation
{
    std::string name;
    float speed;
    std::vector<std::string> frames;
};

struct SpriteAnimationsAsset
{
    std::vector<SpriteAnimation> animations;

private:
    SpriteAnimationsAsset() {}

    friend class AssetLoaderHelper;
};

struct TextAsset
{
    std::string text;

private:
    TextAsset() {}

    friend class AssetLoaderHelper;
};

struct FontAsset
{
    ~FontAsset()
    {
        if (font)
        {
            TTF_CloseFont(font);
            font = nullptr;
        }
    }

    TTF_Font* font;
    int size;

private:
    FontAsset() : font(nullptr), size(0) {}

    friend class AssetLoaderHelper;
};

typedef std::shared_ptr<TextureFramesAsset> TextureFramesAssetPtr;
typedef std::shared_ptr<TextureAsset> TextureAssetPtr;
typedef std::shared_ptr<SpriteAnimationsAsset> SpriteAnimationsAssetPtr;
typedef std::shared_ptr<FontAsset> FontAssetPtr;
typedef std::shared_ptr<TextAsset> TextAssetPtr;
