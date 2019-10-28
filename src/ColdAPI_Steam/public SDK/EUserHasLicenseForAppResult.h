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

#ifndef EUSERHASLICENSEFORAPPRESULT_H
#define EUSERHASLICENSEFORAPPRESULT_H
#ifdef _WIN32
#pragma once
#endif

#include "EnumString.h"

typedef enum
{
	k_EUserHasLicenseResultHasLicense = 0,					// User has a license for specified app
	k_EUserHasLicenseResultDoesNotHaveLicense = 1,			// User does not have a license for the specified app
	k_EUserHasLicenseResultNoAuth = 2,						// User has not been authenticated
} EUserHasLicenseForAppResult;

/*
Begin_Enum_String( EUserHasLicenseForAppResult )
{
	Enum_String( k_EUserHasLicenseResultHasLicense );
	Enum_String( k_EUserHasLicenseResultDoesNotHaveLicense );
	Enum_String( k_EUserHasLicenseResultNoAuth );
}
End_Enum_String( EUserHasLicenseForAppResult );*/

#endif // EUSERHASLICENSEFORAPPRESULT_H