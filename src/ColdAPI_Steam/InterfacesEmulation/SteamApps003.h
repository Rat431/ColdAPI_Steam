#pragma once
#include "../public SDK/ISteamApps003.h"
#include "../Bridge.h"

class SteamAppsIn003 : public ISteamApps003
{
public:
	bool BIsSubscribed()
	{
		return true;
	}
	bool BIsLowViolence()
	{
		return Steam_Config::LowViolence;
	}
	bool BIsCybercafe()
	{
		return false;
	}
	bool BIsVACBanned()
	{
		return false;
	}
	const char* GetCurrentGameLanguage()
	{
		return Steam_Config::Language;
	}
	const char* GetAvailableGameLanguages()
	{
		return Steam_Config::Language;
	}

	bool BIsSubscribedApp(AppId_t nAppID)
	{
		return ColdAPI_DLC::IsDLCAvailable(nAppID);
	}

	bool BIsDlcInstalled(AppId_t nAppID)
	{
		return ColdAPI_DLC::IsDLCAvailable(nAppID);
	}
};
