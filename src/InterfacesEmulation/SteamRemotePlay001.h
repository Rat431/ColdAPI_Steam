#pragma once
#include "../public SDK/ISteamRemotePlay001.h"
#include "../Bridge.h"

class SteamRemotePlayIn001 : public ISteamRemotePlay001
{
public:
	uint32 GetSessionCount()
	{
		return NULL;
	}

	uint32 GetSessionID(int iSessionIndex)
	{
		return NULL;
	}

	CSteamID GetSessionSteamID(uint32 unSessionID)
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}

	const char* GetSessionClientName(uint32 unSessionID)
	{
		return NULL;
	}

	ESteamDeviceFormFactor GetSessionClientFormFactor(uint32 unSessionID)
	{
		return k_ESteamDeviceFormFactorUnknown;
	}

	bool BGetSessionClientResolution(uint32 unSessionID, int* pnResolutionX, int* pnResolutionY)
	{
		return false;
	}
};