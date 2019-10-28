#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUserStats003.h"

class SteamUserStatsIn003 : public ISteamUserStats003
{
public:
	bool RequestCurrentStats()
	{
		return true;
	}

	// Data accessors
#if !(defined(_WIN32) && defined(__GNUC__))
	bool GetStat(const char* pchName, int32* pData)
	{
		return false;
	}
	bool GetStat(const char* pchName, float* pData)
	{
		return false;
	}
#else
	bool GetStat(const char* pchName, float* pData)
	{
		return false;
	}
	bool GetStat(const char* pchName, int32* pData)
	{
		return false;
	}
#endif

	// Set / update data
#if !(defined(_WIN32) && defined(__GNUC__))
	bool SetStat(const char* pchName, int32 nData)
	{
		return false;
	}
	bool SetStat(const char* pchName, float fData)
	{
		return false;
	}
#else
	bool SetStat(const char* pchName, float fData)
	{
		return false;
	}
	bool SetStat(const char* pchName, int32 nData)
	{
		return false;
	}
#endif
	bool UpdateAvgRateStat(const char* pchName, float, double dSessionLength)
	{
		return false;
	}


	bool GetAchievement(const char* pchName, bool* pbAchieved)
	{
		return false;
	}
	bool SetAchievement(const char* pchName)
	{
		return false;
	}
	bool ClearAchievement(const char* pchName)
	{
		return true;
	}

	bool StoreStats()
	{
		return true;
	}

	int GetAchievementIcon(const char* pchName)
	{
		return NULL;
	}
	const char* GetAchievementDisplayAttribute(const char* pchName, const char* pchKey)
	{
		return "";
	}

	bool IndicateAchievementProgress(const char* pchName, uint32 nCurProgress, uint32 nMaxProgress)
	{
		return false;
	}
};