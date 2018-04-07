#pragma once

#include "anax/Component.hpp"

#include "AssetLoaderDefines.h"

struct TextureComponent : anax::Component
{
    TextureAssetPtr texture;
};
