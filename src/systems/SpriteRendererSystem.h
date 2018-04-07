#pragma once

#include "anax/System.hpp"

#include "components/SpriteComponent.h"
#include "components/TextureComponent.h"
#include "components/TransformComponent.h"

class SpriteRendererSystem : public anax::System<anax::Requires<SpriteComponent, TextureComponent, TransformComponent>>
{
public:
    void Render();
};
