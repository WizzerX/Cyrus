// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cyrus : ModuleRules
{
	public Cyrus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"HTTP",
			"Json",
            "JsonUtilities"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Cyrus",
			"Cyrus/Variant_Horror",
			"Cyrus/Variant_Horror/UI",
			"Cyrus/Variant_Shooter",
			"Cyrus/Variant_Shooter/AI",
			"Cyrus/Variant_Shooter/UI",
			"Cyrus/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
