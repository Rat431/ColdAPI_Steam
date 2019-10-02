#pragma once
#include "../public SDK/ISteamContentServer001.h"
#include "../Bridge.h"

class SteamContentServerIn001 : public ISteamContentServer001
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

	void SendClientContentAuthRequest(CSteamID steamID, uint32 unContentID)
	{
		return;
	}
};
