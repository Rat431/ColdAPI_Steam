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

#ifndef ISTEAMUNIFIEDMESSAGES001_H
#define ISTEAMUNIFIEDMESSAGES001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "UnifiedMessagesCommon.h"

abstract_class ISteamUnifiedMessages001
{
public:
	static const ClientUnifiedMessageHandle k_InvalidUnifiedMessageHandle = 0;

	// Sends a service method (in binary serialized form) using the Steam Client.
	// Returns a unified message handle (k_InvalidUnifiedMessageHandle if could not send the message).
	virtual ClientUnifiedMessageHandle SendMethod( const char *pchServiceMethod, const void *pRequestBuffer, uint32 unRequestBufferSize, uint64 unContext ) = 0;

	// Gets the size of the response and the EResult. Returns false if the response is not ready yet.
	virtual bool GetMethodResponseInfo( ClientUnifiedMessageHandle hHandle, uint32 *punResponseSize, EResult *peResult ) = 0;

	// Gets a response in binary serialized form (and optionally release the corresponding allocated memory).
	virtual bool GetMethodResponseData( ClientUnifiedMessageHandle hHandle, void *pResponseBuffer, uint32 unResponseBufferSize, bool bAutoRelease ) = 0;

	// Releases the message and its corresponding allocated memory.
	virtual bool ReleaseMethod( ClientUnifiedMessageHandle hHandle ) = 0;

	// Sends a service notification (in binary serialized form) using the Steam Client.
	// Returns true if the notification was sent successfully.
	virtual bool SendNotification( const char *pchServiceNotification, const void *pNotificationBuffer, uint32 unNotificationBufferSize ) = 0;
};


#endif // ISTEAMUNIFIEDMESSAGES001_H
