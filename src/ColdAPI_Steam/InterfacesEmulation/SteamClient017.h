#pragma once
#include "../public SDK/ISteamClient017.h"
#include "../Steam_data.h"


class SteamClientIn017 : public ISteamClient017
{
public:
	HSteamPipe CreateSteamPipe()
	{
		return 1;
	}

	bool BReleaseSteamPipe(HSteamPipe hSteamPipe)
	{
		return true;
	}

	HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe)
	{
		return 1;
	}

	HSteamUser CreateLocalUser(HSteamPipe* phSteamPipe, EAccountType eAccountType)
	{
		return 1;
	}

	void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser)
	{
		return;
	}

	// Return interface buffer pointer from our exported interface caller functions.

	ISteamUser* GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamUser*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamGameServer* GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamGameServer*)SteamInternal_CreateInterface(pchVersion);
	}

	void SetLocalIPBinding(uint32 unIP, uint16 usPort)
	{
		return;
	}
	ISteamFriends* GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamFriends*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamUtils *GetISteamUtils(HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamUtils*)SteamInternal_CreateInterface(pchVersion);
	}

	
	ISteamMatchmaking* GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamMatchmaking*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamMatchmakingServers* GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamMatchmakingServers*)SteamInternal_CreateInterface(pchVersion);
	}

	void* GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return SteamInternal_CreateInterface(pchVersion);
	}

	ISteamUserStats* GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamUserStats*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamGameServerStats* GetISteamGameServerStats(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamGameServerStats*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamApps* GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamApps*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamNetworking* GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamNetworking*)SteamInternal_CreateInterface(pchVersion);
	}

	
	ISteamRemoteStorage* GetISteamRemoteStorage(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamRemoteStorage*)SteamInternal_CreateInterface(pchVersion);
	}

	
	ISteamScreenshots* GetISteamScreenshots(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamScreenshots*)SteamInternal_CreateInterface(pchVersion);
	}

	void RunFrame()
	{
		return;
	}

	uint32 GetIPCCallCount()
	{
		return NULL;
	}

	void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
	{
		return;
	}

	bool BShutdownIfAllPipesClosed()
	{
		return true;
	}

	ISteamHTTP* GetISteamHTTP(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamHTTP*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamUnifiedMessages* GetISteamUnifiedMessages(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamUnifiedMessages*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamController* GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamController*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamUGC* GetISteamUGC(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamUGC*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamAppList* GetISteamAppList(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamAppList*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamMusic* GetISteamMusic(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamMusic*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamMusicRemote* GetISteamMusicRemote(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamMusicRemote*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamHTMLSurface* GetISteamHTMLSurface(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamHTMLSurface*)SteamInternal_CreateInterface(pchVersion);
	}

	// Some functions are not needed to play offline.

	void Set_SteamAPI_CPostAPIResultInProcess(void(*)(SteamAPICall_t callHandle, void*, uint32 unCallbackSize, int iCallbackNum))
	{
		return;		
	}
	void Remove_SteamAPI_CPostAPIResultInProcess(void(*)(SteamAPICall_t callHandle, void*, uint32 unCallbackSize, int iCallbackNum))
	{
		return;
	}
	void Set_SteamAPI_CCheckCallbackRegisteredInProcess(unsigned int(*)(int iCallbackNum))
	{
		return;
	}

	ISteamInventory* GetISteamInventory(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamInventory*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamVideo* GetISteamVideo(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamVideo*)SteamInternal_CreateInterface(pchVersion);
	}
	void* GetISteamParentalSettings(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return SteamInternal_CreateInterface(pchVersion);
	}
};