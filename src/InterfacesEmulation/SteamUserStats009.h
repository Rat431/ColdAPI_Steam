#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUserStats009.h"

class SteamUserStatsIn009 : public ISteamUserStats009
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

	bool GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, RTime32* prtTime)
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

	SteamAPICall_t RequestUserStats(CSteamID steamIDUser)
	{
		return NULL;
	}


	// requests stat information for a user, usable after a successful call to RequestUserStats()
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
	bool GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char* pchName, bool* pbAchieved, RTime32* prtTime)
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

	bool GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32* pDetails, int cDetailsMax)
	{
		return false;
	}

	SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount)
	{
		return NULL;
	}

	SteamAPICall_t AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, uint64_t hUGC)
	{
		return NULL;
	}

	SteamAPICall_t GetNumberOfCurrentPlayers()
	{
		return NULL;
	}
};