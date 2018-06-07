// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CBPawn.generated.h"

USTRUCT(BlueprintType)
struct FCBPawnInput
{
	GENERATED_BODY()

public:
	// Sanitized movement input
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Input")
	FVector2D MovementInput;

	void Sanitize();
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

private:
	FVector2D RawMovementInput;
};

UCLASS()
class CRAZYBATTLE_API ACBPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACBPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	FCBPawnInput CBPawnInput;

private:
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

private:
	// Sprite for the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* WalkAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
};