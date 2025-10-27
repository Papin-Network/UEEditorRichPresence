using UnrealBuildTool;
using System.IO;

public class UEEditorRichPresence : ModuleRules
{
    public UEEditorRichPresence(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "UnrealEd", "Slate", "SlateCore", "LevelEditor",
            "EditorSubsystem", "Projects", "DeveloperSettings"
        });

        // (Opzionale) cartella con le DLL dell'SDK Rich Presence (es. Discord)
        string ThirdPartyBin = Path.Combine(ModuleDirectory, "ThirdParty", "Bin", Target.Platform.ToString());
        RuntimeDependencies.Add(Path.Combine(ThirdPartyBin, "discord_game_sdk.dll"), StagedFileType.NonUFS);
        PublicDelayLoadDLLs.Add("discord_game_sdk.dll"); // se la usi
    }
}
