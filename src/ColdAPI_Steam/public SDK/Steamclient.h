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


#ifndef STEAMCLIENT_H
#define STEAMCLIENT_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"

#if defined(__GNUC__) && defined(_WIN32)
	// This ugly hack allows us to provide GCC compatibility on windows without much effort
	#pragma push_macro("virtual")
	#undef virtual
	#define virtual virtual __thiscall
#endif

// client
#include "ISteamClient006.h"
#include "ISteamClient007.h"
#include "ISteamClient008.h"
#include "ISteamClient009.h"
#include "ISteamClient010.h"
#include "ISteamClient011.h"
#include "ISteamClient012.h"
#include "ISteamClient014.h"
#include "ISteamClient015.h"
#include "ISteamClient016.h"
#include "ISteamClient017.h"

// friends
#include "ISteamFriends001.h"
#include "ISteamFriends002.h"
#include "ISteamFriends003.h"
#include "ISteamFriends004.h"
#include "ISteamFriends005.h"
#include "ISteamFriends006.h"
#include "ISteamFriends007.h"
#include "ISteamFriends008.h"
#include "ISteamFriends009.h"
#include "ISteamFriends010.h"
#include "ISteamFriends011.h"
#include "ISteamFriends012.h"
#include "ISteamFriends013.h"
#include "ISteamFriends014.h"
#include "ISteamFriends015.h"

// screenshots
#include "ISteamScreenshots001.h"
#include "ISteamScreenshots002.h"

// user
#include "ISteamUser004.h"
#include "ISteamUser005.h"
#include "ISteamUser006.h"
#include "ISteamUser007.h"
#include "ISteamUser008.h"
#include "ISteamUser009.h"
#include "ISteamUser010.h"
#include "ISteamUser011.h"
#include "ISteamUser012.h"
#include "ISteamUser013.h"
#include "ISteamUser014.h"
#include "ISteamUser015.h"
#include "ISteamUser016.h"
#include "ISteamUser017.h"
#include "ISteamUser018.h"

// OAuth
#include "ISteamOAuth001.h"

// apps
#include "ISteamApps001.h"
#include "ISteamApps002.h"
#include "ISteamApps003.h"
#include "ISteamApps004.h"
#include "ISteamApps005.h"
#include "ISteamApps006.h"
#include "ISteamApps007.h"

// user stats
#include "ISteamUserStats001.h"
#include "ISteamUserStats002.h"
#include "ISteamUserStats003.h"
#include "ISteamUserStats004.h"
#include "ISteamUserStats005.h"
#include "ISteamUserStats006.h"
#include "ISteamUserStats007.h"
#include "ISteamUserStats008.h"
#include "ISteamUserStats009.h"
#include "ISteamUserStats010.h"
#include "ISteamUserStats011.h"

// utils
#include "ISteamUtils001.h"
#include "ISteamUtils002.h"
#include "ISteamUtils003.h"
#include "ISteamUtils004.h"
#include "ISteamUtils005.h"
#include "ISteamUtils006.h"
#include "ISteamUtils007.h"

// game server
#include "ISteamGameServer002.h"
#include "ISteamGameServer003.h"
#include "ISteamGameServer004.h"
#include "ISteamGameServer005.h"
#include "ISteamGameServer006.h"
#include "ISteamGameServer007.h"
#include "ISteamGameServer008.h"
#include "ISteamGameServer009.h"
#include "ISteamGameServer010.h"
#include "ISteamGameServer011.h"
#include "ISteamGameServer012.h"

// master server updater
#include "ISteamMasterServerUpdater001.h"

// matchmaking
#include "ISteamMatchmaking001.h"
#include "ISteamMatchmaking002.h"
#include "ISteamMatchmaking003.h"
#include "ISteamMatchmaking004.h"
#include "ISteamMatchmaking005.h"
#include "ISteamMatchmaking006.h"
#include "ISteamMatchmaking007.h"
#include "ISteamMatchmaking008.h"
#include "ISteamMatchmaking009.h"

