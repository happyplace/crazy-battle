// Fill out your copyright notice in the Description page of Project Settings.

#include "CBPaperCharacter.h"

#include "Components/InputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/PawnMovementComponent.h"

#include "Engine/World.h"

// Sets default values
ACBPaperCharacter::ACBPaperCharacter()
	: bWasJumppingUpLastFrame(false)
	, bWasJumppingLastFrame(false)
	, bPlayingOneOffAnimation(false)
	, bAttackPressed(false)
	, bPrevAttackPressed(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACBPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

    //CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    //CameraComponent->bUsePawnControlRotation = false;
    //CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
    //CameraComponent->OrthoWidth = 768.0f;

    //CameraComponent->SetWorldLocation(FVector(0.0f, 500.0f, 30.0f));
    //CameraComponent->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
    //CameraComponent->AttachToComponent(CapsuleComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

	if (!bPrevAttackPressed && bAttackPressed)
	{
		UWorld* world = GetWorld();

        FVector attackPosition = GetActorLocation();
        attackPosition.X += 30.0f;
        FTransform attackTransform;
        attackTransform.SetTranslation(attackPosition);

		AAttack* attack = Cast<AAttack>(world->SpawnActor(BasicAttack, &attackTransform));
		attack->SetOwningActor(GetUniqueID());
		attack->SetInitialDirection(FVector::ZeroVector);
	}

	bPrevAttackPressed = bAttackPressed;
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
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACBPaperCharacter::AttackPressed);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ACBPaperCharacter::AttackReleased);
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

void ACBPaperCharacter::AttackPressed()
{
	bAttackPressed = true;
}

void ACBPaperCharacter::AttackReleased()
{
	bAttackPressed = false;
}
