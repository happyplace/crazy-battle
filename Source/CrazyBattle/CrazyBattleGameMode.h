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

    void CreatePlayerForController(int32 ControllerId, int32 KeyboardIndex = -1);

    UFUNCTION(BlueprintCallable, Category = "Crazy Battle")
    FLinearColor GetPlayerColourForIndex(int32 playerIndex);

    void OnPlayerAttacked(AttackType attackType, int32 attackerIndex, int32 receiverIndex);

    int32 GetControllerIdForPlayerIndex(int32 playerIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Crazy Battle")
    int32 GetSpawnedPlayerNum();

    struct KeyboardPlayerPair
    {
        int32 ControllerId;
        int32 KeyboardIndex;
    };
    TArray<KeyboardPlayerPair> keyboardPlayers;

    bool DoesPlayerUsingKeyboardIndexExist(int32 KeyboardIndex) const;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ACBPaperCharacter> PlayerCharacter;

    TSubclassOf<APawn> initialDefaultClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor PlayerColor3;

    TArray<int32> spawnedPlayersControllerId;

    TArray<APlayerController*> spawnedPlayerControllers;
};