// matchmaking servers
#include "ISteamMatchmakingServers001.h"
#include "ISteamMatchmakingServers002.h"

// networking
#include "ISteamNetworking001.h"
#include "ISteamNetworking002.h"
#include "ISteamNetworking003.h"
#include "ISteamNetworking004.h"
#include "ISteamNetworking005.h"

// billing
#include "ISteamBilling001.h"
#include "ISteamBilling002.h"

// remote storage
#include "ISteamRemoteStorage001.h"
#include "ISteamRemoteStorage002.h"
#include "ISteamRemoteStorage003.h"
#include "ISteamRemoteStorage004.h"
#include "ISteamRemoteStorage005.h"
#include "ISteamRemoteStorage006.h"
#include "ISteamRemoteStorage007.h"
#include "ISteamRemoteStorage008.h"
#include "ISteamRemoteStorage009.h"
#include "ISteamRemoteStorage010.h"
#include "ISteamRemoteStorage011.h"
#include "ISteamRemoteStorage012.h"
#include "ISteamRemoteStorage013.h"

// content server
#include "ISteamContentServer001.h"
#include "ISteamContentServer002.h"

// steam 2 bridge
#include "ISteam2Bridge001.h"
#include "ISteam2Bridge002.h"

// game coordinator
#include "ISteamGameCoordinator001.h"

// game server stats
#include "ISteamGameServerStats001.h"

// game stats
#include "ISteamGameStats001.h"

// app ticket
#include "ISteamAppTicket001.h"

// applist
#include "ISteamAppList001.h"

// http
#include "ISteamHTTP001.h"
#include "ISteamHTTP002.h"

// unified messages
#include "ISteamUnifiedMessages001.h"

// stream launcher
#include "ISteamStreamLauncher001.h"

// ugc
#include "ISteamUGC001.h"
#include "ISteamUGC002.h"
#include "ISteamUGC003.h"
#include "ISteamUGC004.h"
#include "ISteamUGC005.h"
#include "ISteamUGC007.h"

// music
#include "ISteamMusic001.h"

// music remote
#include "ISteamMusicRemote001.h"

// controller
#include "ISteamController001.h"
#include "ISteamController003.h"

// html surface
#include "ISteamHTMLSurface002.h"
#include "ISteamHTMLSurface003.h"

// inventory
#include "ISteamInventory001.h"

// video
#include "ISteamVideo001.h"

#ifndef NO_ICLIENT
// client interfaces
#include "IClientEngine.h"

#include "IClientAppManager.h"
#include "IClientApps.h"
#include "IClientAudio.h"
#include "IClientBilling.h"
#include "IClientContentServer.h"
#include "IClientDepotBuilder.h"
#include "IClientFriends.h"
#include "IClientGameCoordinator.h"
#include "IClientGameServer.h"
#include "IClientGameServerStats.h"
#include "IClientGameStats.h"
#include "IClientMasterServerUpdater.h"
#include "IClientMatchmaking.h"
#include "IClientMatchmakingServers.h"
#include "IClientNetworking.h"
#include "IClientRemoteStorage.h"
#include "IClientScreenshots.h"
#include "IClientUser.h"
#include "IClientUserStats.h"
#include "IClientUtils.h"
#include "IClientHTTP.h"
#include "IClientConfigStore.h"
#include "IClientUnifiedMessages.h"
#include "IClientStreamLauncher.h"
#include "IClientNetworkDeviceManager.h"
#include "IClientDeviceAuth.h"
#endif // NO_ICLIENT

// callback
#include "CCallback.h"

// steam_api
#ifdef VERSION_SAFE_STEAM_API_INTERFACES
	#include "CSteamAPIContext.h"
#endif // VERSION_SAFE_STEAM_API_INTERFACES

#if defined(__GNUC__) && defined(_WIN32)
	#pragma pop_macro("virtual")
