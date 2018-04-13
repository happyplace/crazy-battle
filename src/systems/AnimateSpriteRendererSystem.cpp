#include "AnimateSpriteRendererSystem.h"

#include "SpriteRendererHelper.h"

void AnimateSpriteRendererSystem::Render()
{
    for (const anax::Entity& entity : getEntities())
    {
        const AnimatedSpriteComponent& animatedSpriteComp = entity.getComponent<AnimatedSpriteComponent>();
        const TextureComponent& textureComp = entity.getComponent<TextureComponent>();
        const TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        if (!animatedSpriteComp.enabled)
        {
            continue;
        }

        if (animatedSpriteComp.spriteAnimationsAsset)
        {
            for (const SpriteAnimation& spriteAnimation : animatedSpriteComp.spriteAnimationsAsset->animations)
            {
                if (spriteAnimation.name.compare(animatedSpriteComp.animationName) == 0)
                {
                    const std::string& frameName = spriteAnimation.frames[animatedSpriteComp.animationParams.frame];
                    SpriteRendererHelper::RenderSpriteFrame(frameName, textureComp, transformComp, animatedSpriteComp.colour);
                    break;
                }
            }
        }
    }
}
