// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CrazyBattleGameState.generated.h"

UENUM(BlueprintType)
enum class EPlayerDataState : uint8
{
    PDS_Idle        UMETA(DisplayName="Idle"),
    PDS_Respawn     UMETA(DisplayName="Respawn"),
    PDS_Dead        UMETA(DisplayName="Dead"),
};

USTRUCT(BlueprintType)
struct CRAZYBATTLE_API FPlayerData
{
    GENERATED_USTRUCT_BODY()

    FPlayerData() 
        : Kills(0)
        , Deaths(0)
        , PlayerHealth(100.0f)
        , PlayerState(EPlayerDataState::PDS_Idle)
        , Lives(0)
    {}

    EPlayerDataState PlayerState;
    int32 Kills;
    int32 Deaths;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    float PlayerHealth;
    
    int32 Lives;
    float DealthTimer;
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

    UFUNCTION(BlueprintCallable, Category = "Crazy Battle")
    const FPlayerData& GetPlayerData(int32 playerIndex);

    void OnPlayerDamaged(float Damage, int32 attackerIndex, int32 receiverIndex);

    // Called every frame
    virtual void Tick(float DeltaTime) override;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    float InitialPlayerHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    float RespawnTime;

private:
    class ACBPaperCharacter* GetPaperCharacter(int32 playerIndex);

private:
    UPROPERTY()
    TArray<FPlayerData> playerData;
};
