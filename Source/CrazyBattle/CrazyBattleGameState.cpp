// Fill out your copyright notice in the Description page of Project Settings.

#include "CrazyBattleGameState.h"

#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "CBPaperCharacter.h"
#include "CrazyBattleGameMode.h"

ACrazyBattleGameState::ACrazyBattleGameState()
{
    PrimaryActorTick.bCanEverTick = true;

    InitialPlayerHealth = 100.0f;
    RespawnTime = 5.0f;
}

void ACrazyBattleGameState::BeginPlay()
{
    Super::BeginPlay();

    for (int32 i = 0; i < 4; i++)
    {
        playerData.Emplace();
    }

    for (int32 i = 0; i < playerData.Num(); i++)
    {
        playerData[i].Lives = 5;
    }
}

void ACrazyBattleGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (int32 i = 0; i < playerData.Num(); i++)
    {
        if (playerData[i].PlayerState == PlayerData::State::Respawn)
        {
            playerData[i].DealthTimer -= DeltaTime;
            if (playerData[i].DealthTimer <= 0.0f)
            {
                playerData[i].PlayerState = PlayerData::State::Idle;
                playerData[i].PlayerHealth = InitialPlayerHealth;
                if (ACBPaperCharacter* paperCharacter = GetPaperCharacter(i))
                {
                    paperCharacter->SetActorLocation(FVector(260.0f, 0.0f, 28.0f));
                    paperCharacter->OnRespawn();
                }
            }
        }
    }
}

int32 ACrazyBattleGameState::GetKillsForPlayer(int32 playerIndex)
{
    return -1;
}

int32 ACrazyBattleGameState::GetPlayerDeaths(int32 playerIndex)
{
    return -1;
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
    PlayerData& receiverData = playerData[receiverIndex];
    if (receiverData.PlayerState == PlayerData::State::Respawn ||
        receiverData.PlayerState == PlayerData::State::Dead)
    {
        return;
    }

    receiverData.PlayerHealth -= Damage;
    if (receiverData.PlayerHealth <= 0.0f)
    {
        receiverData.Lives--;
        if (receiverData.Lives < 0)
        {
            receiverData.PlayerState = PlayerData::State::Dead;
        }
        else
        {
            receiverData.PlayerState = PlayerData::State::Respawn;
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
