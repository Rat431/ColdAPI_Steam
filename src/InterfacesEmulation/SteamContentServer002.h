#pragma once
#include "../public SDK/ISteamContentServer002.h"
#include "../Bridge.h"


class SteamContentServerIn002 : public ISteamContentServer002
{
public:
	bool LogOn(uint32 uContentServerID)
	{
		return true;
	}
	bool LogOff()
	{
		return true;
	}

	bool BLoggedOn()
	{
		return Steam_Config::OnlineMod;
	}

	void SendClientContentAuthRequest(CSteamID steamID, uint32 uContentID, uint64 ulSessionToken, bool bTokenPresent)
	{
		return;
	}

	bool BCheckTicket(CSteamID steamID, uint32 uContentID, const void* pvTicketData, uint32 cubTicketLength)
	{
		return true;
	}
};
