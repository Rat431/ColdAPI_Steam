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


EXPORTMYFUNC errno_t Breakpad_SetSteamID(uint64 ulSteamID)
{
	return NULL;
}
EXPORTMYFUNC errno_t Breakpad_SteamSetSteamID(uint64 ulSteamID)
{
	return NULL;
}
EXPORTMYFUNC void Breakpad_SteamMiniDumpInit(uint32 a, const char* b, const char* c)
{
	return;
}
EXPORTMYFUNC errno_t Breakpad_SteamWriteMiniDumpSetComment(const char* pchMsg)
{
	// Pretty useless
	return NULL;
}
EXPORTMYFUNC void Breakpad_SteamWriteMiniDumpUsingExceptionInfoWithBuildId(int a, int b)
{
	return;
}

// Interface loader
EXPORTMYFUNC void* CreateInterface(const char* interfacename, int32_t* returncode)
{
	// Just same as SteamInternal_CreateInterface
	void* InterfaceL = ColdAPI_General::ProvideInterface(NULL, interfacename, true);
	if (returncode > NULL)
		*returncode = 1;
	return InterfaceL;
}

// Steam user
EXPORTMYFUNC bool Steam_BConnected(HSteamUser hUser, HSteamPipe hSteamPipe)
{
	return true;
}
EXPORTMYFUNC bool Steam_BLoggedOn(HSteamUser hUser, HSteamPipe hSteamPipe)
{
	return true;
}
EXPORTMYFUNC void Steam_LogOn(HSteamUser hUser, HSteamPipe hSteamPipe, uint64 ulSteamID)
{
	return;
}
EXPORTMYFUNC void Steam_LogOff(HSteamUser hUser, HSteamPipe hSteamPipe)
{
	return;
}
EXPORTMYFUNC int Steam_InitiateGameConnection(HSteamUser hUser, HSteamPipe hSteamPipe, void* pBlob, int cbMaxBlob, uint64 steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
	return NULL;
}
EXPORTMYFUNC void Steam_TerminateGameConnection(HSteamUser hUser, HSteamPipe hSteamPipe, uint32 unIPServer, uint16 usPortServer)
{
	return;
}

// Steam callbacks
EXPORTMYFUNC void Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks)
{
	if (!Steam_Config::ClientEmulation)
		SteamCallback::RunCallbacks();
}
EXPORTMYFUNC void Steam_RegisterInterfaceFuncs(void* hModule)
{
	return;
}
EXPORTMYFUNC bool Steam_BGetCallback(HSteamPipe hSteamPipe, CallbackMsg_t* pCallbackMsg)
{
	return SteamCallback::CCGetCallBack(pCallbackMsg);
}
EXPORTMYFUNC void Steam_FreeLastCallback(HSteamPipe hSteamPipe)
{
	SteamCallback::FreeCB();
}
EXPORTMYFUNC bool Steam_GetAPICallResult(HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
{
	return SteamCallback::CCGetAPICallResult(hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
}

// Steam client
EXPORTMYFUNC HSteamPipe Steam_CreateSteamPipe()
{
	return 1;
}
EXPORTMYFUNC bool Steam_BReleaseSteamPipe(HSteamPipe hSteamPipe)
{
	return true;
}
EXPORTMYFUNC HSteamUser Steam_CreateLocalUser(HSteamPipe* phSteamPipe, EAccountType eAccountType)
{
	return 1;
}
EXPORTMYFUNC HSteamUser Steam_CreateGlobalUser(HSteamPipe* phSteamPipe)
{
	return 1;
}
EXPORTMYFUNC HSteamUser Steam_ConnectToGlobalUser(HSteamPipe hSteamPipe)
{
	return 1;
}
EXPORTMYFUNC void Steam_ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser)
{
	return;
}
EXPORTMYFUNC void Steam_ReleaseThreadLocalMemory(bool Thread)
{
	return;
}
EXPORTMYFUNC void Steam_SetLocalIPBinding(uint32 unIP, uint16 usLocalPort)
{
	return;
}

// Steam game server
EXPORTMYFUNC int Steam_GSGetSteamGameConnectToken(HSteamUser hUser, HSteamPipe hSteamPipe, void* pBlob, int cbBlobMax)
{
	return NULL;
}
EXPORTMYFUNC void* Steam_GetGSHandle(HSteamUser hUser, HSteamPipe hSteamPipe)
{
	return nullptr;
}
EXPORTMYFUNC bool Steam_GSSendSteam2UserConnect(void* phSteamHandle, uint32 unUserID, const void* pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void* pvCookie, uint32 cubCookie)
{
	return true;
}
EXPORTMYFUNC bool Steam_GSSendSteam3UserConnect(void* phSteamHandle, uint64 steamID, uint32 unIPPublic, const void* pvCookie, uint32 cubCookie)
{
	return true;
}
EXPORTMYFUNC bool Steam_GSSendUserDisconnect(void* phSteamHandle, uint64 ulSteamID, uint32 unUserID)
{
	return true;
}
EXPORTMYFUNC bool Steam_GSSendUserStatusResponse(void* phSteamHandle, uint64 ulSteamID, int nSecondsConnected, int nSecondsSinceLast)
{
	return true;
}
EXPORTMYFUNC bool Steam_GSUpdateStatus(void* phSteamHandle, int cPlayers, int cPlayersMax, int cBotPlayers, const char* pchServerName, const char* pchMapName)
{
	return true;
}
EXPORTMYFUNC bool Steam_GSRemoveUserConnect(void* phSteamHandle, uint32 unUserID)
{
	return true;
}
EXPORTMYFUNC void Steam_GSSetSpawnCount(void* phSteamHandle, uint32 ucSpawn)
{
	return;
}
EXPORTMYFUNC bool Steam_GSGetSteam2GetEncryptionKeyToSendToNewClient(void* phSteamHandle, void* pvEncryptionKey, uint32* pcbEncryptionKey, uint32 cbMaxEncryptionKey)
{
	return false;
}
EXPORTMYFUNC void Steam_GSLogOn(void* phSteamHandle)
{
	return;
}
EXPORTMYFUNC void Steam_GSLogOff(void* phSteamHandle)
{
	return;
}
EXPORTMYFUNC bool Steam_GSBLoggedOn(void* phSteamHandle)
{
	return true;
}
EXPORTMYFUNC uint64 Steam_GSGetSteamID()
{
	return Steam_Config::UserID;
}
EXPORTMYFUNC bool Steam_GSSetServerType(void* phSteamHandle, int32 nAppIdServed, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char* pchGameDir, const char* pchVersion)
{
	return false;
}
EXPORTMYFUNC bool Steam_GSBSecure(void* phSteamHandle)
{
	return true;
}