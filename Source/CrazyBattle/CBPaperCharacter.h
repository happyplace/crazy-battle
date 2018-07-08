// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Attack.h"
#include "CBPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYBATTLE_API ACBPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ACBPaperCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void SetPlayerIndex(int32 playerIndex);
    int32 GetPlayerIndex() const { return m_playerIndex; }

    void OnDeath();
    bool IsDeadOrRespawning() const { return bDeadOrRespawning; }
    void OnRespawn();

private:
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void WalkPressed();
	void WalkReleased();
	void JumpPressed();
	bool HandleLanding();
	void AttackPressed();
	void AttackReleased();

	FVector2D RawMovementInput;
	bool bJumpPressed;
	bool bAttackPressed;
	
	bool bWasJumppingUpLastFrame;
	bool bWasJumppingLastFrame;
	bool bPlayingOneOffAnimation;
	bool bPrevAttackPressed;

    int32_t m_playerIndex;
    bool bDeadOrRespawning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* WalkAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* JumpUpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* JumpDownAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* JumpMidAirAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* JumpLandAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    class UPaperFlipbook* DeathAnimation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crazy Battle")
	TSubclassOf<AAttack> BasicAttack;
};
