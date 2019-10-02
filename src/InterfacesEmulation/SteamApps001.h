#pragma once
#include "../public SDK/ISteamApps001.h"
#include "../Bridge.h"


class SteamAppsIn001 : public ISteamApps001
{
public:
	int GetAppData(AppId_t nAppID, const char* pchKey, char* pchValue, int cchValueMax)
	{
		return NULL;
	}
};
