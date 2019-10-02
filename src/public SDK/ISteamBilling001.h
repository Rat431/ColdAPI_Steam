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

#ifndef ISTEAMBILLING001_H
#define ISTEAMBILLING001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "BillingCommon.h"

//-----------------------------------------------------------------------------
// Purpose: interface to billing
//-----------------------------------------------------------------------------
abstract_class OBSOLETE_INTERFACE ISteamBilling001
{
public:
	// Sets the billing address in the ISteamBilling object for use by other ISteamBilling functions (not stored on server)
	virtual bool SetBillingAddress( const char *pchName, const char *pchAddress1, const char *pchAddress2, const char *pchCity, const char *pchPostcode, const char *pchState, const char *pchCountry, const char *pchPhone ) = 0;
	// Gets any previous set billing address in the ISteamBilling object (not stored on server)
	virtual bool GetBillingAddress( char *pchName, char *pchAddress1, char *pchAddress2, char *pchCity, char *pchPostcode, char *pchState, char *pchCountry, char *pchPhone ) = 0;
	// Sets the billing address in the ISteamBilling object for use by other ISteamBilling functions (not stored on server)
	virtual bool SetShippingAddress( const char *pchName, const char *pchAddress1, const char *pchAddress2, const char *pchCity, const char *pchPostcode, const char *pchState, const char *pchCountry, const char *pchPhone ) = 0;
	// Gets any previous set billing address in the ISteamBilling object (not stored on server)
	virtual bool GetShippingAddress( char *pchName, char *pchAddress1, char *pchAddress2, char *pchCity, char *pchPostcode, char *pchState, char *pchCountry, char *pchPhone ) = 0;
	// Ask the server for the final price of package: requires that ISteamBilling billing & shipping address are set (can be same)
	virtual bool GetFinalPrice( int32 nPackageID ) = 0;

	// Sets the credit card info in the ISteamBilling object for use by other ISteamBilling functions  (may eventually also be stored on server)
	virtual bool SetCardInfo( ECreditCardType eCreditCardType, const char *pchCardNumber, const char *pchCardHolderName, const char *pchCardExpYear, const char *pchCardExpMonth, const char *pchCardCVV2 ) = 0;
	// Gets any credit card info in the ISteamBilling object (not stored on server)
	virtual bool GetCardInfo( ECreditCardType *eCreditCardType, char *pchCardNumber, char *pchCardHolderName, char *pchCardExpYear, char *pchCardExpMonth, char *pchCardCVV2 ) = 0;

	// Ask the server to purchase a package: requires that ISteamBilling cardinfo, billing & shipping address are set
	// gidCardID - if non-NIL, use a server stored card
	// bStoreCardInfo - Should this cardinfo also be stored on the server
	virtual bool Purchase( int32 nPackageID, int32 nExpectedCostCents, uint64 gidCardID, bool bStoreCardInfo ) = 0;
};


#endif // ISTEAMBILLING001_H

