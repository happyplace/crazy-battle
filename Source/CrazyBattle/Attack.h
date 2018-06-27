// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attack.generated.h"

UCLASS()
class CRAZYBATTLE_API AAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetInitialDirection(const FVector& value) { InitialDirection = value; }
	void SetOwningActor(uint32 value) { OwningActorUniqueId = value; }
	uint32 GetOwningActor() { return OwningActorUniqueId; }

private:
	FVector InitialDirection;
	uint32 OwningActorUniqueId;
};
