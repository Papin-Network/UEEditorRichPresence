#pragma once
#include "CoreMinimal.h"

class FDiscordWrapper
{
public:
    bool Init(uint64 AppId);
    void Shutdown();

    void PumpCallbacks();

    void SetPresence(const FString& State, const FString& Details,
                     const FString& LargeImageKey = TEXT(""),
                     const FString& LargeImageText = TEXT(""));
private:
    void* SDKHandle = nullptr; // tieni qui il puntatore all'SDK
    bool bInitialized = false;
};
