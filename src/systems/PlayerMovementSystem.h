#pragma once

#include "anax/System.hpp"

#include "components/PlayerComponent.h"

class PlayerMovementSystem : public anax::System<anax::Requires<PlayerComponent>>
{
public:
    void Update();
};
