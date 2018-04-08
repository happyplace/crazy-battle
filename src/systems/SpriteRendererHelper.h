#pragma once

#include <string>

struct TextureComponent;
struct TransformComponent;

namespace SpriteRendererHelper
{
    void RenderSpriteFrame(const std::string& frameName, const TextureComponent& textureComp,
                           const TransformComponent& transformComp);
}
