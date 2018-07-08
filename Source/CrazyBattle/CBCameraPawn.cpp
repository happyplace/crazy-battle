// Fill out your copyright notice in the Description page of Project Settings.

#include "CBCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"
#include "CBPaperCharacter.h"

// Sets default values
ACBCameraPawn::ACBCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void ACBCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
    FVector location = GetActorLocation();
    location.Y = 343.0;
    SetActorLocation(location);
    SetActorRotation(FRotator(0.0f, 270.0f, 0.0f));

    Camera->SetOrthoWidth(768.0f);
}

// Called every frame
void ACBCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    APlayerController* playerController = GetWorld()->GetFirstPlayerController();

    int32 followedPlayerCount = 0;
    FVector focusTarget = FVector::ZeroVector;
    float largestDistance = 0.0f;

    for (FConstPlayerControllerIterator playerIt = GetWorld()->GetPlayerControllerIterator(); playerIt; ++playerIt)
    {
        ACBPaperCharacter* paperCharacter = Cast<ACBPaperCharacter>(playerIt->Get()->GetPawn());
        if (paperCharacter && paperCharacter->IsDeadOrRespawning() == false)
        {
            focusTarget += paperCharacter->GetActorLocation();
            followedPlayerCount++;

            for (FConstPlayerControllerIterator otherPlayerIt = GetWorld()->GetPlayerControllerIterator(); otherPlayerIt; ++otherPlayerIt)
            {
                ACBPaperCharacter* otherPaperCharacter = Cast<ACBPaperCharacter>(otherPlayerIt->Get()->GetPawn());
                if (otherPaperCharacter && otherPaperCharacter->IsDeadOrRespawning() == false)
                {
                    float distance = FVector::Distance(paperCharacter->GetActorLocation(), otherPaperCharacter->GetActorLocation());
                    if (distance > largestDistance)
                    {
                        largestDistance = distance;
                    }
                }
            }
        }
    }

    if (followedPlayerCount > 0)
    {
        focusTarget /= followedPlayerCount;
        focusTarget.Y = GetActorLocation().Y;
        SetActorLocation(focusTarget);

        Camera->SetOrthoWidth(FMath::Lerp(768, 1200, largestDistance / 900.0f));
    }
}
