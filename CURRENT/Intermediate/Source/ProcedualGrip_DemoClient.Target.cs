using UnrealBuildTool;

public class ProcedualGrip_DemoClientTarget : TargetRules
{
	public ProcedualGrip_DemoClientTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Client;
		ExtraModuleNames.Add("ProcedualGrip_Demo");
	}
}
