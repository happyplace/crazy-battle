#pragma once

#include "anax/System.hpp"

#include "components/TransformComponent.h"
#include "components/ChildComponent.h"

class ChildTransformSystem : public anax::System<anax::Requires<TransformComponent, ChildComponent>>
{
public:
	void Update();
};
