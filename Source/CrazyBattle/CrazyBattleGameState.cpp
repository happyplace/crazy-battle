// Fill out your copyright notice in the Description page of Project Settings.

#include "CrazyBattleGameState.h"

ACrazyBattleGameState::ACrazyBattleGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACrazyBattleGameState::BeginPlay()
{
    Super::BeginPlay();

    for (int32 i = 0; i < 4; i++)
    {
        playerData.Emplace();
    }
}

void ACrazyBattleGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (int32 i = 0; i < playerData.Num(); i++)
    {
        if (playerData[i].PlayerState == PlayerData::State::Respawn)
        {
            // if death timer is below zero
            // call pawn respawn function
            playerData[i].PlayerState = PlayerData::State::Idle;
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
        receiverData.PlayerState = receiverData.Lives < 0 ? PlayerData::State::Dead : PlayerData::State::Respawn;
        // Call Die Function on Pawn of PlayerController;

        receiverData.Deaths++;

        playerData[attackerIndex].Kills++;
    }
    
    if (receiverData.PlayerState == PlayerData::State::Respawn ||
        receiverData.PlayerState == PlayerData::State::Dead)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("played died"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Format(TEXT("Basic Attack: {0} Damage: {1}"), { receiverIndex, playerData[receiverIndex].PlayerHealth }));
    }
}
