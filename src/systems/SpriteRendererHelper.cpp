#include "SpriteRendererHelper.h"

#include "CrazyBattle.h"
#include "components/TextureComponent.h"
#include "components/TransformComponent.h"

void SpriteRendererHelper::RenderSpriteFrame(const std::string& frameName, const TextureComponent& textureComp,
                                             const TransformComponent& transformComp)
{
    SDL_Rect renderQuad;
    SDL_Rect frameRect;

    SDL_assert(textureComp.texture);

    bool hasFrame = false;
    if (textureComp.textureFrames)
    {
        for (const TextureFrame& textureFrame : textureComp.textureFrames->frames)
        {
            if (textureFrame.name.compare(frameName) == 0)
            {
                hasFrame = true;
                frameRect.x = textureFrame.x;
                frameRect.y = textureFrame.y;
                frameRect.w = textureFrame.width;
                frameRect.h = textureFrame.height;
                break;
            }
        }
    }

    // TODO: use a texture missing asset

    renderQuad.x = static_cast<int>(transformComp.position.x);
    renderQuad.y = static_cast<int>(transformComp.position.y);
    renderQuad.w = hasFrame ? frameRect.w : textureComp.texture->width;
    renderQuad.h = hasFrame ? frameRect.h : textureComp.texture->height;

    renderQuad.w = static_cast<int>(renderQuad.w * transformComp.scale.x);
    renderQuad.h = static_cast<int>(renderQuad.h * transformComp.scale.y);

    SDL_RenderCopy(CrazyBattle::Game().Renderer(), textureComp.texture->texture, hasFrame ? &frameRect : nullptr, &renderQuad);
}
