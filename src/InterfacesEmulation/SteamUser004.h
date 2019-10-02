#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUser004.h"


class SteamUserIn004 : public ISteamUser004
{
public:
	HSteamUser GetHSteamUser()
	{
		return NULL;
	}

	void LogOn(CSteamID steamID)
	{
		return;
	}
	void LogOff()
	{
		return;
	}

	bool BLoggedOn()
	{
		return Steam_Config::OnlineMod;
	}

	ELogonState GetLogonState()
	{
		return k_ELogonStateLoggedOn;
	}
	bool BConnected()
	{
		return Steam_Config::OnlineMod;
	}

	CSteamID GetSteamID()
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}

	bool IsVACBanned(EVACBan eVACBan)
	{
		return false;
	}

	bool RequireShowVACBannedMessage(EVACBan eVACBan)
	{
		return false;
	}

	void AcknowledgeVACBanning(EVACBan eVACBan)
	{
		return;
	}

	OBSOLETE_FUNCTION int NClientGameIDAdd(int nGameID)
	{
		return NULL;
	}
	OBSOLETE_FUNCTION void RemoveClientGame(int nClientGameID)
	{
		return;
	}
	OBSOLETE_FUNCTION void SetClientGameServer(int nClientGameID, uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	void SetSteam2Ticket(uint8* pubTicket, int cubTicket)
	{
		return;
	}
	OBSOLETE_FUNCTION void AddServerNetAddress(uint32 unIP, uint16 unPort)
	{
		return;
	}

	bool SetEmail(const char* pchEmail)
	{
		return true;
	}

	OBSOLETE_FUNCTION int GetSteamGameConnectToken(void* pBlob, int cbMaxBlob)
	{
		return NULL;
	}

	bool SetRegistryString(ERegistrySubTree eRegistrySubTree, const char* pchKey, const char* pchValue)
	{
		return false;
	}
	bool GetRegistryString(ERegistrySubTree eRegistrySubTree, const char* pchKey, char* pchValue, int cbValue)
	{
		return false;
	}
	bool SetRegistryInt(ERegistrySubTree eRegistrySubTree, const char* pchKey, int iValue)
	{
		return false;
	}
	bool GetRegistryInt(ERegistrySubTree eRegistrySubTree, const char* pchKey, int* piValue)
	{
		return false;
	}

	int InitiateGameConnection(void* pBlob, int cbMaxBlob, CSteamID steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure)
	{
		return cbMaxBlob;
	}

	void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	void SetSelfAsPrimaryChatDestination()
	{
		return;
	}
	bool IsPrimaryChatDestination()
	{
		return true;
	}

	void RequestLegacyCDKey(AppId_t iAppID)
	{
		return;
	}
};
