using UnrealBuildTool;

public class ProcedualGrip_DemoEditorTarget : TargetRules
{
	public ProcedualGrip_DemoEditorTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Editor;
		ExtraModuleNames.Add("ProcedualGrip_Demo");
	}
}
