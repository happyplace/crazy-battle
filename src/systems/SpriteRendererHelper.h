#pragma once

#include <string>

#include "SDL.h"

struct TextureComponent;
struct TransformComponent;

namespace SpriteRendererHelper
{
    void RenderSpriteFrame(const std::string& frameName, const TextureComponent& textureComp,
                           const TransformComponent& transformComp, const SDL_Color& colour);
}
