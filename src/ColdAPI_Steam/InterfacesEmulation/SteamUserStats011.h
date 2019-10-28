#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUserStats011.h"

class SteamUserStatsIn011 : public ISteamUserStats011		
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
	bool UpdateAvgRateStat(const char* pchName, float flCountThisSession, double dSessionLength)
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

	bool GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, uint32* punUnlockTime)
	{
		return false;
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

	uint32 GetNumAchievements()
	{
		return NULL;
	}
	const char* GetAchievementName(uint32 iAchievement)
	{
		return "";
	}

	SteamAPICall_t RequestUserStats(CSteamID steamIDUser)
	{
		return NULL;
	}

	
#if !(defined(_WIN32) && defined(__GNUC__))
	bool GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData)
	{
		return false;
	}
	bool GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData)
	{
		return false;
	}
#else
	bool GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData)
	{
		return false;
	}
	bool GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData)
	{
		return false;
	}
#endif
	bool GetUserAchievement(CSteamID steamIDUser, const char* pchName, bool* pbAchieved)
	{
		return false;
	}
	bool GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char* pchName, bool* pbAchieved, uint32* punUnlockTime)
	{
		return false;
	}

	bool ResetAllStats(bool bAchievementsToo)
	{
		return true;
	}

	SteamAPICall_t FindOrCreateLeaderboard(const char* pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
	{
		return NULL;
	}

	SteamAPICall_t FindLeaderboard(const char* pchLeaderboardName)
	{
		return NULL;
	}

	const char* GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard)
	{
		return "";
	}

	int GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard)
	{
		return NULL;
	}

	ELeaderboardSortMethod GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard)
	{
		return k_ELeaderboardSortMethodNone;
	}

	ELeaderboardDisplayType GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard)
	{
		return k_ELeaderboardDisplayTypeNone;
	}

	SteamAPICall_t DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
	{
		return NULL;
	}
	SteamAPICall_t DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, CSteamID* prgUsers, int cUsers)
	{
		return NULL;
	}

	bool GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32 pDetails[], int cDetailsMax)
	{
		return false;
	}

	SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount)
	{
		return NULL;
	}

	SteamAPICall_t AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
	{
		return NULL;
	}

	SteamAPICall_t GetNumberOfCurrentPlayers()
	{
		return NULL;
	}

	SteamAPICall_t RequestGlobalAchievementPercentages()
	{
		return NULL;
	}

	int GetMostAchievedAchievementInfo(char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved)
	{
		return NULL;
	}

	int GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved)
	{
		return NULL;
	}

	bool GetAchievementAchievedPercent(const char* pchName, float* pflPercent)
	{
		return false;
	}

	SteamAPICall_t RequestGlobalStats(int nHistoryDays)
	{
		return NULL;
	}

	// Gets the lifetime totals for an aggregated stat
#if !(defined(_WIN32) && defined(__GNUC__))
	bool GetGlobalStat(const char* pchStatName, int64* pData)
	{
		return false;
	}
	bool GetGlobalStat(const char* pchStatName, double* pData)
	{
		return false;
	}
#else
	bool GetGlobalStat(const char* pchStatName, double* pData)
	{
		return false;
	}
	bool GetGlobalStat(const char* pchStatName, int64* pData)
	{
		return false;
	}
#endif

	// Gets history for an aggregated stat. pData will be filled with daily values, starting with today.
	// So when called, pData[0] will be today, pData[1] will be yesterday, and pData[2] will be two days ago, 
	// etc. cubData is the size in bytes of the pubData buffer. Returns the number of 
	// elements actually set.
#if !(defined(_WIN32) && defined(__GNUC__))
	int32 GetGlobalStatHistory(const char* pchStatName, int64* pData, uint32 cubData)
	{
		return NULL;
	}
	int32 GetGlobalStatHistory(const char* pchStatName, double* pData, uint32 cubData)
	{
		return NULL;
	}
#else
	int32 GetGlobalStatHistory(const char* pchStatName, double* pData, uint32 cubData)
	{
		return NULL;
	}
	int32 GetGlobalStatHistory(const char* pchStatName, int64* pData, uint32 cubData)
	{
		return NULL;
	}
#endif

};
