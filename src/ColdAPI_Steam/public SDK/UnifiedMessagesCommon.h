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

#ifndef UNIFIEDMESSAGESCOMMON_H
#define UNIFIEDMESSAGESCOMMON_H
#ifdef _WIN32
#pragma once
#endif


// versions
#define CLIENTUNIFIEDMESSAGES_INTERFACE_VERSION "CLIENTUNIFIEDMESSAGES_INTERFACE_VERSION001"
#define STEAMUNIFIEDMESSAGES_INTERFACE_VERSION_001 "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION001"

typedef uint64 ClientUnifiedMessageHandle;

// callbacks
#pragma pack( push, 8 )

struct SteamUnifiedMessagesSendMethodResult_t
{
	enum { k_iCallback = k_iClientUnifiedMessagesCallbacks + 1 };
	ClientUnifiedMessageHandle m_hHandle;	// The handle returned by SendMethod().
	uint64 m_unContext;						// Context provided when calling SendMethod().
	EResult m_eResult;						// The result of the method call.
	uint32 m_unResponseSize;				// The size of the response.
};

#pragma pack( pop )


#endif // UNIFIEDMESSAGESCOMMON_H
