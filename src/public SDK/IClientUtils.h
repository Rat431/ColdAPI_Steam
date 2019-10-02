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

#ifndef ICLIENTUTILS_H
#define ICLIENTUTILS_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "UtilsCommon.h"

abstract_class UNSAFE_INTERFACE IClientUtils
{
public:

	virtual const char *GetInstallPath() = 0;
	virtual const char *GetUserBaseFolderInstallImage() = 0;
	virtual const char *GetManagedContentRoot() = 0;

	// return the number of seconds since the user 
	virtual uint32 GetSecondsSinceAppActive() = 0;
	virtual uint32 GetSecondsSinceComputerActive() = 0;
	virtual void SetComputerActive() = 0;

	// the universe this client is connecting to
	virtual EUniverse GetConnectedUniverse() = 0;

	// server time - in PST, number of seconds since January 1, 1970 (i.e unix time)
	virtual uint32 GetServerRealTime() = 0;

	// returns the 2 digit ISO 3166-1-alpha-2 format country code this client is running in (as looked up via an IP-to-location database)
	// e.g "US" or "UK".
	virtual const char *GetIPCountry() = 0;

	// returns true if the image exists, and valid sizes were filled out
	virtual bool GetImageSize( int32 iImage, uint32 *pnWidth, uint32 *pnHeight ) = 0;

	// returns true if the image exists, and the buffer was successfully filled out
	// results are returned in RGBA format
	// the destination buffer size should be 4 * height * width * sizeof(char)
	virtual bool GetImageRGBA( int32 iImage, uint8 *pubDest, int32 nDestBufferSize ) = 0;

	// returns the IP of the reporting server for valve - currently only used in Source engine games
	virtual bool GetCSERIPPort( uint32 *unIP, uint16 *usPort ) = 0;

	virtual uint32 GetNumRunningApps() = 0;

	// return the amount of battery power left in the current system in % [0..100], 255 for being on AC power
	virtual uint8 GetCurrentBatteryPower() = 0;

	virtual void SetOfflineMode( bool bOffline ) = 0;
	virtual bool GetOfflineMode() = 0;

	virtual AppId_t SetAppIDForCurrentPipe( AppId_t nAppID, bool bTrackProcess ) = 0;
	virtual AppId_t GetAppID() = 0;

	virtual void SetAPIDebuggingActive( bool bActive, bool bVerbose ) = 0;

	// API asynchronous call results
	// can be used directly, but more commonly used via the callback dispatch API (see steam_api.h)
	virtual bool IsAPICallCompleted( SteamAPICall_t hSteamAPICall, bool *pbFailed ) = 0;
	virtual ESteamAPICallFailure GetAPICallFailureReason( SteamAPICall_t hSteamAPICall ) = 0;
	virtual bool GetAPICallResult( SteamAPICall_t hSteamAPICall, void *pCallback, int32 cubCallback, int32 iCallbackExpected, bool *pbFailed ) = 0;

	virtual bool SignalAppsToShutDown() = 0;

	virtual CellID_t GetCellID() = 0;

	virtual bool BIsGlobalInstance() = 0;

	// Asynchronous call to check if file is signed, result is returned in CheckFileSignature_t
	virtual SteamAPICall_t CheckFileSignature( const char *szFileName ) = 0;

	virtual uint64 GetBuildID() = 0;

	virtual void SetCurrentUIMode( EUIMode eUIMode ) = 0;
	virtual bool ShowGamepadTextInput( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eInputLineMode, const char *szText, uint32 uMaxLength ) = 0;
	virtual uint32 GetEnteredGamepadTextLength() = 0;
	virtual bool GetEnteredGamepadTextInput( char *pchValue, uint32 cchValueMax ) = 0;
	virtual void GamepadTextInputClosed( HSteamPipe hSteamPipe, bool, const char * ) = 0;

	virtual void SetSpew( ESpewGroup eSpewGroup, int32 iSpewLevel, int32 iLogLevel ) = 0;

	virtual bool BDownloadsDisabled() = 0;

	virtual void SetFocusedWindow( EWindowType eWindowType, uint32 uUnk ) = 0;
	virtual const char *GetSteamUILanguage() = 0;
};

#endif // ICLIENTUTILS_H
