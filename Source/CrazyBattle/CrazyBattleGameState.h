// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CrazyBattleGameState.generated.h"

struct PlayerData
{
    enum class State
    {
        Idle,
        Respawn,
        Dead,
    };

    PlayerData() 
        : Kills(0)
        , Deaths(0)
        , PlayerHealth(100.0f)
        , PlayerState(State::Idle)
        , Lives(0)
    {}

    State PlayerState;
    int32 Kills;
    int32 Deaths;
    float PlayerHealth;
    int32 Lives;
};

/**
 * 
 */
UCLASS()
class CRAZYBATTLE_API ACrazyBattleGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    ACrazyBattleGameState();

    UFUNCTION()
    int32 GetKillsForPlayer(int32 playerIndex);

    UFUNCTION()
    int32 GetPlayerDeaths(int32 playerIndex);

    void OnPlayerDamaged(float Damage, int32 attackerIndex, int32 receiverIndex);

    // Called every frame
    virtual void Tick(float DeltaTime) override;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    float InitialPlayerHealth;

private:
    class ACBPaperCharacter* GetPaperCharacter(int32 playerIndex);

private:
    TArray<PlayerData> playerData;
};
