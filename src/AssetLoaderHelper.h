#pragma once

#include "AssetLoaderDefines.h"

class AssetLoaderHelper
{
public:
    static const TextureAssetPtr LoadTexture(const char* path);
    static const TextureFramesAssetPtr LoadTextureFrames(const char* path);
    static const SpriteAnimationsAssetPtr LoadSpriteAnimations(const char* path);
    static const FontAssetPtr LoadFont(const char* path, int size);
    static const TextAssetPtr LoadText(const char* path);
};