#endif

// Breakpad
S_API errno_t STEAM_CALL Breakpad_SetSteamID( uint64 ulSteamID );
S_API errno_t STEAM_CALL Breakpad_SteamSetSteamID( uint64 ulSteamID );
S_API void STEAM_CALL Breakpad_SteamMiniDumpInit( uint32 a, const char *b, const char *c );
S_API errno_t STEAM_CALL Breakpad_SteamWriteMiniDumpSetComment( const char *pchMsg );
S_API void STEAM_CALL Breakpad_SteamWriteMiniDumpUsingExceptionInfoWithBuildId( int a, int b );


// Steam user
S_API bool STEAM_CALL Steam_BConnected( HSteamUser hUser, HSteamPipe hSteamPipe );
S_API bool STEAM_CALL Steam_BLoggedOn( HSteamUser hUser, HSteamPipe hSteamPipe );
S_API void STEAM_CALL Steam_LogOn( HSteamUser hUser, HSteamPipe hSteamPipe, uint64 ulSteamID );
S_API void STEAM_CALL Steam_LogOff( HSteamUser hUser, HSteamPipe hSteamPipe );
S_API int STEAM_CALL Steam_InitiateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, void *pBlob, int cbMaxBlob, uint64 steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure );
S_API void STEAM_CALL Steam_TerminateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, uint32 unIPServer, uint16 usPortServer );

// Steam callbacks
S_API bool STEAM_CALL Steam_BGetCallback( HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg );
S_API void STEAM_CALL Steam_FreeLastCallback( HSteamPipe hSteamPipe );
S_API bool STEAM_CALL Steam_GetAPICallResult( HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed );

// Steam client
S_API HSteamPipe STEAM_CALL Steam_CreateSteamPipe();
S_API bool STEAM_CALL Steam_BReleaseSteamPipe( HSteamPipe hSteamPipe );
S_API HSteamUser STEAM_CALL Steam_CreateLocalUser( HSteamPipe *phSteamPipe, EAccountType eAccountType );
S_API HSteamUser STEAM_CALL Steam_CreateGlobalUser( HSteamPipe *phSteamPipe );
S_API HSteamUser STEAM_CALL Steam_ConnectToGlobalUser( HSteamPipe hSteamPipe );
S_API void STEAM_CALL Steam_ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser );
S_API void STEAM_CALL Steam_SetLocalIPBinding( uint32 unIP, uint16 usLocalPort );

// Steam game server
S_API int STEAM_CALL Steam_GSGetSteamGameConnectToken( HSteamUser hUser, HSteamPipe hSteamPipe, void *pBlob, int cbBlobMax ); // does this exist anymore?
S_API void* STEAM_CALL Steam_GetGSHandle( HSteamUser hUser, HSteamPipe hSteamPipe );
S_API bool STEAM_CALL Steam_GSSendSteam2UserConnect( void *phSteamHandle, uint32 unUserID, const void *pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie );
S_API bool STEAM_CALL Steam_GSSendUserDisconnect( void *phSteamHandle, uint64 ulSteamID, uint32 unUserID );
S_API OBSOLETE_FUNCTION bool STEAM_CALL Steam_GSSendUserStatusResponse( void *phSteamHandle, uint64 ulSteamID, int nSecondsConnected, int nSecondsSinceLast );
S_API bool STEAM_CALL Steam_GSUpdateStatus( void *phSteamHandle, int cPlayers, int cPlayersMax, int cBotPlayers, const char *pchServerName, const char *pchMapName );
S_API bool STEAM_CALL Steam_GSRemoveUserConnect( void *phSteamHandle, uint32 unUserID );
S_API void STEAM_CALL Steam_GSSetSpawnCount( void *phSteamHandle, uint32 ucSpawn );
S_API bool STEAM_CALL Steam_GSGetSteam2GetEncryptionKeyToSendToNewClient( void *phSteamHandle, void *pvEncryptionKey, uint32 *pcbEncryptionKey, uint32 cbMaxEncryptionKey );
S_API void STEAM_CALL Steam_GSLogOn( void *phSteamHandle );
S_API void STEAM_CALL Steam_GSLogOff( void *phSteamHandle );
S_API bool STEAM_CALL Steam_GSBLoggedOn( void *phSteamHandle );
S_API bool STEAM_CALL Steam_GSSetServerType( void *phSteamHandle, int32 nAppIdServed, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char *pchGameDir, const char *pchVersion );
S_API bool STEAM_CALL Steam_GSBSecure( void *phSteamHandle);


