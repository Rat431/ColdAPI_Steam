#include "Steam_data.h"
#include "Bridge.h"
// Steam standard functions.
EXPORTMYFUNC bool SteamAPI_Init()
{
	return ColdAPI_InitAndShutDown::ColdClientInitializzation();
}
EXPORTMYFUNC bool SteamAPI_InitSafe()
{
	return SteamAPI_Init();
}
EXPORTMYFUNC void SteamAPI_Shutdown()
{
	ColdAPI_InitAndShutDown::ColdClientShutDown();
}
EXPORTMYFUNC bool SteamAPI_IsSteamRunning()
{
	return true;
}
EXPORTMYFUNC const char* SteamAPI_GetSteamInstallPath()
{
	return ColdAPI_General::ColdAPI_GetSteamInstallPath();
}
EXPORTMYFUNC bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID)
{
	Steam_Config::AppId = unOwnAppID;
	return false;
}

// SteamCustom attempt.
EXPORTMYFUNC void SteamAPI_ReleaseCurrentThreadMemory()
{
	return;
}
EXPORTMYFUNC void Steam_RegisterInterfaceFuncs(void* hModule)
{
	return;
}

// SteamMiniDump Attempt.
EXPORTMYFUNC void SteamAPI_SetMiniDumpComment(const char* pchMsg)
{
	return;
}
EXPORTMYFUNC void SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID)
{
	// A bit useless, implement it if you need.
	return;
}

// SteamInternal attempt.
EXPORTMYFUNC void* SteamInternal_CreateInterface(const char* interfacename)
{
	return ColdAPI_General::ProvideInterface(NULL, interfacename, true);
}
EXPORTMYFUNC void* SteamInternal_FindOrCreateUserInterface(int32_t hSteamUser, const char* pszVersion)
{
	return SteamInternal_CreateInterface(pszVersion);
}
EXPORTMYFUNC void* SteamInternal_FindOrCreateGameServerInterface(int32_t hSteamUser, const char* pszVersion)
{
	return SteamInternal_CreateInterface(pszVersion);
}
EXPORTMYFUNC void* SteamInternal_ContextInit(void* pContextInitData)
{
	return ColdAPI_General::ContextInitializzation(pContextInitData);
}

