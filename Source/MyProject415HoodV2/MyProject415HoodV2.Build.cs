// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject415HoodV2 : ModuleRules
{
	public MyProject415HoodV2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "ProceduralMeshComponent" });
	}
}
