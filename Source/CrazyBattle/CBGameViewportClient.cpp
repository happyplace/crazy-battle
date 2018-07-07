// Fill out your copyright notice in the Description page of Project Settings.

#include "CBGameViewportClient.h"

#include "CrazyBattleGameMode.h"
#include "Engine.h"
#include "Engine/World.h"

// The first player is the camera, so when we're sending keyboard input we increment the controller id by 1 to skip over the camera
// gamepads controller index start after the first index so we have to increase by two because we're skiping the camera and the keyboard
// game controller

bool UCBGameViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
    int32 modifiedControllerId = ControllerId + bGamepad ? 2 : 1;

    if (Key.GetFName().Compare(TEXT("Gamepad_Special_Right")) == 0 ||
        Key.GetFName().Compare(TEXT("Y")) == 0)
    {
        ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());
        gameMode->CreatePlayerForController(modifiedControllerId);
    }

    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Key.GetDisplayName().ToString());

    return Super::InputKey(Viewport, modifiedControllerId, Key, EventType, AmountDepressed, bGamepad);
}

bool UCBGameViewportClient::InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples /*= 1*/, bool bGamepad /*= false*/)
{
    if (bGamepad)
    {
        return Super::InputAxis(Viewport, ControllerId + 2, Key, Delta, DeltaTime, NumSamples, bGamepad);
    }
    else
    {
        return Super::InputAxis(Viewport, ControllerId + 1, Key, Delta, DeltaTime, NumSamples, bGamepad);
    }
}

// This sends all input to all players
//bool UCBGameViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
//{
//    if (IgnoreInput() || bGamepad || Key.IsMouseButton())
//    {
//        return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
//    }
//    else
//    {
//        UEngine* const Engine = GetOuterUEngine();
//        const int32 NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
//        bool bRetVal = false;
//        for (int32 i = 0; i < NumPlayers; i++)
//        {
//            bRetVal = Super::InputKey(Viewport, i, Key, EventType, AmountDepressed, bGamepad) || bRetVal;
//        }
//
//        return bRetVal;
//    }
//}
