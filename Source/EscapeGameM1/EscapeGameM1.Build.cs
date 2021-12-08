// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EscapeGameM1 : ModuleRules
{
	public EscapeGameM1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
