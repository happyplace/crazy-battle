#include "UIRendererHelper.h"

#include "AssetLoaderHelper.h"
#include "CrazyBattle.h"

void UIRendererHelper::RenderTextureFrame(int x, int y, const char* frameName, TextureAssetPtr texture,
                                          TextureFramesAssetPtr frames, float scaleX /*= 1.0f*/, float scaleY /*= 1.0f*/)
{
    SDL_Rect frameRect;
    for (const TextureFrame& textureFrame : frames->frames)
    {
        if (strcmp(textureFrame.name.c_str(), frameName) == 0)
        {
            frameRect.x = textureFrame.x;
            frameRect.y = textureFrame.y;
            frameRect.w = textureFrame.width;
            frameRect.h = textureFrame.height;

            SDL_Rect dstRect;
            dstRect.w = textureFrame.width * scaleX;
            dstRect.h = textureFrame.height * scaleY;
            dstRect.x = x;
            dstRect.y = y;

            SDL_RenderCopy(CrazyBattle::Game().Renderer(), texture->texture, &frameRect, &dstRect);

            break;
        }
    }
}
