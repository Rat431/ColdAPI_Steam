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

#ifndef ISTEAM2BRIDGE001_H
#define ISTEAM2BRIDGE001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "BridgeCommon.h"

abstract_class ISteam2Bridge001
{
public:
	virtual void SetSteam2Ticket( uint8 *pubTicket, int cubTicket ) = 0;

	virtual bool SetAccountName( const char *pchAccountName ) = 0;
	virtual bool SetPassword( const char *pchPassword ) = 0;
	virtual bool SetAccountCreationTime( RTime32 rt ) = 0;

	virtual bool CreateProcess( void *lpVACBlob, uint32 cbBlobSize, char const *lpApplicationName, char *lpCommandLine, uint32 dwCreationFlags, void *lpEnvironment, char *lpCurrentDirectory, uint32 nGameID ) = 0;

	virtual EUniverse GetConnectedUniverse() = 0;
	virtual const char *GetIPCountry() = 0;

	virtual uint32 GetNumLicenses() = 0;

	virtual int32 GetLicensePackageID( uint32 nLicenseIndex ) = 0;
	virtual RTime32 GetLicenseTimeCreated( uint32 nLicenseIndex ) = 0;
	virtual RTime32 GetLicenseTimeNextProcess( uint32 nLicenseIndex ) = 0;
	virtual int32 GetLicenseMinuteLimit( uint32 nLicenseIndex ) = 0;
	virtual int32 GetLicenseMinutesUsed( uint32 nLicenseIndex ) = 0;
	virtual EPaymentMethod GetLicensePaymentMethod( uint32 nLicenseIndex ) = 0;
	virtual ELicenseFlags GetLicenseFlags( uint32 nLicenseIndex ) = 0;
	virtual const char *GetLicensePurchaseCountryCode( uint32 nLicenseIndex ) = 0;

	virtual bool SetOfflineMode( bool bOffline ) = 0;
};

#endif // ISTEAM2BRIDGE001_H
