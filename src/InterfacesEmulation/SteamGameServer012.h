#pragma once
#include "../public SDK/ISteamGameServer012.h"
#include "../Bridge.h"


class SteamGameServerIn012 : public ISteamGameServer012
{
public:
	bool InitGameServer(uint32 unGameIP, uint16 unGamePort, uint16 usQueryPort, uint32 unServerFlags, AppId_t nAppID, const char* pchVersion)
	{
		return true;
	}

	void SetProduct(const char* pchProductName)
	{
		return;
	}

	void SetGameDescription(const char* pchGameDescription)
	{
		return;
	}

	void SetModDir(const char* pchModDir)
	{
		return;
	}

	void SetDedicatedServer(bool bDedicatedServer)
	{
		return;
	}

	void LogOn(const char* pszUnk)
	{
		{
			SteamServersConnected_t* Response = (SteamServersConnected_t*)malloc(sizeof(SteamServersConnected_t));
			auto RequestID = SteamCallback::RegisterCall(true);
			SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
		}

		{
			GSPolicyResponse_t* Response = (GSPolicyResponse_t*)malloc(sizeof(GSPolicyResponse_t));
			auto RequestID = SteamCallback::RegisterCall(true);

			Response->m_bSecure = false;
			SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
		}
	}

	void LogOnAnonymous()
	{
		{
			SteamServersConnected_t* Response = (SteamServersConnected_t*)malloc(sizeof(SteamServersConnected_t));
			auto RequestID = SteamCallback::RegisterCall(true);
			SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
		}

		{
			GSPolicyResponse_t* Response = (GSPolicyResponse_t*)malloc(sizeof(GSPolicyResponse_t));
			auto RequestID = SteamCallback::RegisterCall(true);

			Response->m_bSecure = false;
			SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
		}
	}

	void LogOff()
	{
		return;
	}

	bool BLoggedOn()
	{
		return Steam_Config::OnlineMod;
	}
	bool BSecure()
	{
		return true;
	}
	CSteamID GetSteamID()
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}

	bool WasRestartRequested()
	{
		return false;
	}

	void SetMaxPlayerCount(int cPlayersMax)
	{
		return;
	}


	void SetBotPlayerCount(int cBotPlayers)
	{
		return;
	}

	void SetServerName(const char* pszServerName)
	{
		return;
	}

	void SetMapName(const char* pszMapName)
	{
		return;
	}

	void SetPasswordProtected(bool bPasswordProtected)
	{
		return;
	}

	void SetSpectatorPort(uint16 unSpectatorPort)
	{
		return;
	}

	void SetSpectatorServerName(const char* pszSpectatorServerName)
	{
		return;
	}

	void ClearAllKeyValues()
	{
		return;
	}

	void SetKeyValue(const char* pKey, const char* pValue)
	{
		return;
	}

	void SetGameTags(const char* pchGameTags)
	{
		return;
	}

	void SetGameData(const char* pchGameData)
	{
		return;
	}

	void SetRegion(const char* pchRegionName)
	{
		return;
	}

	bool SendUserConnectAndAuthenticate(uint32 unIPClient, const void* pvAuthBlob, uint32 cubAuthBlobSize, CSteamID* pSteamIDUser)
	{
		return false;
	}

	CSteamID CreateUnauthenticatedUserConnection()
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}

	void SendUserDisconnect(CSteamID steamIDUser)
	{
		return;
	}

	bool BUpdateUserData(CSteamID steamIDUser, const char* pchPlayerName, uint32 uScore)
	{
		return false;
	}

	HAuthTicket GetAuthSessionTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket)
	{
		return NULL;
	}

	uint32_t BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, CSteamID steamID)
	{
		return NULL;
	}

	void EndAuthSession(CSteamID steamID)
	{
		return;
	}

	void CancelAuthTicket(HAuthTicket hAuthTicket)
	{
		return;
	}

	uint32_t UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
	{
		return NULL;
	}

	bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup)
	{
		return false;
	}

	void GetGameplayStats()
	{
		return;
	}

	SteamAPICall_t GetServerReputation()
	{
		return NULL;
	}

	uint32 GetPublicIP()
	{
		return NULL;
	}

	bool HandleIncomingPacket(const void* pData, int cbData, uint32 srcIP, uint16 srcPort)
	{
		return true;
	}

	int GetNextOutgoingPacket(void* pOut, int cbMaxOut, uint32* pNetAdr, uint16* pPort)
	{
		return NULL;
	}

	void EnableHeartbeats(bool bActive)
	{
		return;
	}

	void SetHeartbeatInterval(int iHeartbeatInterval)
	{
		return;
	}

	void ForceHeartbeat()
	{
		return;
	}

	SteamAPICall_t AssociateWithClan(CSteamID clanID)
	{
		return NULL;
	}

	SteamAPICall_t ComputeNewPlayerCompatibility(CSteamID steamID)
	{
		return NULL;
	}
};
