#include "AssetLoaderHelper.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <SDL_image.h>
#include "rapidjson/document.h"

#include "CrazyBattle.h"

using namespace rapidjson;

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

const TextureFramesAssetPtr AssetLoaderHelper::LoadTextureFrames(const char* path)
{
    std::ifstream myfile(path);
    if (myfile.is_open())
    {
        std::string line;
        std::stringstream jsonFrame;
        while (getline(myfile, line))
        {
            jsonFrame << line;
        }
        myfile.close();

        Document textureFramesDoc;
        textureFramesDoc.Parse(jsonFrame.str().c_str());

        TextureFramesAssetPtr textureFramesAsset(new TextureFramesAsset());

        TextureFrame frame;
        const Value& frames = textureFramesDoc["frames"];
        for (SizeType i = 0; i < frames.Size(); i++)
        {
            frame.name = frames[i]["filename"].GetString();
            frame.x = frames[i]["frame"]["x"].GetInt();
            frame.y = frames[i]["frame"]["y"].GetInt();
            frame.width = frames[i]["frame"]["w"].GetInt();
            frame.height = frames[i]["frame"]["h"].GetInt();
            textureFramesAsset->frames.push_back(frame);
        }
        return textureFramesAsset;
    }
    return nullptr;
}

const SpriteAnimationsAssetPtr AssetLoaderHelper::LoadSpriteAnimations(const char* path)
{
    std::ifstream myfile(path);
    if (myfile.is_open())
    {
        std::string line;
        std::stringstream spriteAnimations;
        while (getline(myfile, line))
        {
            spriteAnimations << line;
        }
        myfile.close();

        Document spriteAnimationDoc;
        spriteAnimationDoc.Parse(spriteAnimations.str().c_str());

        SpriteAnimationsAssetPtr spriteAnimationAsset(new SpriteAnimationsAsset());

        for (SizeType i = 0; i < spriteAnimationDoc.Size(); i++)
        {
            SpriteAnimation animation;
            animation.name = spriteAnimationDoc[i]["name"].GetString();
            animation.speed = spriteAnimationDoc[i]["speed"].GetFloat();
            const Value& frames = spriteAnimationDoc[i]["frames"];
            for (SizeType k = 0; k < frames.Size(); k++)
            {
                animation.frames.push_back(frames[k].GetString());
            }
            spriteAnimationAsset->animations.push_back(animation);
        }
        return spriteAnimationAsset;
    }
    return nullptr;
}
