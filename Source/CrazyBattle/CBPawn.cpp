// Fill out your copyright notice in the Description page of Project Settings.

#include "CBPawn.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#include "Engine.h"

void FCBPawnInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	MovementInput *= bWalkPressed ? 0.5f : 1.0f;
	RawMovementInput.Set(0.0f, 0.0f);
}

void FCBPawnInput::MoveX(float AxisValue)
{
	RawMovementInput.X += AxisValue;
}

void FCBPawnInput::MoveY(float AxisValue)
{
	RawMovementInput.Y += AxisValue;
}

void FCBPawnInput::WalkPressed()
{
	bWalkPressed = true;
}

void FCBPawnInput::WalkReleased()
{
	bWalkPressed = false;
}

// Sets default values
ACBPawn::ACBPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapculeComponent"));
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->bIgnoreRadialForce = true;
	CapsuleComponent->bIgnoreRadialImpulse = true;
	CapsuleComponent->AttachTo(RootComponent);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->AttachTo(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 768.0f;
	
	float aspectRatio = 3.0f / 4.0f;
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		aspectRatio = ViewportSize.Y / ViewportSize.X;
	}
	CameraComponent->AspectRatio = aspectRatio;

	CameraComponent->SetWorldLocation(FVector(0.0f, 500.0f, 30.0f));
	CameraComponent->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	CameraComponent->AttachToComponent(CapsuleComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACBPawn::BeginPlay()
{
	Super::BeginPlay();

	Flipbook->SetFlipbook(IdleAnimation);
}

// Called every frame
void ACBPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CBPawnInput.Sanitize();

	float MoveSpeed = 500.0f;

	FVector Pos(MoveSpeed * DeltaTime * CBPawnInput.MovementInput.X, 0.0f, 0.0f);

	CapsuleComponent->AddWorldOffset(Pos);

	if (CBPawnInput.MovementInput.X > 0.1f)
	{
		Flipbook->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (CBPawnInput.MovementInput.X < -0.1f)
	{
		// yaw
		Flipbook->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
	}

	if (FMath::Abs(CBPawnInput.MovementInput.X) > 0.51f)
	{
		Flipbook->SetFlipbook(RunAnimation);
	}
	else if (FMath::Abs(CBPawnInput.MovementInput.X) > 0.01f)
	{
		Flipbook->SetFlipbook(WalkAnimation);
	}
	else
	{
		Flipbook->SetFlipbook(IdleAnimation);
	}
}

// Called to bind functionality to input
void ACBPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ACBPawn::MoveX);
	InputComponent->BindAxis("MoveY", this, &ACBPawn::MoveY);

	InputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACBPawn::WalkPressed);
	InputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACBPawn::WalkReleased);
}

void ACBPawn::MoveX(float AxisValue)
{
	CBPawnInput.MoveX(AxisValue);
}

void ACBPawn::MoveY(float AxisValue)
{
	CBPawnInput.MoveY(AxisValue);
}

void ACBPawn::WalkPressed()
{
	CBPawnInput.WalkPressed();
}

void ACBPawn::WalkReleased()
{
	CBPawnInput.WalkReleased();
}
