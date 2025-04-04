class CfgPatches
{
	class OVG_Aduty
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class OVG_Aduty
	{
		dir="OVG_Aduty";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="OVG_Aduty";
		credits="OVG Team";
		author="1Example";
		authorID="";
		version="0.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"OVG_Aduty/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"OVG_Aduty/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"OVG_Aduty/Scripts/5_Mission"
				};
			};
		};
	};
};
