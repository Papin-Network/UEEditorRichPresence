#include "UEERPSubsystem.h"
#include "Discord/DiscordWrapper.h"
#include "UEERPSettings.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "EditorDelegates.h"
#include "Misc/Paths.h"
#include "Misc/ProjectDescriptor.h"

void UUEERPSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    const auto* Settings = GetDefault<UUEERPSettings>();
    if (!Settings->bEnableRichPresence || Settings->DiscordApplicationId == 0)
        return;

    Discord = MakeUnique<FDiscordWrapper>();
    if (Discord->Init(Settings->DiscordApplicationId))
    {
        HookEditorDelegates();

        const FString ProjectName = Settings->bShowProjectName ? FApp::GetProjectName() : TEXT("Unreal Project");
        UpdatePresence(TEXT("Editor avviato"), ProjectName);
    }
}

void UUEERPSubsystem::Deinitialize()
{
    UnhookEditorDelegates();
    if (Discord) { Discord->Shutdown(); Discord.Reset(); }
}

void UUEERPSubsystem::Tick(float DeltaTime)
{
    if (Discord) Discord->PumpCallbacks();
}

void UUEERPSubsystem::HookEditorDelegates()
{
    FEditorDelegates::OnMapOpened.AddUObject(this, &UUEERPSubsystem::OnMapOpened);
    FEditorDelegates::BeginPIE.AddUObject(this, &UUEERPSubsystem::OnPIEStarted);
    FEditorDelegates::EndPIE.AddUObject(this, &UUEERPSubsystem::OnPIEEnded);
}

void UUEERPSubsystem::UnhookEditorDelegates()
{
    FEditorDelegates::OnMapOpened.RemoveAll(this);
    FEditorDelegates::BeginPIE.RemoveAll(this);
    FEditorDelegates::EndPIE.RemoveAll(this);
}

void UUEERPSubsystem::OnMapOpened(const FString& Filename, bool)
{
    const auto* Settings = GetDefault<UUEERPSettings>();
    FString Details = Settings->bShowMapName
        ? FPaths::GetBaseFilename(Filename) : TEXT("Mappa");
    UpdatePresence(bPIE ? TEXT("In Play-In-Editor") : TEXT("Editing"),
                   Details);
}

void UUEERPSubsystem::OnPIEStarted(bool)
{
    bPIE = true;
    UpdatePresence(TEXT("In Play-In-Editor"), TEXT("Giocando in Editor"));
}

void UUEERPSubsystem::OnPIEEnded(bool)
{
    bPIE = false;
    UpdatePresence(TEXT("Editing"), TEXT("Tornato all'Editor"));
}

void UUEERPSubsystem::UpdatePresence(const FString& Activity, const FString& Context)
{
    if (!Discord) return;

    if (LastState == Activity && LastDetails == Context) return;
    LastState = Activity; LastDetails = Context;

    const auto* Settings = GetDefault<UUEERPSettings>();
    Discord->SetPresence(/*State*/ Activity,
                         /*Details*/ Context,
                         /*LargeImageKey*/ Settings->DefaultLargeImageKey,
                         /*LargeImageText*/ TEXT("Unreal Engine"));
}
