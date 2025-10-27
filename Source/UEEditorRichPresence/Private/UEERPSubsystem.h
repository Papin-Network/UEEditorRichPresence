#pragma once
#include "EditorSubsystem.h"
#include "UEERPSubsystem.generated.h"

class FDiscordWrapper;

UCLASS()
class UEEDITORRICHPRESENCE_API UUEERPSubsystem : public UEditorSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
    TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(UUEERPSubsystem, STATGROUP_Tickables); }

private:
    void HookEditorDelegates();
    void UnhookEditorDelegates();
    void UpdatePresence(const FString& Activity, const FString& Context);

    void OnMapOpened(const FString& Filename, bool bAsTemplate);
    void OnPIEStarted(bool bSimulating);
    void OnPIEEnded(bool bSimulating);

private:
    TUniquePtr<FDiscordWrapper> Discord;
    FString LastState, LastDetails;
    bool bPIE = false;
};
