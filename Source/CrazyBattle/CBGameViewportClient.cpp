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
    ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());

    int32 modifiedControllerId = ControllerId + bGamepad ? 3 : 1;
 
    if (Key == EKeys::Y || Key == EKeys::NumPadSeven)
    {
        if (gameMode->keyboardPlayers.Num() < 2)
        {
            int keyboardControllerId = ControllerId + 1 + gameMode->keyboardPlayers.Num(); // Next available input
            int keyboardIndex = Key == EKeys::Y ? 0 : 1;

            if (!gameMode->DoesPlayerUsingKeyboardIndexExist(keyboardIndex))
            {
                ACrazyBattleGameMode* gameMode = Cast<ACrazyBattleGameMode>(GetWorld()->GetAuthGameMode());
                gameMode->CreatePlayerForController(keyboardControllerId, keyboardIndex);

                ACrazyBattleGameMode::KeyboardPlayerPair pair;
                pair.ControllerId = keyboardControllerId;
                pair.KeyboardIndex = keyboardIndex;
                gameMode->keyboardPlayers.Add(pair);
            }
        }
    }
    else if (Key == EKeys::Gamepad_Special_Right)
    {
        gameMode->CreatePlayerForController(modifiedControllerId);
    }

    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Key.GetDisplayName().ToString());

    if (IgnoreInput() || bGamepad || Key.IsMouseButton())
    {
        return Super::InputKey(Viewport, modifiedControllerId, Key, EventType, AmountDepressed, bGamepad);
    }
    else
    {
        UEngine* const Engine = GetOuterUEngine();
        const int32 NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
        bool bRetVal = false;
        for (int32 i = 0; i < NumPlayers; i++)
        {
            bRetVal = Super::InputKey(Viewport, i, Key, EventType, AmountDepressed, bGamepad) || bRetVal;
        }
        return bRetVal;
    }
}

bool UCBGameViewportClient::InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples /*= 1*/, bool bGamepad /*= false*/)
{
    if (bGamepad)
    {
        return Super::InputAxis(Viewport, ControllerId + 3, Key, Delta, DeltaTime, NumSamples, bGamepad);
    }
    else
    {
        return Super::InputAxis(Viewport, ControllerId + 1, Key, Delta, DeltaTime, NumSamples, bGamepad);
    }
}
