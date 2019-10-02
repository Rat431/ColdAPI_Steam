//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef ISTEAMUSERSTATS001_H
#define ISTEAMUSERSTATS001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "UserStatsCommon.h"

abstract_class ISteamUserStats001
{
public:
	// The "schema" of a Game's UserData is really defined elsewhere, and
	// the game should know it before accessing this interface. These top
	// three functions are mostly provided for iteration / testing purposes.
	// Get the number of stats fields for nGameID
	virtual uint32 GetNumStats( CGameID nGameID ) = 0;
	// Get stat name iStat in [0,GetNumStats)
	virtual const char *GetStatName( CGameID nGameID, uint32 iStat ) = 0;
	// Get type of this field
	virtual ESteamUserStatType GetStatType( CGameID nGameID, const char *pchName ) = 0;
	// Get the number of achievements for nGameID
	virtual uint32 GetNumAchievements( CGameID nGameID ) = 0;
	// Get achievement name iAchievement in [0,GetNumAchievements)
	virtual const char *GetAchievementName( CGameID nGameID, uint32 iAchievement ) = 0;

	virtual OBSOLETE_FUNCTION uint32 GetNumGroupAchievements( CGameID ) = 0;
	virtual OBSOLETE_FUNCTION const char *GetGroupAchievementName( CGameID, uint32 iAchievement ) = 0;

	// Ask the server to send down this user's data and achievements for nGameID
	virtual bool RequestCurrentStats( CGameID nGameID ) = 0;

	// Data accessors
#if !(defined(_WIN32) && defined(__GNUC__))
	virtual bool GetStat( CGameID nGameID, const char *pchName, int32 *pData ) = 0;
	virtual bool GetStat( CGameID nGameID, const char *pchName, float *pData ) = 0;
#else
	virtual bool GetStat( CGameID nGameID, const char *pchName, float *pData ) = 0;
	virtual bool GetStat( CGameID nGameID, const char *pchName, int32 *pData ) = 0;
#endif

	// Set / update data
#if !(defined(_WIN32) && defined(__GNUC__))
	virtual bool SetStat( CGameID nGameID, const char *pchName, int32 nData ) = 0;
	virtual bool SetStat( CGameID nGameID, const char *pchName, float fData ) = 0;
#else
	virtual bool SetStat( CGameID nGameID, const char *pchName, float fData ) = 0;
	virtual bool SetStat( CGameID nGameID, const char *pchName, int32 nData ) = 0;
#endif

	virtual bool UpdateAvgRateStat( CGameID nGameID, const char *pchName, float, double dSessionLength ) = 0;

	virtual bool GetAchievement( CGameID nGameID, const char *pchName, bool *pbAchieved ) = 0;
	virtual bool GetGroupAchievement( CGameID nGameID, const char *pchName, bool *pbAchieved ) = 0;

	virtual bool SetAchievement( CGameID nGameID, const char *pchName ) = 0;
	virtual bool SetGroupAchievement( CGameID nGameID, const char *pchName ) = 0;

	// Store the current data on the server, will get a callback when set
	// And one callback for every new achievement
	virtual bool StoreStats( CGameID nGameID ) = 0;

	virtual bool ClearAchievement( CGameID nGameID, const char *pchName ) = 0;
	virtual bool ClearGroupAchievement( CGameID nGameID, const char *pchName ) = 0;

	// Gets the icon of the achievement, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetAchievementIcon( CGameID nGameID, const char *pchName ) = 0;
	// Get general attributes (display name / text, etc) for an Achievement
	virtual const char *GetAchievementDisplayAttribute( CGameID nGameID, const char *pchName, const char *pchKey ) = 0;
};

#endif // ISTEAMUSERSTATS001_H
