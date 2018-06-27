// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAttack.h"

#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "CBPaperCharacter.h"

#include "Engine.h"

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

	FVector force(InitialAttackSpeed, 0.0f, 0.0f);
	Sphere->AddImpulse(force * Sphere->GetMass());

    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Overlap);;
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
		}
	}
}

void ABasicAttack::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (shouldDelete)
	{
		return;
	}

	ACBPaperCharacter* otherCharacter = Cast<ACBPaperCharacter>(OtherActor);

	if (otherCharacter != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Is Owner")));
	}
	else
	{
		shouldDelete = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Not Owner")));
	}
}
