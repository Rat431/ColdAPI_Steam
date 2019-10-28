#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUser010.h"


class SteamUserIn010 : public ISteamUser010
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

	int InitiateGameConnection(void* pBlob, int cbMaxBlob, CSteamID steamID, uint32 unIPServer, uint16 usPortServer, bool bSecure)
	{
		return cbMaxBlob;
	}

	void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	void TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char* pchExtraInfo = "")
	{
		return;
	}
};