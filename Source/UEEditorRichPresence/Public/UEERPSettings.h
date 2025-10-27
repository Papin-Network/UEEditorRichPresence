#pragma once
#include "Engine/DeveloperSettings.h"
#include "UEERPSettings.generated.h"

UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="Editor Rich Presence"))
class UEEDITORRICHPRESENCE_API UUEERPSettings : public UDeveloperSettings
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Config, Category="General")
    bool bEnableRichPresence = true;

    UPROPERTY(EditAnywhere, Config, Category="Discord", meta=(ClampMin="0"))
    uint64 DiscordApplicationId = 0; // inserisci l’App ID

    UPROPERTY(EditAnywhere, Config, Category="Discord")
    FString DefaultLargeImageKey = TEXT("ue-logo");

    UPROPERTY(EditAnywhere, Config, Category="Privacy")
    bool bShowProjectName = true;

    UPROPERTY(EditAnywhere, Config, Category="Privacy")
    bool bShowMapName = true;
};
