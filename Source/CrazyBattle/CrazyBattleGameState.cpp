// Fill out your copyright notice in the Description page of Project Settings.

#include "CrazyBattleGameState.h"

#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "CBPaperCharacter.h"
#include "CrazyBattleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CrazyBattleGameInstance.h"

ACrazyBattleGameState::ACrazyBattleGameState()
    : state(ECrazyBattleGameState::CBGS_Lobby)
{
    PrimaryActorTick.bCanEverTick = true;

    InitialPlayerHealth = 100.0f;
    RespawnTime = 5.0f;
}

void ACrazyBattleGameState::BeginPlay()
{
    Super::BeginPlay();

    state = ECrazyBattleGameState::CBGS_Lobby;

    playerData.Empty();
    for (int32 i = 0; i < 4; i++)
    {
        playerData.Emplace();
    }

    for (int32 i = 0; i < playerData.Num(); i++)
    {
        playerData[i].Lives = 0;
    }
}

void ACrazyBattleGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (state)
    {
        case ECrazyBattleGameState::CBGS_Lobby:
            Tick_Lobby(DeltaTime);
            break;
        case ECrazyBattleGameState::CBGS_Game:
            Tick_Game(DeltaTime);
            break;
        case ECrazyBattleGameState::CBGS_EndGame:
            Tick_EndGame(DeltaTime);
            break;
    }
}

void ACrazyBattleGameState::Tick_Lobby(float DeltaTime)
{

}

namespace ACrazyBattleGameState_private
{
    FPlayerScoreCard& GetPlayerScoreCardForPlayerIndex(UCrazyBattleGameInstance* gameInstance, int32 index)
    {
        switch (index)
        {
            case 0: 
                return gameInstance->Player0;
            case 1:
                return gameInstance->Player1;
            case 2:
                return gameInstance->Player2;
            case 3:
                return gameInstance->Player3;
            default:
            {
                static FPlayerScoreCard emptyScoreCard;
                return emptyScoreCard;
            }
        }
    }
}

void ACrazyBattleGameState::Tick_Game(float DeltaTime)
{
    int32 playersAlive = 0;

    for (int32 i = 0; i < playerData.Num(); i++)
    {
        if (playerData[i].PlayerState == EPlayerDataState::PDS_Respawn)
        {
            playerData[i].DealthTimer -= DeltaTime;
            if (playerData[i].DealthTimer <= 0.0f)
            {
                playerData[i].PlayerState = EPlayerDataState::PDS_Idle;
                playerData[i].PlayerHealth = InitialPlayerHealth;
                if (ACBPaperCharacter* paperCharacter = GetPaperCharacter(i))
                {
                    paperCharacter->SetActorLocation(FVector(260.0f, 0.0f, 28.0f));
                    paperCharacter->OnRespawn();
                }
            }
        }

        if (playerData[i].PlayerState != EPlayerDataState::PDS_Dead)
        {
            playersAlive++;
        }
    }

    ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());
  
    int32 actualPlayersAlive = (playersAlive - (4 - gameMode->GetSpawnedPlayerNum()));

    if (actualPlayersAlive <= 1)
    {
        bool hasWinner = actualPlayersAlive == 1;

        UCrazyBattleGameInstance* gameInstance = Cast<UCrazyBattleGameInstance>(GetGameInstance());
        if (gameInstance)
        {
            if (hasWinner)
            {
                int cardIndex = 1;
                for (int32 i = 0; i < playerData.Num(); i++)
                {
                    if (playerData[i].PlayerState != EPlayerDataState::PDS_Dead)
                    {
                        FPlayerScoreCard& playerScoreCard = ACrazyBattleGameState_private::GetPlayerScoreCardForPlayerIndex(gameInstance, 0);
                        playerScoreCard.IsSet = true;
                        playerScoreCard.Kills = playerData[i].Kills;
                        playerScoreCard.Deaths = playerData[i].Deaths;
                        playerScoreCard.Color = gameMode->GetPlayerColourForIndex(i);
                    }
                    else
                    {
                        FPlayerScoreCard& playerScoreCard = ACrazyBattleGameState_private::GetPlayerScoreCardForPlayerIndex(gameInstance, cardIndex);
                        playerScoreCard.IsSet = true;
                        playerScoreCard.Kills = playerData[i].Kills;
                        playerScoreCard.Deaths = playerData[i].Deaths;
                        playerScoreCard.Color = gameMode->GetPlayerColourForIndex(i);
                        cardIndex++;
                    }
                }

                for (int32 i = gameMode->GetSpawnedPlayerNum(); i < playerData.Num(); i++)
                {
                    FPlayerScoreCard& playerScoreCard = ACrazyBattleGameState_private::GetPlayerScoreCardForPlayerIndex(gameInstance, i);
                    playerScoreCard.IsSet = false;
                }
            }
            else
            {
                for (int32 i = 0; i < playerData.Num(); i++)
                {
                    FPlayerScoreCard& playerScoreCard = ACrazyBattleGameState_private::GetPlayerScoreCardForPlayerIndex(gameInstance, i);
                    if (i < gameMode->GetSpawnedPlayerNum())
                    {
                        playerScoreCard.IsSet = true;
                        playerScoreCard.Kills = playerData[i].Kills;
                        playerScoreCard.Deaths = playerData[i].Deaths;
                        playerScoreCard.Color = gameMode->GetPlayerColourForIndex(i);
                    }
                    else
                    {
                        playerScoreCard.IsSet = false;
                    }
                }
            }
        }

        UGameplayStatics::OpenLevel(GetGameInstance(), TEXT("game_end"));
    }
}

