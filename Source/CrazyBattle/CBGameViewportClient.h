// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "CBGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYBATTLE_API UCBGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
    virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamePad = false) override;
    virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamePad = false) override;
};
