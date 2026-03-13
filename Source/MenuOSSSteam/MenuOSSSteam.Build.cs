// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MenuOSSSteam : ModuleRules
{
	public MenuOSSSteam(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MenuOSSSteam",
			"MenuOSSSteam/Variant_Platforming",
			"MenuOSSSteam/Variant_Platforming/Animation",
			"MenuOSSSteam/Variant_Combat",
			"MenuOSSSteam/Variant_Combat/AI",
			"MenuOSSSteam/Variant_Combat/Animation",
			"MenuOSSSteam/Variant_Combat/Gameplay",
			"MenuOSSSteam/Variant_Combat/Interfaces",
			"MenuOSSSteam/Variant_Combat/UI",
			"MenuOSSSteam/Variant_SideScrolling",
			"MenuOSSSteam/Variant_SideScrolling/AI",
			"MenuOSSSteam/Variant_SideScrolling/Gameplay",
			"MenuOSSSteam/Variant_SideScrolling/Interfaces",
			"MenuOSSSteam/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
