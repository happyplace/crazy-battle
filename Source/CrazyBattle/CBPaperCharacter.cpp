// Fill out your copyright notice in the Description page of Project Settings.

#include "CBPaperCharacter.h"

#include "Components/InputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ACBPaperCharacter::ACBPaperCharacter()
	: bWasJumppingUpLastFrame(false)
	, bWasJumppingLastFrame(false)
	, bPlayingOneOffAnimation(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACBPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACBPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector movementInput = FVector(RawMovementInput.X, 0.0f, 0.0f);
	AddMovementInput(movementInput.GetSafeNormal());

	if (movementInput.X > 0.01f)
	{
		GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (movementInput.X < -0.01f)
	{
		// yaw
		GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
	}

	if (bJumpPressed)
	{
		bJumpPressed = false;
		Jump();
	}

	if (bPlayingOneOffAnimation)
	{
		bWasJumppingLastFrame = false;
		if (!GetSprite()->IsPlaying())
		{
			bPlayingOneOffAnimation = false;
			GetSprite()->SetLooping(true);
			GetSprite()->PlayFromStart();
		}
	}

	if (!bPlayingOneOffAnimation)
	{
		if (GetMovementComponent()->IsFalling())
		{
			if (GetMovementComponent()->Velocity.Z > 0.0f)
			{
				GetSprite()->SetFlipbook(JumpUpAnimation);
			}
			else
			{
				if (bWasJumppingUpLastFrame)
				{
					GetSprite()->SetLooping(false);
					GetSprite()->SetFlipbook(JumpMidAirAnimation);
					GetSprite()->PlayFromStart();
					bPlayingOneOffAnimation = true;
				}
				else
				{
					GetSprite()->SetFlipbook(JumpDownAnimation);
				}
			}
			bWasJumppingUpLastFrame = GetMovementComponent()->Velocity.Z > 0.0f;
			bWasJumppingLastFrame = true;
		}
		else if (GetMovementComponent()->IsMovingOnGround() && fabsf(movementInput.X) > 0.5f)
		{
			if (!HandleLanding())
			{
				GetSprite()->SetFlipbook(RunAnimation);
			}
		}
		else if (GetMovementComponent()->IsMovingOnGround() && fabsf(movementInput.X) > 0.01f)
		{
			if (!HandleLanding())
			{
				GetSprite()->SetFlipbook(WalkAnimation);
			}
		}
		else
		{
			if (!HandleLanding())
			{
				GetSprite()->SetFlipbook(IdleAnimation);
			}
		}
	}
}

bool ACBPaperCharacter::HandleLanding()
{
	if (bWasJumppingLastFrame)
	{
		GetSprite()->SetLooping(false);
		GetSprite()->SetFlipbook(JumpLandAnimation);
		GetSprite()->PlayFromStart();
		bPlayingOneOffAnimation = true;
		return true;
	}
	bWasJumppingLastFrame = false;
	return false;
}

// Called to bind functionality to input
void ACBPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ACBPaperCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ACBPaperCharacter::MoveY);

	//PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACBPaperCharacter::WalkPressed);
	//PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACBPaperCharacter::WalkReleased);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACBPaperCharacter::JumpPressed);
}

void ACBPaperCharacter::MoveX(float AxisValue)
{
	RawMovementInput.X = AxisValue;
}

void ACBPaperCharacter::MoveY(float AxisValue)
{
	RawMovementInput.Y = AxisValue;
}

void ACBPaperCharacter::WalkPressed()
{
}

void ACBPaperCharacter::WalkReleased()
{
}

void ACBPaperCharacter::JumpPressed()
{
	bJumpPressed = true;
}
