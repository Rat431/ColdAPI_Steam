#pragma once
#include "../public SDK/ISteamApps002.h"
#include "../Bridge.h"

class SteamAppsIn002 : public ISteamApps002
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
};
