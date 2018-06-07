// Fill out your copyright notice in the Description page of Project Settings.

#include "CBPawn.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Engine.h"

void FCBPawnInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
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

// Sets default values
ACBPawn::ACBPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->AttachTo(RootComponent);

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
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

	FVector Pos = GetActorLocation();
	Pos.X += 500.0f * DeltaTime * CBPawnInput.MovementInput.X;
	SetActorLocation(Pos);

	if (FMath::Abs(CBPawnInput.MovementInput.X) > 0.1f)
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
}

void ACBPawn::MoveX(float AxisValue)
{
	CBPawnInput.MoveX(AxisValue);
}

void ACBPawn::MoveY(float AxisValue)
{
	CBPawnInput.MoveY(AxisValue);
}
