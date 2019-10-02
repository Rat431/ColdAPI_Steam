#pragma once
#include "../public SDK/ISteamAppList001.h"
#include "../Bridge.h"



class SteamAppListIn001 : public ISteamAppList001
{
public:
	uint32 GetNumInstalledApps()
	{
		return 1;
	}
	uint32 GetInstalledApps(uint32* puUnk, uint32 uUnk)
	{
		return 1;
	}
	unknown_ret GetAppName(uint32 uUnk, char* pUnk, int32 iUnk)
	{
		return  1;
	}
	unknown_ret GetAppInstallDir(uint32 uUnk, char* pUnk, int32 iUnk)
	{
		return 1;
	}
	unknown_ret GetAppBuildId(uint32 uUnk)
	{
		return Steam_Config::AppBuildId;
	}
};