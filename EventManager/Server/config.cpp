class CfgPatches
{
	class SimpleEventManager
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","JM_CF_Scripts","DF_Scripts"};
	};
};
class CfgMods
{
	class SimpleEventManager
	{
		dir = "SimpleEventManager";
		hideName = 1;
		hidePicture = 1;
		name = "SimpleEventManager";
		credits = "Scarabyte";
		author = "Scarabyte";
		version = "0.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"SimpleEvents/EventManager/Server/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"SimpleEvents/EventManager/Server/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"SimpleEvents/EventManager/Server/scripts/5_Mission"};
			};
		};
	};
};
