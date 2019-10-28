#pragma once
#include "../public SDK/ISteamGameServer008.h"
#include "../Bridge.h"


class SteamGameServerIn008 : public ISteamGameServer008
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

	bool BSetServerType(uint32 unServerFlags, uint32 unGameIP, uint16 unGamePort, uint16 unSpectatorPort, uint16 usQueryPort, const char* pchGameDir, const char* pchVersion, bool bLANMode)
	{
		return false;
	}

	void UpdateServerStatus(int cPlayers, int cPlayersMax, int cBotPlayers, const char* pchServerName, const char* pSpectatorServerName, const char* pchMapName)
	{
		return;
	}

	void UpdateSpectatorPort(uint16 unSpectatorPort)
	{
		return;
	}

	void SetGameType(const char* pchGameType)
	{
		return;
	}

	bool BGetUserAchievementStatus(CSteamID steamID, const char* pchAchievementName)
	{
		return false;
	}

	void GetGameplayStats()
	{
		return;
	}

	bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup)
	{
		return false;
	}

	uint32 GetPublicIP()
	{
		return NULL;
	}
};
