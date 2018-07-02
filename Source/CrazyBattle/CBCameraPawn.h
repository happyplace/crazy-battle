// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CBCameraPawn.generated.h"

UCLASS()
class CRAZYBATTLE_API ACBCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACBCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    class UArrowComponent* CameraDirection;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;
};