// SteamAccessors attempt.
EXPORTMYFUNC void* SteamApps()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_APPS, NULL, false);
}
EXPORTMYFUNC void* SteamClient()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_CLIENT, NULL, false);
}
EXPORTMYFUNC void* SteamController()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_CONTROLLER, NULL, false);
}
EXPORTMYFUNC void* SteamBilling()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_BILLING, NULL, false);
}
EXPORTMYFUNC void* SteamContentServer()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_CONTENTSERVER, NULL, false);
}
EXPORTMYFUNC void* SteamFriends()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_FRIENDS, NULL, false);
}
EXPORTMYFUNC void* SteamParentalSettings()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_PARENTALSETTINGS, NULL, false);
}
EXPORTMYFUNC void* SteamGameSearch()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESEARCH, NULL, false);
}
EXPORTMYFUNC void* SteamInput()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_INPUT, NULL, false);
}
EXPORTMYFUNC void* SteamParties()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_PARTIES, NULL, false);
}
EXPORTMYFUNC void* SteamGameServer()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVER, NULL, false);
}
EXPORTMYFUNC void* SteamGameServerHTTP()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVERHTTP, NULL, false);
}
EXPORTMYFUNC void* SteamGameCoordinator()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMECOORDINATOR, NULL, false);
}
EXPORTMYFUNC void* SteamGameServerInventory()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVERINVENTORY, NULL, false);
}
EXPORTMYFUNC void* SteamGameServerNetworking()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVERNETWORKING, NULL, false);
}
EXPORTMYFUNC void* SteamGameServerStats()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVERSTATS, NULL, false);
}
EXPORTMYFUNC void* SteamGameServerUGC()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVERUGC, NULL, false);
}
EXPORTMYFUNC void* SteamGameServerUtils()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_GAMESERVERUTILS, NULL, false);
}
EXPORTMYFUNC void* SteamHTMLSurface()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_HTMLSURFACE, NULL, false);
}
EXPORTMYFUNC void* SteamAppList()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_APPLIST, NULL, false);
}
EXPORTMYFUNC void* SteamHTTP()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_HTTP, NULL, false);
}
EXPORTMYFUNC void* SteamInventory()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_INVENTORY, NULL, false);
}
EXPORTMYFUNC void* SteamMatchmaking()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_MATCHMAKING, NULL, false);
}
EXPORTMYFUNC void* SteamMatchmakingServers()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_MATCHMAKINGSERVERS, NULL, false);
}
EXPORTMYFUNC void* SteamMusic()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_MUSIC, NULL, false);
}
EXPORTMYFUNC void* SteamMusicRemote()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_MUSICREMOTE, NULL, false);
}
EXPORTMYFUNC void* SteamNetworking()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_NETWORKING, NULL, false);
}
EXPORTMYFUNC void* SteamRemoteStorage()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_REMOTESTORAGE, NULL, false);
}
EXPORTMYFUNC void* SteamScreenshots()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_SCREENSHOTS, NULL, false);
}
EXPORTMYFUNC void* SteamUnifiedMessages()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_UNIFIEDMESSAGES, NULL, false);
}
EXPORTMYFUNC void* SteamUGC()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_UGC, NULL, false);
}
EXPORTMYFUNC void* SteamUser()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_USER, NULL, false);
}
EXPORTMYFUNC void* SteamUserStats()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_USERSTATS, NULL, false);
}
EXPORTMYFUNC void* SteamUtils()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_UTILS, NULL, false);
}
EXPORTMYFUNC void* SteamVideo()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_VIDEO, NULL, false);
}
EXPORTMYFUNC void* SteamMasterServerUpdater()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_MASTERSERVERUPDATER, NULL, false);
}
EXPORTMYFUNC void* SteamRemotePlay()
{
	return ColdAPI_General::ProvideInterface(CSteamInterface::STEAM_REMOTEPLAY, NULL, false);
}
// SteamHandlers attempt.
EXPORTMYFUNC int32_t GetHSteamUser()
{
	return 1;
}
EXPORTMYFUNC int32_t GetHSteamPipe()
{
	return 1;
}
EXPORTMYFUNC int32_t SteamAPI_GetHSteamUser()
{
	return 1;
}
EXPORTMYFUNC int32_t SteamAPI_GetHSteamPipe()
{
	return 1;
}
EXPORTMYFUNC int32_t SteamGameServer_GetHSteamUser()
{
	return 1;
}
EXPORTMYFUNC int32_t SteamGameServer_GetHSteamPipe()
{
	return 1;
}
EXPORTMYFUNC int32_t Steam_GetHSteamUserCurrent()
{
	return 1;
}

// SteamCallBacks attempt.
EXPORTMYFUNC void SteamAPI_RunCallbacks()
{
	SteamCallback::RunCallbacks();
}
EXPORTMYFUNC void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks)
{
	return;
}
EXPORTMYFUNC void SteamAPI_RegisterCallback(void* pCallback, int iCallback)
{
	if(pCallback)
		SteamCallback::RegisterCallback((CCallbackBase*)pCallback, iCallback);
}
EXPORTMYFUNC void SteamAPI_UnregisterCallback(void* pCallback, int iCallback)
{
	if (pCallback)
		SteamCallback::UnregisterCallback((CCallbackBase*)pCallback, iCallback);
}
EXPORTMYFUNC void SteamAPI_RegisterCallResult(void* pCallback, uint64_t hAPICall)
{
	if (pCallback)
		SteamCallback::RegisterCallResult((CCallbackBase*)pCallback, hAPICall);
}
EXPORTMYFUNC void SteamAPI_UnregisterCallResult(void* pCallback, uint64_t hAPICall)
{
	if (pCallback)
		SteamCallback::UnregisterCallResult((CCallbackBase*)pCallback, hAPICall);
}
EXPORTMYFUNC bool SteamGameServer_BSecure()
{
	return true;
}
EXPORTMYFUNC void SteamGameServer_Shutdown()
{
	return;
}
EXPORTMYFUNC void SteamGameServer_RunCallbacks()
{
	return;
}

// SteamServer attempt.
EXPORTMYFUNC uint64_t SteamGameServer_GetSteamID()
{
	return Steam_Config::UserID;
}

EXPORTMYFUNC bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char* pchVersionString)
{
	return true;
}
EXPORTMYFUNC bool SteamGameServer_InitSafe(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char* pchVersionString)
{
	return true;
}
EXPORTMYFUNC bool SteamInternal_GameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char* pchVersionString)
{
	return true;
}