//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//	Steam API setup & shutdown
//
//	These functions manage loading, initializing and shutdown of the steamclient.dll
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

// S_API void SteamAPI_Init(); (see below)
S_API void SteamAPI_Shutdown();

// checks if a local Steam client is running 
S_API bool SteamAPI_IsSteamRunning();

// Detects if your executable was launched through the Steam client, and restarts your game through 
// the client if necessary. The Steam client will be started if it is not running.
//
// Returns: true if your executable was NOT launched through the Steam client. This function will
//          then start your application through the client. Your current process should exit.
//
//          false if your executable was started through the Steam client or a steam_appid.txt file
//          is present in your game's directory (for development). Your current process should continue.
//
// NOTE: This function should be used only if you are using CEG or not using Steam's DRM. Once applied
//       to your executable, Steam's DRM will handle restarting through Steam if necessary.
S_API bool SteamAPI_RestartAppIfNecessary( uint32 unOwnAppID );

// crash dump recording functions
S_API void SteamAPI_WriteMiniDump( uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID );
S_API void SteamAPI_SetMiniDumpComment( const char *pchMsg );

// this should be called before the game initialized the steam APIs
// pchDate should be of the format "Mmm dd yyyy" (such as from the __DATE__ macro )
// pchTime should be of the format "hh:mm:ss" (such as from the __TIME__ macro )
// bFullMemoryDumps (Win32 only) -- writes out a uuid-full.dmp in the client/dumps folder
// pvContext-- can be NULL, will be the void * context passed into m_pfnPreMinidumpCallback
// PFNPreMinidumpCallback m_pfnPreMinidumpCallback   -- optional callback which occurs just before a .dmp file is written during a crash.  Applications can hook this to allow adding additional information into the .dmp comment stream.
S_API void SteamAPI_UseBreakpadCrashHandler( char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback );
S_API void SteamAPI_SetBreakpadAppID( uint32 unAppID );

// interface pointers, configured by SteamAPI_Init()
S_API_UNSAFE ISteamClient009* STEAM_CALL SteamClient();

// VERSION_SAFE_STEAM_API_INTERFACES is usually not necessary, but it provides safety against releasing
// new steam_api.dll's without recompiling/rereleasing modules that use it.
//
// If you use VERSION_SAFE_STEAM_API_INTERFACES, then you should call SteamAPI_InitSafe(). Also, to get the 
// Steam interfaces, you must create and Init() a CSteamAPIContext (below) and use the interfaces in there.
//
// If you don't use VERSION_SAFE_STEAM_API_INTERFACES, then you can use SteamAPI_Init() and the SteamXXXX() 
// functions below to get at the Steam interfaces.
//
#ifdef VERSION_SAFE_STEAM_API_INTERFACES
S_API bool STEAM_CALL SteamAPI_InitSafe();
#else
S_API bool STEAM_CALL SteamAPI_Init();

