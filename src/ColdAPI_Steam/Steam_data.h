#pragma once
#include "Bridge.h"
#include "public SDK/ClientCommon.h"
#include "public SDK/SteamTypes.h"

// Steam standard functions.
EXPORTMYFUNC bool SteamAPI_Init();
EXPORTMYFUNC bool SteamAPI_InitSafe();
EXPORTMYFUNC void SteamAPI_Shutdown();
EXPORTMYFUNC bool SteamAPI_IsSteamRunning();
EXPORTMYFUNC const char* SteamAPI_GetSteamInstallPath();
EXPORTMYFUNC bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID);

// SteamCustom attempt.
EXPORTMYFUNC void SteamAPI_ReleaseCurrentThreadMemory();

// SteamMiniDump Attempt.
EXPORTMYFUNC void SteamAPI_SetMiniDumpComment(const char* pchMsg);
EXPORTMYFUNC void SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID);

// SteamInternal attempt.
EXPORTMYFUNC void* SteamInternal_CreateInterface(const char* interfacename);
EXPORTMYFUNC void* SteamInternal_FindOrCreateUserInterface(int32_t hSteamUser, const char* pszVersion);
EXPORTMYFUNC void* SteamInternal_FindOrCreateGameServerInterface(int32_t hSteamUser, const char* pszVersion);
EXPORTMYFUNC void* SteamInternal_ContextInit(void* pContextInitData);

// SteamAccessors attempt.
EXPORTMYFUNC void* SteamApps();
EXPORTMYFUNC void* SteamClient();
EXPORTMYFUNC void* SteamController();
EXPORTMYFUNC void* SteamBilling();
EXPORTMYFUNC void* SteamContentServer();
EXPORTMYFUNC void* SteamFriends();
EXPORTMYFUNC void* SteamParentalSettings();
EXPORTMYFUNC void* SteamGameSearch();
EXPORTMYFUNC void* SteamInput();
EXPORTMYFUNC void* SteamParties();
EXPORTMYFUNC void* SteamGameServer();
EXPORTMYFUNC void* SteamGameServerHTTP();
EXPORTMYFUNC void* SteamGameCoordinator();
EXPORTMYFUNC void* SteamGameServerInventory();
EXPORTMYFUNC void* SteamGameServerNetworking();
EXPORTMYFUNC void* SteamGameServerStats();
EXPORTMYFUNC void* SteamGameServerUGC();
EXPORTMYFUNC void* SteamGameServerUtils();
EXPORTMYFUNC void* SteamHTMLSurface();
EXPORTMYFUNC void* SteamAppList();
EXPORTMYFUNC void* SteamHTTP();
EXPORTMYFUNC void* SteamInventory();
EXPORTMYFUNC void* SteamMatchmaking();
EXPORTMYFUNC void* SteamMatchmakingServers();
EXPORTMYFUNC void* SteamMusic();
EXPORTMYFUNC void* SteamMusicRemote();
EXPORTMYFUNC void* SteamNetworking();
EXPORTMYFUNC void* SteamRemoteStorage();
EXPORTMYFUNC void* SteamScreenshots();
EXPORTMYFUNC void* SteamUnifiedMessages();
EXPORTMYFUNC void* SteamUGC();
EXPORTMYFUNC void* SteamUser();
EXPORTMYFUNC void* SteamUserStats();
EXPORTMYFUNC void* SteamUtils();
EXPORTMYFUNC void* SteamVideo();
EXPORTMYFUNC void* SteamMasterServerUpdater();
EXPORTMYFUNC void* SteamRemotePlay();

// SteamHandlers attempt.
EXPORTMYFUNC int32_t GetHSteamUser();
EXPORTMYFUNC int32_t GetHSteamPipe();
EXPORTMYFUNC int32_t SteamAPI_GetHSteamUser();
EXPORTMYFUNC int32_t SteamAPI_GetHSteamPipe();
EXPORTMYFUNC int32_t SteamGameServer_GetHSteamUser();
EXPORTMYFUNC int32_t SteamGameServer_GetHSteamPipe();
EXPORTMYFUNC int32_t Steam_GetHSteamUserCurrent();

// SteamCallBacks attempt.
EXPORTMYFUNC void SteamAPI_RunCallbacks();
EXPORTMYFUNC void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks);
EXPORTMYFUNC void SteamAPI_RegisterCallback(void* pCallback, int iCallback);
EXPORTMYFUNC void SteamAPI_UnregisterCallback(void* pCallback, int iCallback);
EXPORTMYFUNC void SteamAPI_RegisterCallResult(void* pCallback, uint64_t hAPICall);
EXPORTMYFUNC void SteamAPI_UnregisterCallResult(void* pCallback, uint64_t hAPICall);
EXPORTMYFUNC bool SteamGameServer_BSecure();
EXPORTMYFUNC void SteamGameServer_Shutdown();
EXPORTMYFUNC void SteamGameServer_RunCallbacks();

// SteamServer attempt.
EXPORTMYFUNC uint64_t SteamGameServer_GetSteamID();

EXPORTMYFUNC bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char* pchVersionString);
EXPORTMYFUNC bool SteamGameServer_InitSafe(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char* pchVersionString);
EXPORTMYFUNC bool SteamInternal_GameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char* pchVersionString);


// Steam client exports

