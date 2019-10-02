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

#ifndef EBEGINAUTHSESSIONRESULT_H
#define EBEGINAUTHSESSIONRESULT_H
#ifdef _WIN32
#pragma once
#endif

#include "EnumString.h"

// results from BeginAuthSession
typedef enum
{
	k_EBeginAuthSessionResultOK = 0,						// Ticket is valid for this game and this steamID.
	k_EBeginAuthSessionResultInvalidTicket = 1,				// Ticket is not valid.
	k_EBeginAuthSessionResultDuplicateRequest = 2,			// A ticket has already been submitted for this steamID
	k_EBeginAuthSessionResultInvalidVersion = 3,			// Ticket is from an incompatible interface version
	k_EBeginAuthSessionResultGameMismatch = 4,				// Ticket is not for this game
	k_EBeginAuthSessionResultExpiredTicket = 5,				// Ticket has expired
} EBeginAuthSessionResult;

Begin_Enum_String(EBeginAuthSessionResult)
{
	Enum_String( k_EBeginAuthSessionResultOK );						// Ticket is valid for this game and this steamID.
	Enum_String( k_EBeginAuthSessionResultInvalidTicket );				// Ticket is not valid.
	Enum_String( k_EBeginAuthSessionResultDuplicateRequest );			// A ticket has already been submitted for this steamID
	Enum_String( k_EBeginAuthSessionResultInvalidVersion );			// Ticket is from an incompatible interface version
	Enum_String( k_EBeginAuthSessionResultGameMismatch );				// Ticket is not for this game
	Enum_String( k_EBeginAuthSessionResultExpiredTicket );				// Ticket has expired
}
End_Enum_String;

#endif // EBEGINAUTHSESSIONRESULT_H