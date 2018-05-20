#include "gf/systems/SpriteRendererSystem.h"

#include <SDL_image.h>

#include "gf/components/SpriteComponent.h"
#include "gf/Renderer.h"

using namespace gf;

SpriteRendererSystem::SpriteRendererSystem()
{
    SDL_Surface* loadedSurface = IMG_Load("button_sprites.png");
    SDL_assert(loadedSurface);
    if (loadedSurface)
    {
        texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetRenderer(), loadedSurface);
        SDL_assert(texture);
        if (texture)
        {
            SDL_FreeSurface(loadedSurface);
        }
    }
}

void SpriteRendererSystem::update(entityx::EntityManager& entityManager,
                                  entityx::EventManager& events,
                                  entityx::TimeDelta deltaTime)
{
    SDL_RenderCopy(Renderer::GetInstance().GetRenderer(), texture, nullptr, nullptr);
}
