// Fill out your copyright notice in the Description page of Project Settings.

#include "CrazyBattleGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "CBPaperCharacter.h"
#include "Engine/World.h"

void ACrazyBattleGameMode::BeginPlay()
{
    Super::BeginPlay();

    // The default player controller is set to the camera pawn, after that pawn is created
    // the default pawn is changed to the actual ACBPaperCharacter Pawn
    DefaultPawnClass = PlayerCharacter;
}

#include "Engine.h"

void ACrazyBattleGameMode::CreatePlayerForController(int32 ControllerId)
{
    if (spawnedPlayersControllerId.Find(ControllerId) != INDEX_NONE)
    {
        return;
    }

    spawnedPlayersControllerId.Add(ControllerId);

    APlayerController* player = UGameplayStatics::CreatePlayer(GetWorld(), ControllerId, true);
    player->SetViewTarget(GetWorld()->GetFirstPlayerController());
}
