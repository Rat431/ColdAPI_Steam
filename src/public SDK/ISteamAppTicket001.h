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

#ifndef ISTEAMAPPTICKET001_H
#define ISTEAMAPPTICKET001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "AppTicketCommon.h"

//-----------------------------------------------------------------------------
// Purpose: hand out a reasonable "future proof" view of an app ownership ticket
// the raw (signed) buffer, and indices into that buffer where the appid and 
// steamid are located.  the sizes of the appid and steamid are implicit in 
// (each version of) the interface - currently uin32 appid and uint64 steamid
//-----------------------------------------------------------------------------
abstract_class ISteamAppTicket001
{
public:
	virtual uint32 GetAppOwnershipTicketData( AppId_t nAppId, void *pvSignedTicket, uint32 cbSignedTicket, uint32 *piAppId, uint32 *piSteamId, uint32 *piSignature, uint32 *pcbSignature ) = 0;
};

#endif // ISTEAMAPPTICKET001_H
