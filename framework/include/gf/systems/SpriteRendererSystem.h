#pragma once

#include "gf/FrameworkExport.h"
#include "entityx/entityx.h"

#include <SDL.h>

namespace gf
{
    class SpriteRendererSystem : public entityx::System<SpriteRendererSystem>
    {
    public:
        SpriteRendererSystem();

        void update(entityx::EntityManager& entityManager, entityx::EventManager& events,
                    entityx::TimeDelta deltaTime) override;

    private:
        SDL_Texture* texture;
    };
}