S_API_UNSAFE ISteamUser013* STEAM_CALL SteamUser();
S_API_UNSAFE ISteamFriends005* STEAM_CALL SteamFriends();
S_API_UNSAFE ISteamUtils005* STEAM_CALL SteamUtils();
S_API_UNSAFE ISteamMatchmaking008* STEAM_CALL SteamMatchmaking();
S_API_UNSAFE ISteamUserStats007* STEAM_CALL SteamUserStats();
S_API_UNSAFE ISteamApps003* STEAM_CALL SteamApps();
S_API_UNSAFE ISteamNetworking003* STEAM_CALL SteamNetworking();
S_API_UNSAFE ISteamMatchmakingServers002* STEAM_CALL SteamMatchmakingServers();
S_API_UNSAFE ISteamRemoteStorage002* STEAM_CALL SteamRemoteStorage();
#endif // VERSION_SAFE_STEAM_API_INTERFACES

// sets whether or not Steam_RunCallbacks() should do a try {} catch (...) {} around calls to issuing callbacks
S_API void STEAM_CALL SteamAPI_SetTryCatchCallbacks( bool bTryCatchCallbacks );

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//	steam callback and call-result helpers
//
//	The following macros and classes are used to register your application for
//	callbacks and call-results, which are delivered in a predictable manner.
//
//	STEAM_CALLBACK macros are meant for use inside of a C++ class definition.
//	They map a Steam notification callback directly to a class member function
//	which is automatically prototyped as "void func( callback_type *pParam )".
//
//	CCallResult is used with specific Steam APIs that return "result handles".
//	The handle can be passed to a CCallResult object's Set function, along with
//	an object pointer and member-function pointer. The member function will
//	be executed once the results of the Steam API call are available.
//
//	CCallback and CCallbackManual classes can be used instead of STEAM_CALLBACK
//	macros if you require finer control over registration and unregistration.
//
//	Callbacks and call-results are queued automatically and are only
//	delivered/executed when your application calls SteamAPI_RunCallbacks().
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
S_API void SteamAPI_RunCallbacks();



// Internal functions used by the utility CCallback objects to receive callbacks
S_API void SteamAPI_RegisterCallback( class CCallbackBase *pCallback, int iCallback );
S_API void SteamAPI_UnregisterCallback( class CCallbackBase *pCallback );
// Internal functions used by the utility CCallResult objects to receive async call results
S_API void SteamAPI_RegisterCallResult( class CCallbackBase *pCallback, SteamAPICall_t hAPICall );
S_API void SteamAPI_UnregisterCallResult( class CCallbackBase *pCallback, SteamAPICall_t hAPICall );

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//	steamclient.dll private wrapper functions
//
//	The following functions are part of abstracting API access to the steamclient.dll, but should only be used in very specific cases
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
S_API void STEAM_CALL Steam_RunCallbacks( HSteamPipe hSteamPipe, bool bGameServerCallbacks );
S_API void STEAM_CALL Steam_RegisterInterfaceFuncs( void *hModule );

S_API HSteamUser STEAM_CALL Steam_GetHSteamUserCurrent();

S_API const char* STEAM_CALL SteamAPI_GetSteamInstallPath();

// used in version safe api
S_API HSteamPipe STEAM_CALL GetHSteamPipe();
S_API HSteamUser STEAM_CALL GetHSteamUser();

S_API HSteamPipe STEAM_CALL SteamAPI_GetHSteamPipe();
S_API HSteamUser STEAM_CALL SteamAPI_GetHSteamUser();

//S_API bool STEAM_CALL SteamGameServer_InitSafe( uint32 unIP, uint16 usPort, uint16 usGamePort, uint16 usSpectatorPort, uint16 usQueryPort, EServerMode eServerMode, const char *pchGameDir, const char *pchVersionString );
//S_API bool STEAM_CALL SteamGameServer_Init( uint32 unIP, uint16 usPort, uint16 usGamePort, uint16 usSpectatorPort, uint16 usQueryPort, EServerMode eServerMode, const char *pchGameDir, const char *pchVersionString );

S_API void STEAM_CALL SteamGameServer_Shutdown();
S_API void STEAM_CALL SteamGameServer_RunCallbacks();

