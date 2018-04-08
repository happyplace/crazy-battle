#pragma once

#include "anax/System.hpp"

#include "components/AnimatedSpriteComponent.h"
#include "components/TextureComponent.h"
#include "components/TransformComponent.h"

class AnimateSpriteRendererSystem : public anax::System<anax::Requires<AnimatedSpriteComponent, TextureComponent, TransformComponent>>
{
public:
    void Render();
};