void ACrazyBattleGameState::Tick_EndGame(float DeltaTime)
{

}

ACBPaperCharacter* ACrazyBattleGameState::GetPaperCharacter(int32 playerIndex)
{
    ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());
    int controllerId = gameMode->GetControllerIdForPlayerIndex(playerIndex);

    for (FConstPlayerControllerIterator playerIt = GetWorld()->GetPlayerControllerIterator(); playerIt; ++playerIt)
    {
        ACBPaperCharacter* paperCharacter = Cast<ACBPaperCharacter>(playerIt->Get()->GetPawn());
        if (paperCharacter)
        {
            if (ULocalPlayer* localPlayer = playerIt->Get()->GetLocalPlayer())
            {
                if (localPlayer->GetControllerId() == controllerId)
                {
                    return paperCharacter;
                }
            }
        }
    }

    return nullptr;
}

void ACrazyBattleGameState::OnPlayerDamaged(float Damage, int32 attackerIndex, int32 receiverIndex)
{
    if (state != ECrazyBattleGameState::CBGS_Game)
    {
        return;
    }

    FPlayerData& receiverData = playerData[receiverIndex];
    if (receiverData.PlayerState == EPlayerDataState::PDS_Respawn ||
        receiverData.PlayerState == EPlayerDataState::PDS_Dead)
    {
        return;
    }

    receiverData.PlayerHealth -= Damage;
    if (receiverData.PlayerHealth <= 0.0f)
    {
        receiverData.Lives--;
        if (receiverData.Lives < 0)
        {
            receiverData.PlayerState = EPlayerDataState::PDS_Dead;
        }
        else
        {
            receiverData.PlayerState = EPlayerDataState::PDS_Respawn;
            receiverData.DealthTimer = RespawnTime;
        }

        if (ACBPaperCharacter* paperCharacter = GetPaperCharacter(receiverIndex))
        {
            paperCharacter->OnDeath();
        }

        receiverData.Deaths++;

        playerData[attackerIndex].Kills++;
    }
}

const FPlayerData& ACrazyBattleGameState::GetPlayerData(int32 playerIndex)
{
    if (playerIndex >= 0 && playerIndex < playerData.Num())
    {
        return playerData[playerIndex];
    }
    return playerData[0];
}
