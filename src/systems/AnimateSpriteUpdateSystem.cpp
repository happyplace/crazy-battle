﻿#include "AnimateSpriteUpdateSystem.h"

#include "GameTimer.h"

void AnimateSpriteUpdateSystem::Update(const GameTimer& gameTimer)
{
    for (const anax::Entity& entity : getEntities())
    {
        AnimatedSpriteComponent& animatedSpriteComp = entity.getComponent<AnimatedSpriteComponent>();

        if (animatedSpriteComp.spriteAnimationsAsset)
        {
            for (const SpriteAnimation& spriteAnimation : animatedSpriteComp.spriteAnimationsAsset->animations)
            {
                if (spriteAnimation.name.compare(animatedSpriteComp.animationName) == 0)
                {
                    animatedSpriteComp.animationParams.timeOnFrame += static_cast<float>(gameTimer.DeltaTime());
                    if (animatedSpriteComp.animationParams.timeOnFrame >= spriteAnimation.speed)
                    {
                        animatedSpriteComp.animationParams.frame++;
                        animatedSpriteComp.animationParams.timeOnFrame = 0.0f;
                        if (animatedSpriteComp.animationParams.frame >= spriteAnimation.frames.size())
                        {
                            animatedSpriteComp.animationParams.frame = 0;
                        }
                    }
                    break;
                }
            }
        }
    }
}