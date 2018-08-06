// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CrazyBattleGameInstance.generated.h"

USTRUCT(BlueprintType)
struct CRAZYBATTLE_API FPlayerScoreCard
{
    GENERATED_USTRUCT_BODY()

    FPlayerScoreCard()
        : Color(FLinearColor::White)
        , Kills(0)
        , Deaths(0)
        , IsSet(false)
    {}

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FLinearColor Color;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    int32 Kills;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    int32 Deaths;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    bool IsSet;
};

/**
 * 
 */
UCLASS()
class CRAZYBATTLE_API UCrazyBattleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FPlayerScoreCard Player0;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FPlayerScoreCard Player1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FPlayerScoreCard Player2;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crazy Battle", meta = (AllowPrivateAccess = "true"))
    FPlayerScoreCard Player3;
};
