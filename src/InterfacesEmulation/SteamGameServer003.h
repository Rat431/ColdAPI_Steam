#pragma once
#include "../public SDK/ISteamGameServer003.h"
#include "../Bridge.h"


class SteamGameServerIn003 : public ISteamGameServer003
{
public:
	void LogOn()
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
		return true; // <---- :D
	}
	CSteamID GetSteamID()
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}

	bool GetSteam2GetEncryptionKeyToSendToNewClient(void* pvEncryptionKey, uint32* pcbEncryptionKey, uint32 cbMaxEncryptionKey)
	{
		return false;
	}

	bool SendUserConnect(uint32, uint32, uint16, const void*, uint32)
	{
		return false;
	}

	bool RemoveUserConnect(uint32 unUserID)
	{
		return false;
	}

	bool SendUserDisconnect(CSteamID steamID, uint32 unUserID)
	{
		return false;
	}

	void SetSpawnCount(uint32 ucSpawn)
	{
		return;
	}

	bool SetServerType(int32 nGameAppId, uint32 unServerFlags, uint32 unGameIP, uint16 unGamePort, uint16 usSpectatorPort, uint16 usQueryPort, const char* pchGameDir, const char* pchVersion, bool bLANMode)
	{
		return false;
	}

	bool UpdateStatus(int cPlayers, int cPlayersMax, int cBotPlayers, const char* pchServerName, const char* pSpectatorServerName, const char* pchMapName)
	{
		return false;
	}

	bool CreateUnauthenticatedUser(CSteamID* pSteamID)
	{
		return false;
	}

	bool SetUserData(CSteamID steamIDUser, const char* pchPlayerName, uint32 uScore)
	{
		return true;
	}

	void UpdateSpectatorPort(uint16 unSpectatorPort)
	{
		return;
	}

	void SetGameType(const char* pchGameType)
	{
		return;
	}

	bool GetUserAchievementStatus(CSteamID steamID, const char* pchAchievementName)
	{
		return false;
	}
};
