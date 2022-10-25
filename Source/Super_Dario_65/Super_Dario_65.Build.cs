// Fill out your copyright notice in the Description page of Project Settings.

/// summary ///
/// Edited by Nisara
///  "AIModule", "GameplayTasks", "NavigationSystem"
/// Theses are new modules needed for the AI. for example the; UBTTask_BlackboardBase
///  end of summary ///
///  
using UnrealBuildTool;

public class Super_Dario_65 : ModuleRules
{
	public Super_Dario_65(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "AIModule", "NavigationSystem", "Niagara", "UMG", "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		//PublicIncludePaths.AddRange(new string[] {"Engine/Plugins/FX/Niagara/Source/Niagara/Public"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
