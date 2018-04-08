#include "SpriteRendererSystem.h"

#include "systems/SpriteRendererHelper.h"

void SpriteRendererSystem::Render()
{
    for (const anax::Entity& entity : getEntities())
    {
        const SpriteComponent& spriteComp = entity.getComponent<SpriteComponent>();
        const TextureComponent& textureComp = entity.getComponent<TextureComponent>();
        const TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        SpriteRendererHelper::RenderSpriteFrame(spriteComp.frameName, textureComp, transformComp);
    }
}
