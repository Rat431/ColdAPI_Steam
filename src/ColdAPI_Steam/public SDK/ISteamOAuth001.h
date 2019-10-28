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

#ifndef ISTEAMOAUTH001_H
#define ISTEAMOAUTH001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "OAuthCommon.h"


abstract_class OBSOLETE_INTERFACE ISteamOAuth001
{
public:
	virtual SteamAPICall_t RequestOAuthTokenForApp( const char *cszOAuthScope ) = 0;
	virtual bool GetOAuthTokenForApp( void *pubBuffer, int32 cubBuffer, uint32 *puTokenSize ) = 0;
	virtual void InvalidateOAuthTokenForApp() = 0;
};


#endif // ISTEAMOAUTH001_H

