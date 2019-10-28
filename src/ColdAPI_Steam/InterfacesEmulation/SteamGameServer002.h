#pragma once
#include "../public SDK/ISteamGameServer002.h"
#include "../Bridge.h"


class SteamGameServerIn002 : public ISteamGameServer002
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

	void SetSpawnCount(uint32 ucSpawn)
	{
		return;
	}

	bool GetSteam2GetEncryptionKeyToSendToNewClient(void* pvEncryptionKey, uint32* pcbEncryptionKey, uint32 cbMaxEncryptionKey)
	{
		return false;
	}

	bool SendSteam2UserConnect(uint32 unUserID, const void* pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void* pvCookie, uint32 cubCookie)
	{
		return false;
	}

	bool SendSteam3UserConnect(CSteamID steamID, uint32 unIPPublic, const void* pvCookie, uint32 cubCookie)
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

	bool SendUserStatusResponse(CSteamID steamID, int nSecondsConnected, int nSecondsSinceLast)
	{
		return false;
	}

	bool Obsolete_GSSetStatus(int32 nAppIdServed, uint32 unServerFlags, int cPlayers, int cPlayersMax, int cBotPlayers, int unGamePort, const char* pchServerName, const char* pchGameDir, const char* pchMapName, const char* pchVersion)
	{
		return false;
	}

	bool UpdateStatus(int cPlayers, int cPlayersMax, int cBotPlayers, const char* pchServerName, const char* pchMapName)
	{
		return false;
	}

	bool BSecure()
	{
		return true; // <----- :D
	}
	CSteamID GetSteamID()
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}

	bool SetServerType(int32 nGameAppId, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char* pchGameDir, const char* pchVersion)
	{
		return false;
	}

	bool SetServerType2(int32 nGameAppId, uint32 unServerFlags, uint32 unGameIP, uint16 unGamePort, uint16 usSpectatorPort, uint16 usQueryPort, const char* pchGameDir, const char* pchVersion, bool bLANMode)
	{
		return false;
	}

	bool UpdateStatus2(int cPlayers, int cPlayersMax, int cBotPlayers, const char* pchServerName, const char* pSpectatorServerName, const char* pchMapName)
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
};
