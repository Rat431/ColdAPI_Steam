#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUserStats001.h"

class SteamUserStatsIn001 : public ISteamUserStats001
{
public:
	uint32 GetNumStats(CGameID nGameID)
	{
		return NULL;
	}
	const char* GetStatName(CGameID nGameID, uint32 iStat)
	{
		return "";
	}
	ESteamUserStatType GetStatType(CGameID nGameID, const char* pchName)
	{
		return k_ESteamUserStatTypeINT;
	}
	uint32 GetNumAchievements(CGameID nGameID)
	{
		return NULL;
	}
	const char* GetAchievementName(CGameID nGameID, uint32 iAchievement)
	{
		return "Achievement";
	}

	OBSOLETE_FUNCTION uint32 GetNumGroupAchievements(CGameID)
	{
		return NULL;
	}
	OBSOLETE_FUNCTION const char* GetGroupAchievementName(CGameID, uint32 iAchievement)
	{
		return "Achievement";
	}

	bool RequestCurrentStats(CGameID nGameID)
	{
		return true;
	}

	// Data accessors
#if !(defined(_WIN32) && defined(__GNUC__))
	bool GetStat(CGameID nGameID, const char* pchName, int32* pData)
	{
		return false;
	}
	bool GetStat(CGameID nGameID, const char* pchName, float* pData)
	{
		return false;
	}
#else
	bool GetStat(CGameID nGameID, const char* pchName, float* pData)
	{
		return false;
	}
	bool GetStat(CGameID nGameID, const char* pchName, int32* pData)
	{
		return false;
	}
#endif

	// Set / update data
#if !(defined(_WIN32) && defined(__GNUC__))
	bool SetStat(CGameID nGameID, const char* pchName, int32 nData)
	{
		return false;
	}
	bool SetStat(CGameID nGameID, const char* pchName, float fData)
	{
		return false;
	}
#else
	bool SetStat(CGameID nGameID, const char* pchName, float fData)
	{
		return false;
	}
	bool SetStat(CGameID nGameID, const char* pchName, int32 nData)
	{
		return false;
	}
#endif

	bool UpdateAvgRateStat(CGameID nGameID, const char* pchName, float, double dSessionLength)
	{
		return false;
	}

	bool GetAchievement(CGameID nGameID, const char* pchName, bool* pbAchieved)
	{
		return false;
	}
	bool GetGroupAchievement(CGameID nGameID, const char* pchName, bool* pbAchieved)
	{
		return false;
	}

	bool SetAchievement(CGameID nGameID, const char* pchName)
	{
		return false;
	}
	bool SetGroupAchievement(CGameID nGameID, const char* pchName)
	{
		return false;
	}

	bool StoreStats(CGameID nGameID)
	{
		return true;
	}

	bool ClearAchievement(CGameID nGameID, const char* pchName)
	{
		return true;
	}
	bool ClearGroupAchievement(CGameID nGameID, const char* pchName)
	{
		return true;
	}

	int GetAchievementIcon(CGameID nGameID, const char* pchName)
	{
		return NULL;
	}
	const char* GetAchievementDisplayAttribute(CGameID nGameID, const char* pchName, const char* pchKey)
	{
		return "";
	}
};