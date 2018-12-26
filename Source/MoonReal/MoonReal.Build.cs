// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MoonReal : ModuleRules {

    private string ThirdPartyPath { get { return Path.Combine(ModuleDirectory, "../../ThirdParty/"); } }

    public MoonReal(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "ShaderCore",
                "RenderCore",
                "RHI",
                "SlateCore",
                "Slate",
                "NavigationSystem"
        });

        PrivateIncludePaths.AddRange(
            new string[] {
                "MoonReal/Private",
        });

        LoadLua(Target);
    }

    private bool LoadLua(ReadOnlyTargetRules Target) {
        bool isLibSupported = false;
        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32) {
            isLibSupported = true;
            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86"; // This string is either "x64" or "x86" so we can append it on the lib filename
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Lua", "libraries");
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "lua53." + PlatformString + ".lib"));
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Lua", "includes"));

        }
        Definitions.Add(string.Format("WITH_LUA_BINDING={0}", isLibSupported ? 1 : 0));
        return isLibSupported;
    }
}
