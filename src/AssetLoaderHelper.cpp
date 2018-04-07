#include "AssetLoaderHelper.h"

#include <SDL_image.h>

#include "CrazyBattle.h"

const TextureAssetPtr AssetLoaderHelper::LoadTexture(const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to load image %s SDL_image Error: %s", path, IMG_GetError());
        return nullptr;
    }
    else
    {
        TextureAssetPtr textureAsset(new TextureAsset());
        textureAsset->texture = SDL_CreateTextureFromSurface(CrazyBattle::Game().Renderer(), loadedSurface);
        if (textureAsset->texture == nullptr)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from %s SDL_Error: %s", path, SDL_GetError());
            return nullptr;
        }
        textureAsset->width = loadedSurface->w;
        textureAsset->height = loadedSurface->h;
        SDL_FreeSurface(loadedSurface);
        return textureAsset;
    }
}
