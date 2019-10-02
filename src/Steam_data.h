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
EXPORTMYFUNC void Steam_RegisterInterfaceFuncs(void* hModule);

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