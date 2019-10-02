#pragma once
#include "../public SDK/ISteamMatchmakingServers002.h"
#include "../Bridge.h"


class SteamMatchmakingServersIn002 : public ISteamMatchmakingServers002
{
public:
	HServerListRequest RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse)
	{
		return NULL;
	}
	HServerListRequest RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse* pRequestServersResponse)
	{
		return NULL;
	}
	HServerListRequest RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse)
	{
		return NULL;
	}
	HServerListRequest RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse)
	{
		return NULL;
	}
	HServerListRequest RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse)
	{
		return NULL;
	}
	HServerListRequest RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse)
	{
		return NULL;
	}

	void ReleaseRequest(HServerListRequest hServerListRequest)
	{
		return;
	}

	gameserveritem_t* GetServerDetails(HServerListRequest hRequest, int iServer)
	{
		return NULL;
	}

	void CancelQuery(HServerListRequest hRequest)
	{
		return;
	}

	void RefreshQuery(HServerListRequest hRequest)
	{
		return;
	}

	bool IsRefreshing(HServerListRequest hRequest)
	{
		return false;
	}

	int GetServerCount(HServerListRequest hRequest)
	{
		return NULL;
	}

	void RefreshServer(HServerListRequest hRequest, int iServer)
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
