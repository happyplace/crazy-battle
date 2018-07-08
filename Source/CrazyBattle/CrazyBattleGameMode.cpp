// Fill out your copyright notice in the Description page of Project Settings.

#include "CrazyBattleGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "CBPaperCharacter.h"
#include "Engine/World.h"
#include "PaperFlipbookComponent.h"

ACrazyBattleGameMode::ACrazyBattleGameMode()
{
    PlayerColor0 = FLinearColor::White;
    PlayerColor1 = FLinearColor::Yellow;
    PlayerColor2 = FLinearColor::Blue;
    PlayerColor3 = FLinearColor::Green;
}

void ACrazyBattleGameMode::BeginPlay()
{
    Super::BeginPlay();

    // The default player controller is set to the camera pawn, after that pawn is created
    // the default pawn is changed to the actual ACBPaperCharacter Pawn
    DefaultPawnClass = PlayerCharacter;
}

void ACrazyBattleGameMode::CreatePlayerForController(int32 ControllerId)
{
    if (spawnedPlayersControllerId.Find(ControllerId) != INDEX_NONE)
    {
        return;
    }

    int32 playerIndex = spawnedPlayersControllerId.Add(ControllerId);

    APlayerController* player = UGameplayStatics::CreatePlayer(GetWorld(), ControllerId, true);
    player->SetViewTarget(GetWorld()->GetFirstPlayerController());
    ACBPaperCharacter* playerCharacter = Cast<ACBPaperCharacter>(player->GetPawn());
    check(playerCharacter);
    playerCharacter->SetPlayerIndex(playerIndex);
    playerCharacter->GetSprite()->SetSpriteColor(GetPlayerColourForIndex(playerIndex));
}

FLinearColor ACrazyBattleGameMode::GetPlayerColourForIndex(int32 playerIndex)
{
    switch (playerIndex)
    {
        case 0:
            return PlayerColor0;
        case 1:
            return PlayerColor1;
        case 2:
            return PlayerColor2;
        case 3:
            return PlayerColor3;
        default:
            return FLinearColor::Black;
    }
}

#include "CrazyBattleGameState.h"

void ACrazyBattleGameMode::OnPlayerAttacked(AttackType attackType, int32 attackerIndex, int32 receiverIndex)
{
    ACrazyBattleGameState* gameState = GetGameState<ACrazyBattleGameState>();
    gameState->OnPlayerDamaged(15.0f, attackerIndex, receiverIndex);
}
