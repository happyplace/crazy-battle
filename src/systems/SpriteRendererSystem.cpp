#include "SpriteRendererSystem.h"

#include "CrazyBattle.h"

void SpriteRendererSystem::Render()
{
    SDL_Rect renderQuad;
    for (const anax::Entity& entity : getEntities())
    {
        const SpriteComponent spriteComp = entity.getComponent<SpriteComponent>();
        const TextureAssetPtr textureAsset = entity.getComponent<TextureComponent>().texture;
        const TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        SDL_assert(textureAsset);
        // TODO: use a texture missing asset

        renderQuad.x = static_cast<int>(transformComp.position.x);
        renderQuad.y = static_cast<int>(transformComp.position.y);
        renderQuad.w = static_cast<int>(textureAsset->width * transformComp.scale.x);
        renderQuad.h = static_cast<int>(textureAsset->height * transformComp.scale.y);
        SDL_RenderCopy(CrazyBattle::Game().Renderer(), textureAsset->texture, nullptr, &renderQuad);
    }
}
