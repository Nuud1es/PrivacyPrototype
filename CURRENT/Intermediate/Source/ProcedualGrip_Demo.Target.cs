using UnrealBuildTool;

public class ProcedualGrip_DemoTarget : TargetRules
{
	public ProcedualGrip_DemoTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Game;
		ExtraModuleNames.Add("ProcedualGrip_Demo");
	}
}
