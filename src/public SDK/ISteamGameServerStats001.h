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

#ifndef ISTEAMGAMESERVERSTATS001_H
#define ISTEAMGAMESERVERSTATS001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "GameServerStatsCommon.h"



//-----------------------------------------------------------------------------
// Purpose: Functions for authenticating users via Steam to play on a game server
//-----------------------------------------------------------------------------
abstract_class ISteamGameServerStats001
{
public:
	// downloads stats for the user
	// returns a GSStatsReceived_t callback when completed
	// if the user has no stats, GSStatsReceived_t.m_eResult will be set to k_EResultFail
	// these stats will only be auto-updated for clients playing on the server. For other
	// users you'll need to call RequestUserStats() again to refresh any data
	virtual SteamAPICall_t RequestUserStats( CSteamID steamIDUser ) = 0;

	// requests stat information for a user, usable after a successful call to RequestUserStats()
	virtual bool GetUserStat( CSteamID steamIDUser, const char *pchName, int32 *pData ) = 0;
	virtual bool GetUserStat( CSteamID steamIDUser, const char *pchName, float *pData ) = 0;
	virtual bool GetUserAchievement( CSteamID steamIDUser, const char *pchName, bool *pbAchieved ) = 0;

	// Set / update stats and achievements. 
	// Note: These updates will work only on stats game servers are allowed to edit and only for 
	// game servers that have been declared as officially controlled by the game creators. 
	// Set the IP range of your official servers on the Steamworks page
	virtual bool SetUserStat( CSteamID steamIDUser, const char *pchName, int32 nData ) = 0;
	virtual bool SetUserStat( CSteamID steamIDUser, const char *pchName, float fData ) = 0;
	virtual bool UpdateUserAvgRateStat( CSteamID steamIDUser, const char *pchName, float flCountThisSession, double dSessionLength ) = 0;

	virtual bool SetUserAchievement( CSteamID steamIDUser, const char *pchName ) = 0;
	virtual bool ClearUserAchievement( CSteamID steamIDUser, const char *pchName ) = 0;

	// Store the current data on the server, will get a GSStatsStored_t callback when set.
	//
	// If the callback has a result of k_EResultInvalidParam, one or more stats 
	// uploaded has been rejected, either because they broke constraints
	// or were out of date. In this case the server sends back updated values.
	// The stats should be re-iterated to keep in sync.
	virtual SteamAPICall_t StoreUserStats( CSteamID steamIDUser ) = 0;
};

#endif // ISTEAMGAMESERVERSTATS001_H