// Breakpad
EXPORTMYFUNC errno_t Breakpad_SetSteamID(uint64 ulSteamID);
EXPORTMYFUNC errno_t Breakpad_SteamSetSteamID(uint64 ulSteamID);
EXPORTMYFUNC void Breakpad_SteamMiniDumpInit(uint32 a, const char* b, const char* c);
EXPORTMYFUNC errno_t Breakpad_SteamWriteMiniDumpSetComment(const char* pchMsg);
EXPORTMYFUNC void Breakpad_SteamWriteMiniDumpUsingExceptionInfoWithBuildId(int a, int b);

// Interface loader
EXPORTMYFUNC void* CreateInterface(const char* interfacename, int32_t* returncode);

// Steam user
EXPORTMYFUNC bool Steam_BConnected(HSteamUser hUser, HSteamPipe hSteamPipe);
EXPORTMYFUNC bool Steam_BLoggedOn(HSteamUser hUser, HSteamPipe hSteamPipe);
EXPORTMYFUNC void Steam_LogOn(HSteamUser hUser, HSteamPipe hSteamPipe, uint64 ulSteamID);
EXPORTMYFUNC void Steam_LogOff(HSteamUser hUser, HSteamPipe hSteamPipe);
EXPORTMYFUNC int Steam_InitiateGameConnection(HSteamUser hUser, HSteamPipe hSteamPipe, void* pBlob, int cbMaxBlob, uint64 steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure);
EXPORTMYFUNC void Steam_TerminateGameConnection(HSteamUser hUser, HSteamPipe hSteamPipe, uint32 unIPServer, uint16 usPortServer);

// Steam callbacks
EXPORTMYFUNC void Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks);
EXPORTMYFUNC void Steam_RegisterInterfaceFuncs(void* hModule);
EXPORTMYFUNC bool Steam_BGetCallback(HSteamPipe hSteamPipe, CallbackMsg_t* pCallbackMsg);
EXPORTMYFUNC void Steam_FreeLastCallback(HSteamPipe hSteamPipe);
EXPORTMYFUNC bool Steam_GetAPICallResult(HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed);

// Steam client
EXPORTMYFUNC HSteamPipe Steam_CreateSteamPipe();
EXPORTMYFUNC bool Steam_BReleaseSteamPipe(HSteamPipe hSteamPipe);
EXPORTMYFUNC HSteamUser Steam_CreateLocalUser(HSteamPipe* phSteamPipe, EAccountType eAccountType);
EXPORTMYFUNC HSteamUser Steam_CreateGlobalUser(HSteamPipe* phSteamPipe);
EXPORTMYFUNC HSteamUser Steam_ConnectToGlobalUser(HSteamPipe hSteamPipe);
EXPORTMYFUNC void Steam_ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser);
EXPORTMYFUNC void Steam_ReleaseThreadLocalMemory(bool Thread);
EXPORTMYFUNC void Steam_SetLocalIPBinding(uint32 unIP, uint16 usLocalPort);

// Steam game server
EXPORTMYFUNC int Steam_GSGetSteamGameConnectToken(HSteamUser hUser, HSteamPipe hSteamPipe, void* pBlob, int cbBlobMax);
EXPORTMYFUNC void* Steam_GetGSHandle(HSteamUser hUser, HSteamPipe hSteamPipe);
EXPORTMYFUNC bool Steam_GSSendSteam2UserConnect(void* phSteamHandle, uint32 unUserID, const void* pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void* pvCookie, uint32 cubCookie);
EXPORTMYFUNC bool Steam_GSSendSteam3UserConnect(void* phSteamHandle, uint64 steamID, uint32 unIPPublic, const void* pvCookie, uint32 cubCookie);
EXPORTMYFUNC bool Steam_GSSendUserDisconnect(void* phSteamHandle, uint64 ulSteamID, uint32 unUserID);
EXPORTMYFUNC bool Steam_GSSendUserStatusResponse(void* phSteamHandle, uint64 ulSteamID, int nSecondsConnected, int nSecondsSinceLast);
EXPORTMYFUNC bool Steam_GSUpdateStatus(void* phSteamHandle, int cPlayers, int cPlayersMax, int cBotPlayers, const char* pchServerName, const char* pchMapName);
EXPORTMYFUNC bool Steam_GSRemoveUserConnect(void* phSteamHandle, uint32 unUserID);
EXPORTMYFUNC void Steam_GSSetSpawnCount(void* phSteamHandle, uint32 ucSpawn);
EXPORTMYFUNC bool Steam_GSGetSteam2GetEncryptionKeyToSendToNewClient(void* phSteamHandle, void* pvEncryptionKey, uint32* pcbEncryptionKey, uint32 cbMaxEncryptionKey);
EXPORTMYFUNC void Steam_GSLogOn(void* phSteamHandle);
EXPORTMYFUNC void Steam_GSLogOff(void* phSteamHandle);
EXPORTMYFUNC bool Steam_GSBLoggedOn(void* phSteamHandle);
EXPORTMYFUNC uint64 Steam_GSGetSteamID();
EXPORTMYFUNC bool Steam_GSSetServerType(void* phSteamHandle, int32 nAppIdServed, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char* pchGameDir, const char* pchVersion);
EXPORTMYFUNC bool Steam_GSBSecure(void* phSteamHandle);