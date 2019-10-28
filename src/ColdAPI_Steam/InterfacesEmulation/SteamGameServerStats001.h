#pragma once
#include "../public SDK/ISteamGameServerStats001.h"
#include "../Bridge.h"


class SteamGameServerStatsIn001 : public ISteamGameServerStats001
{
public:
	SteamAPICall_t RequestUserStats(CSteamID steamIDUser)
	{
		return NULL;
	}
	bool GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData)
	{
		return true;
	}
	bool GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData)
	{
		return true;
	}
	bool GetUserAchievement(CSteamID steamIDUser, const char* pchName, bool* pbAchieved)
	{
		return true;
	}
	bool SetUserStat(CSteamID steamIDUser, const char* pchName, int32 nData)
	{
		return true;
	}
	bool SetUserStat(CSteamID steamIDUser, const char* pchName, float fData)
	{
		return true;
	}
	bool UpdateUserAvgRateStat(CSteamID steamIDUser, const char* pchName, float flCountThisSession, double dSessionLength)
	{
		return true;
	}

	bool SetUserAchievement(CSteamID steamIDUser, const char* pchName)
	{
		return true;
	}
	bool ClearUserAchievement(CSteamID steamIDUser, const char* pchName)
	{
		return true;
	}

	SteamAPICall_t StoreUserStats(CSteamID steamIDUser)
	{
		return NULL;
	}
};