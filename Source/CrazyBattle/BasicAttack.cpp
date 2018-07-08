// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAttack.h"

#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "CBPaperCharacter.h"
#include "CrazyBattleGameMode.h"
#include "Engine/World.h"

//#include "Engine.h"

ABasicAttack::ABasicAttack()
{
	shouldDelete = false;
	playingExplosionAnimation = false;

	InitialAttackSpeed = 100.0f;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSimulatePhysics(true);
	Sphere->SetEnableGravity(false);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = Sphere;

	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbook"));
	PaperFlipbook->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABasicAttack::BeginPlay()
{
	Super::BeginPlay();

	Sphere->bGenerateOverlapEvents = true;
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABasicAttack::OnBeginOverlap);
}

void ABasicAttack::Fire()
{
    FVector force = GetInitialDirection() * InitialAttackSpeed * Sphere->GetMass();
    Sphere->AddImpulse(force * Sphere->GetMass());

    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Overlap);

    switch (GetOwningPlayerIndex())
    {
        case 0:
            Sphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
            Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
            break;
        case 1:
            Sphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
            Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
            break;
        case 2:
            Sphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
            Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
            break;
        case 3:
            Sphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4);
            Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);
            break;
    }

    ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());
    PaperFlipbook->SetSpriteColor(gameMode->GetPlayerColourForIndex(GetOwningPlayerIndex()));
}

void ABasicAttack::SetColour(const FLinearColor& color)
{
    PaperFlipbook->SetSpriteColor(color);
}

void ABasicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (shouldDelete)
	{
		if (playingExplosionAnimation)
		{
            Sphere->SetPhysicsLinearVelocity(FVector::ZeroVector);
            Sphere->Deactivate();
			if (!PaperFlipbook->IsPlaying())
			{
				Destroy();
			}
		}
		else
		{
			playingExplosionAnimation = true;
			PaperFlipbook->SetLooping(false);
			PaperFlipbook->SetFlipbook(ExplosionAnimation);
            PaperFlipbook->SetSpriteColor(FLinearColor::White);
		}
	}
}

void ABasicAttack::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (shouldDelete || GetOwningPlayerIndex() < 0)
	{
		return;
	}

	ACBPaperCharacter* otherCharacter = Cast<ACBPaperCharacter>(OtherActor);

	if (otherCharacter != nullptr)
	{
        if (otherCharacter->IsDeadOrRespawning() == false && 
            otherCharacter->GetPlayerIndex() != GetOwningPlayerIndex())
        {         
            ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());
            gameMode->OnPlayerAttacked(ACrazyBattleGameMode::AttackType::BasicAttack, GetOwningPlayerIndex(), otherCharacter->GetPlayerIndex());
            shouldDelete = true;

            //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Format(TEXT("Basic Attack: Owner: {0} Other: {1}"), { otherCharacter->GetPlayerIndex(), GetOwningPlayerIndex() }));
            // Tell game mode that it got attacked
        }
	}
    else
    {
        shouldDelete = true;
    }
}
