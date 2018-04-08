#pragma once

#include <memory>
#include <vector>
#include <string>

#include <SDL.h>

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

typedef std::shared_ptr<TextureFramesAsset> TextureFramesAssetPtr;
typedef std::shared_ptr<TextureAsset> TextureAssetPtr;
