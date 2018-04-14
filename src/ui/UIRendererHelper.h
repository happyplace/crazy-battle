#pragma once

#include "AssetLoaderDefines.h"

namespace UIRendererHelper
{
void RenderTextureFrame(int x, int y, const char* frameName, TextureAssetPtr texture, TextureFramesAssetPtr Frames, float scaleX = 1.0f, float scaleY = 1.0f, SDL_Color color = { 0xff, 0xff, 0xff, 0xff });
}
