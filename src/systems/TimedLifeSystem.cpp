#include "TimedLifeSystem.h"

#include "GameTimer.h"

void TimedLifeSystem::Update(const GameTimer& gameTimer)
{
    for (anax::Entity entity : getEntities())
    {
        TimedLifeComponent& timedLifeComp = entity.getComponent<TimedLifeComponent>();
        timedLifeComp.timeLeftToKeepAlive -= static_cast<float>(gameTimer.DeltaTime());
        if (timedLifeComp.timeLeftToKeepAlive <= 0.0f)
        {
            entity.kill();
        }
    }
}
