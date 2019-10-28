#pragma once
#include "../public SDK/ISteamMatchmakingServers001.h"
#include "../Bridge.h"


class SteamMatchmakingServersIn001 : public ISteamMatchmakingServers001
{
public:
	void RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001* pRequestServersResponse)
	{
		return;
	}
	void RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse001* pRequestServersResponse)
	{
		return;
	}
	void RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001* pRequestServersResponse)
	{
		return;
	}
	void RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001* pRequestServersResponse)
	{
		return;
	}
	void RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001* pRequestServersResponse)
	{
		return;
	}
	void RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001* pRequestServersResponse)
	{
		return;
	}

	gameserveritem_t* GetServerDetails(EMatchMakingType eType, int iServer)
	{
		return nullptr;
	}

	void CancelQuery(EMatchMakingType eType)
	{
		return;
	}

	void RefreshQuery(EMatchMakingType eType)
	{
		return;
	}

	bool IsRefreshing(EMatchMakingType eType)
	{
		return false;
	}

	int GetServerCount(EMatchMakingType eType)
	{
		return NULL;
	}

	void RefreshServer(EMatchMakingType eType, int iServer)
	{
		return;
	}


	int32_t PingServer(uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse* pRequestServersResponse)
	{
		return NULL;
	}

	int32_t PlayerDetails(uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse* pRequestServersResponse)
	{
		return NULL;
	}

	int32_t ServerRules(uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse* pRequestServersResponse)
	{
		return NULL;
	}

	void CancelServerQuery(int32_t hServerQuery)
	{
		return;
	}
};
