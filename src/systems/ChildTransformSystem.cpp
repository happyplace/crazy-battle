#include "ChildTransformSystem.h"

#include "anax/World.hpp"

using namespace anax;

void ChildTransformSystem::Update()
{
	for (const Entity& entity : getEntities())
	{
		const ChildComponent& childComp = entity.getComponent<ChildComponent>();
		TransformComponent& transformComp = entity.getComponent<TransformComponent>();

        if (!childComp.parentEntity.isActivated())
		{
			getWorld().getEntity(entity.getId().index).kill();
		}
		else
		{
            const TransformComponent& parentTransformComp = childComp.parentEntity.getComponent<TransformComponent>();
			transformComp.position.x = parentTransformComp.position.x;
			transformComp.position.y = parentTransformComp.position.y;
			transformComp.rotation = parentTransformComp.rotation; 
		}
	}
}
