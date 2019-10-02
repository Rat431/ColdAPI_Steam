#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUser008.h"


class SteamUserIn008 : public ISteamUser008
{
public:
	HSteamUser GetHSteamUser()
	{
		return NULL;
	}

	bool BLoggedOn()
	{
		return Steam_Config::OnlineMod;
	}

	CSteamID GetSteamID()
	{
		return CSteamID(Steam_Config::UserID);
	}

	int InitiateGameConnection(void* pBlob, int cbMaxBlob, CSteamID steamID, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure, void* pvSteam2GetEncryptionKey, int cbSteam2GetEncryptionKey)
	{
		return cbMaxBlob;
	}

	void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	void TrackAppUsageEvent(CGameID gameID, EAppUsageEvent eAppUsageEvent, const char* pchExtraInfo = "")
	{
		return;
	}

	void RefreshSteam2Login()
	{
		return;
	}
};