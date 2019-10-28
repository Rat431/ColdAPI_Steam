#pragma once
#include "../public SDK/ISteamClient010.h"
#include "../Steam_data.h"


class SteamClientIn010 : public ISteamClient010
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

	ISteamUtils* GetISteamUtils(HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamUtils*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamMatchmaking* GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamMatchmaking*)SteamInternal_CreateInterface(pchVersion);
	}

	ISteamMasterServerUpdater* GetISteamMasterServerUpdater(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
	{
		return (ISteamMasterServerUpdater*)SteamInternal_CreateInterface(pchVersion);
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

	ISteamGameServerStats* GetISteamGameServerStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
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
};
