// Fill out your copyright notice in the Description page of Project Settings.

#include "CBCameraController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

#include "Engine/World.h"

// Sets default values
ACBCameraController::ACBCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CameraDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Root"));
    RootComponent = CameraDirection;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->AttachToComponent(CameraDirection, FAttachmentTransformRules::KeepRelativeTransform);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(1024.0f);
    Camera->SetAspectRatio(1920.0f / 1080.0f);
    Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ACBCameraController::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
}

// Called every frame
void ACBCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    APlayerController* playerController = GetWorld()->GetFirstPlayerController();
    FVector playerLocation = playerController->GetPawn()->GetActorLocation();
    playerLocation.Y = GetActorLocation().Y;
    SetActorLocation(playerLocation);

    Camera->SetOrthoWidth(768.0f);

}

