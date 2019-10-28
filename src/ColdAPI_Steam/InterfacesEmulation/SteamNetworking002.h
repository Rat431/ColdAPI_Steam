#pragma once
#include "../public SDK/ISteamNetworking002.h"
#include "../Bridge.h"


class SteamNetworkingIn002 : public ISteamNetworking002
{
public:
	SNetListenSocket_t CreateListenSocket(int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
	{
		return NULL;
	}

	SNetSocket_t CreateP2PConnectionSocket(CSteamID steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay)
	{
		return NULL;
	}
	SNetSocket_t CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec)
	{
		return NULL;
	}

	bool DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd)
	{
		return false;
	}
	bool DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd)
	{
		return false;
	}

	bool SendDataOnSocket(SNetSocket_t hSocket, void* pubData, uint32 cubData, bool bReliable)
	{
		return false;
	}

	bool IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32* pcubMsgSize)
	{
		return false;
	}

	bool RetrieveDataFromSocket(SNetSocket_t hSocket, void* pubDest, uint32 cubDest, uint32* pcubMsgSize)
	{
		return false;
	}

	bool IsDataAvailable(SNetListenSocket_t hListenSocket, uint32* pcubMsgSize, SNetSocket_t* phSocket)
	{
		return false;
	}

	bool RetrieveData(SNetListenSocket_t hListenSocket, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, SNetSocket_t* phSocket)
	{
		return false;
	}

	bool GetSocketInfo(SNetSocket_t hSocket, CSteamID* pSteamIDRemote, int* peSocketStatus, uint32* punIPRemote, uint16* punPortRemote)
	{
		return false;
	}

	bool GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32* pnIP, uint16* pnPort)
	{
		return false;
	}

	ESNetSocketConnectionType GetSocketConnectionType(SNetSocket_t hSocket)
	{
		return k_ESNetSocketConnectionTypeNotConnected;
	}

	int GetMaxPacketSize(SNetSocket_t hSocket)
	{
		return NULL;
	}
};
