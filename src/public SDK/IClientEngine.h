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

#ifndef ICLIENTENGINE_H
#define ICLIENTENGINE_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"

class IClientApps;
class IClientBilling;
class IClientContentServer;
class IClientFriends;
class IClientGameCoordinator;
class IClientGameServer;
class IClientGameServerItems;
class IClientGameStats;
class IClientMasterServerUpdater;
class IClientMatchmaking;
class IClientMatchmakingServers;
class IClientNetworking;
class IClientRemoteStorage;
class IClientUser;
class IClientUserItems;
class IClientUserStats;
class IClientUtils;
class IP2PController;
class IClientAppManager;
class IClientDepotBuilder;
class IConCommandBaseAccessor;
class IClientGameCoordinator;
class IClientHTTP;
class IClientGameServerStats;
class IClientConfigStore;
class IClientScreenshots;
class IClientAudio;
class IClientUnifiedMessages;
class IClientStreamLauncher;
class IClientNetworkDeviceManager;
class IClientController;
class IClientParentalSettings;
class IClientDeviceAuth;

abstract_class UNSAFE_INTERFACE IClientEngine
{

public:
	virtual HSteamPipe CreateSteamPipe() = 0; 
	virtual bool BReleaseSteamPipe( HSteamPipe hSteamPipe ) = 0;

	virtual HSteamUser CreateGlobalUser( HSteamPipe* phSteamPipe ) = 0;
	virtual HSteamUser ConnectToGlobalUser( HSteamPipe hSteamPipe ) = 0;

	virtual HSteamUser CreateLocalUser( HSteamPipe* phSteamPipe, EAccountType eAccountType ) = 0;
	virtual void CreatePipeToLocalUser( HSteamUser hSteamUser, HSteamPipe* phSteamPipe ) = 0;

	virtual void ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser ) = 0;

	virtual bool IsValidHSteamUserPipe( HSteamPipe hSteamPipe, HSteamUser hUser ) = 0;

	virtual IClientUser *GetIClientUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientGameServer *GetIClientGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	virtual void SetLocalIPBinding( uint32 unIP, uint16 usPort ) = 0;
	virtual char const *GetUniverseName( EUniverse eUniverse ) = 0;

	virtual IClientFriends *GetIClientFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientUtils *GetIClientUtils( HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientBilling *GetIClientBilling( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientMatchmaking *GetIClientMatchmaking( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientApps *GetIClientApps( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientContentServer *GetIClientContentServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientMatchmakingServers *GetIClientMatchmakingServers( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;

	virtual void RunFrame() = 0;
	virtual uint32 GetIPCCallCount() = 0;

	virtual IClientUserStats *GetIClientUserStats( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientGameServerStats *GetIClientGameServerStats( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientNetworking *GetIClientNetworking( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientRemoteStorage *GetIClientRemoteStorage( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientScreenshots *GetIClientScreenshots( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;

	virtual void SetWarningMessageHook( SteamAPIWarningMessageHook_t pFunction ) = 0;

	virtual IClientGameCoordinator *GetIClientGameCoordinator( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) = 0;

	virtual void SetOverlayNotificationPosition( ENotificationPosition eNotificationPosition ) = 0;
	virtual bool HookScreenshots( bool bHook ) = 0;
	virtual bool IsOverlayEnabled() = 0;

	virtual bool GetAPICallResult( HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed ) = 0;

	virtual IClientDepotBuilder *GetIClientDepotBuilder( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientNetworkDeviceManager *GetIClientNetworkDeviceManager( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;

	virtual void ConCommandInit( IConCommandBaseAccessor *pAccessor ) = 0;

	virtual IClientAppManager *GetIClientAppManager( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientConfigStore *GetIClientConfigStore( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;

	virtual bool BOverlayNeedsPresent() = 0;

	virtual IClientGameStats *GetIClientGameStats( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientHTTP *GetIClientHTTP( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;

	virtual bool BShutdownIfAllPipesClosed() = 0;

	virtual IClientAudio *GetIClientAudio( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientUnifiedMessages *GetIClientUnifiedMessages( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientController *GetIClientController( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientParentalSettings *GetIClientParentalSettings( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientStreamLauncher *GetIClientStreamLauncher( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
	virtual IClientDeviceAuth *GetIClientDeviceAuth( HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion ) = 0;
};

#endif // ICLIENTENGINE_H
