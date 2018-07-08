// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrazyBattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYBATTLE_API ACrazyBattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    enum class AttackType
    { 
        None, 
        BasicAttack,
    };
    
    ACrazyBattleGameMode();

    void CreatePlayerForController(int32 ControllerId);

    FLinearColor GetPlayerColourForIndex(int32 playerIndex);

    void OnPlayerAttacked(AttackType attackType, int32 attackerIndex, int32 receiverIndex);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ACBPaperCharacter> PlayerCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor3;

    TArray<int32> spawnedPlayersControllerId;
};
