using UnrealBuildTool;

public class HackAndSlash : ModuleRules
{
	public HackAndSlash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"SlateCore",
			"AIModule",
			"GameplayTasks",
			"UMG"
		});

		PublicIncludePaths.Add(ModuleDirectory);

	}
}
