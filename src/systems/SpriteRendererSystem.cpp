#include "SpriteRendererSystem.h"

#include "CrazyBattle.h"

void SpriteRendererSystem::Render()
{
    SDL_Rect renderQuad;
    SDL_Rect frameRect;
    for (const anax::Entity& entity : getEntities())
    {
        const SpriteComponent& spriteComp = entity.getComponent<SpriteComponent>();
        const TextureComponent& textureComp = entity.getComponent<TextureComponent>();
        const TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        SDL_assert(textureComp.texture);

        bool hasFrame = false;
        if (textureComp.textureFrames)
        {
            for (const TextureFrame& textureFrame : textureComp.textureFrames->frames)
            {
                if (textureFrame.name.compare(spriteComp.frameName) == 0)
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
}
