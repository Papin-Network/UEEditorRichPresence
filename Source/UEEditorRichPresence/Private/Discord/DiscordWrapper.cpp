#include "Discord/DiscordWrapper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

bool FDiscordWrapper::Init(uint64 AppId)
{
    if (bInitialized || AppId == 0) return false;
    // TODO: inizializza SDK (create core, activities, ecc.)
    bInitialized = true;
    return true;
}

void FDiscordWrapper::Shutdown()
{
    if (!bInitialized) return;
    
    // TODO: cleanup SDK resources
    
    if (SDKHandle)
    {
        FPlatformProcess::FreeDllHandle(SDKHandle);
        SDKHandle = nullptr;
    }
    
    bInitialized = false;
}

void FDiscordWrapper::PumpCallbacks()
{
    if (!bInitialized) return;
    // TODO: run callbacks/tick dell'SDK
}

void FDiscordWrapper::SetPresence(const FString& State, const FString& Details,
                                 const FString& LargeImageKey, const FString& LargeImageText)
{
    if (!bInitialized) return;
    // TODO: invia activity rich presence con State/Details/images
    
    // Esempio di log per debug
    UE_LOG(LogTemp, Log, TEXT("Rich Presence - State: %s, Details: %s, Image: %s"), 
        *State, *Details, *LargeImageKey);
}
