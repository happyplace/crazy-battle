// Fill out your copyright notice in the Description page of Project Settings.

#include "CrazyBattleGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "CBPaperCharacter.h"
#include "Engine/World.h"
#include "PaperFlipbookComponent.h"
#include "CrazyBattleGameState.h"

ACrazyBattleGameMode::ACrazyBattleGameMode()
{
    PlayerColor0 = FLinearColor::White;
    PlayerColor1 = FLinearColor::Yellow;
    PlayerColor2 = FLinearColor::Blue;
    PlayerColor3 = FLinearColor::Green;

    initialDefaultClass = DefaultPawnClass;
}

void ACrazyBattleGameMode::BeginPlay()
{
    Super::BeginPlay();

    // The default player controller is set to the camera pawn, after that pawn is created
    // the default pawn is changed to the actual ACBPaperCharacter Pawn
    DefaultPawnClass = PlayerCharacter;
}

void ACrazyBattleGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);;

    DefaultPawnClass = initialDefaultClass;

    for (int i = 0; i < spawnedPlayerControllers.Num(); i++)
    {
        UGameplayStatics::RemovePlayer(spawnedPlayerControllers[i], true);
    }
    spawnedPlayerControllers.Empty();
    spawnedPlayersControllerId.Empty();
    
    UGameplayStatics::RemovePlayer(GetWorld()->GetFirstPlayerController(), true);
}

void ACrazyBattleGameMode::CreatePlayerForController(int32 ControllerId, int32 KeyboardIndex /*= -1*/)
{
    if (spawnedPlayersControllerId.Find(ControllerId) != INDEX_NONE)
    {
        return;
    }

    int32 playerIndex = spawnedPlayersControllerId.Add(ControllerId);

    APlayerController* player = UGameplayStatics::CreatePlayer(GetWorld(), ControllerId, true);
    check(player);

    spawnedPlayerControllers.Add(player);
    
    player->SetViewTarget(GetWorld()->GetFirstPlayerController());
    ACBPaperCharacter* playerCharacter = Cast<ACBPaperCharacter>(player->GetPawn());
    check(playerCharacter);
    playerCharacter->SetPlayerIndex(playerIndex);
    playerCharacter->GetSprite()->SetSpriteColor(GetPlayerColourForIndex(playerIndex));
    playerCharacter->SetKeyboardIndex(KeyboardIndex);
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

void ACrazyBattleGameMode::OnPlayerAttacked(AttackType attackType, int32 attackerIndex, int32 receiverIndex)
{
    ACrazyBattleGameState* gameState = GetGameState<ACrazyBattleGameState>();
    gameState->OnPlayerDamaged(15.0f, attackerIndex, receiverIndex);
}

int32 ACrazyBattleGameMode::GetControllerIdForPlayerIndex(int32 playerIndex) const
{
    // TODO: check that it's within bounds
    return spawnedPlayersControllerId[playerIndex];
}

int32 ACrazyBattleGameMode::GetSpawnedPlayerNum()
{
    return spawnedPlayersControllerId.Num();
}

bool ACrazyBattleGameMode::DoesPlayerUsingKeyboardIndexExist(int32 KeyboardIndex) const
{
    for (int32 i = 0; i < keyboardPlayers.Num(); i++)
    {
        if (keyboardPlayers[i].KeyboardIndex == KeyboardIndex)
        {
            return true;
        }
    }
    return false;
}
