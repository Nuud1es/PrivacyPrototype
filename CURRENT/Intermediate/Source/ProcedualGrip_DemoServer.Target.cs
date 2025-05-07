using UnrealBuildTool;

public class ProcedualGrip_DemoServerTarget : TargetRules
{
	public ProcedualGrip_DemoServerTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Server;
		ExtraModuleNames.Add("ProcedualGrip_Demo");
	}
}