S_API bool STEAM_CALL SteamGameServer_BSecure();
S_API uint64 STEAM_CALL SteamGameServer_GetSteamID();

S_API HSteamPipe STEAM_CALL SteamGameServer_GetHSteamPipe();
S_API HSteamUser STEAM_CALL SteamGameServer_GetHSteamUser(); 
S_API int32 STEAM_CALL SteamGameServer_GetIPCCallCount();

// Note: if you pass MASTERSERVERUPDATERPORT_USEGAMESOCKETSHARE for usQueryPort, then it will use "GameSocketShare" mode, 
// which means that the game is responsible for sending and receiving UDP packets for the master 
// server updater. See references to GameSocketShare in isteammasterserverupdater.h.
//
// Pass 0 for usGamePort or usSpectatorPort if you're not using that. Then, the master server updater will report 
// what's running based on that.
#ifdef VERSION_SAFE_STEAM_API_INTERFACES
S_API bool STEAM_CALL SteamGameServer_InitSafe( uint32 unIP, uint16 usPort, uint16 usGamePort, uint16 usSpectatorPort, uint16 usQueryPort, EServerMode eServerMode, const char *pchGameDir, const char *pchVersionString );
#else
S_API bool STEAM_CALL SteamGameServer_Init( uint32 unIP, uint16 usPort, uint16 usGamePort, uint16 usSpectatorPort, uint16 usQueryPort, EServerMode eServerMode, const char *pchGameDir, const char *pchVersionString );

S_API_UNSAFE ISteamGameServer010* STEAM_CALL SteamGameServer();
S_API_UNSAFE ISteamUtils005* STEAM_CALL SteamGameServerUtils();
S_API_UNSAFE ISteamMasterServerUpdater001* STEAM_CALL SteamMasterServerUpdater();
S_API_UNSAFE ISteamNetworking003* STEAM_CALL SteamGameServerNetworking();
S_API_UNSAFE ISteamGameServerStats001* STEAM_CALL SteamGameServerStats();
#endif

//content server
S_API_UNSAFE ISteamContentServer002* STEAM_CALL SteamContentServer();
S_API_UNSAFE ISteamUtils005* STEAM_CALL SteamContentServerUtils();
S_API bool STEAM_CALL SteamContentServer_Init(uint32 unIP, uint16 usPort);

S_API void STEAM_CALL SteamContentServer_Shutdown();
S_API void STEAM_CALL SteamContentServer_RunCallbacks();


// Purpose: utilities to decode/decrypt a ticket from the
// ISteamUser::RequestEncryptedAppTicket, ISteamUser::GetEncryptedAppTicket API
// 
// To use: declare CSteamEncryptedAppTicket, then call BDecryptTicket
// if BDecryptTicket returns true, other accessors are valid
static const int k_nSteamEncryptedAppTicketSymmetricKeyLen = 32;				


S_API bool SteamEncryptedAppTicket_BDecryptTicket( const uint8 *rgubTicketEncrypted, uint32 cubTicketEncrypted,
												  uint8 *rgubTicketDecrypted, uint32 *pcubTicketDecrypted,
												  const uint8 rgubKey[k_nSteamEncryptedAppTicketSymmetricKeyLen], int cubKey );

S_API bool SteamEncryptedAppTicket_BIsTicketForApp( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID );

S_API RTime32 SteamEncryptedAppTicket_GetTicketIssueTime( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted );

S_API void SteamEncryptedAppTicket_GetTicketSteamID( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, CSteamID *psteamID );

S_API AppId_t SteamEncryptedAppTicket_GetTicketAppID( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted );

S_API bool SteamEncryptedAppTicket_BUserOwnsAppInTicket( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID );

S_API bool SteamEncryptedAppTicket_BUserIsVacBanned( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted );

S_API const uint8 *SteamEncryptedAppTicket_GetUserVariableData( uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, uint32 *pcubUserData );

#endif // STEAMCLIENT_H
