#pragma once

#include <memory>

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

typedef std::shared_ptr<TextureAsset> TextureAssetPtr;
