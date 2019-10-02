#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUtils001.h"

class SteamUtilsIn001 : public ISteamUtils001
{
public:
	uint32 GetSecondsSinceAppActive()
	{
		return NULL;
	}
	uint32 GetSecondsSinceComputerActive()
	{
		return 10;
	}

	EUniverse GetConnectedUniverse()
	{
		return k_EUniverseInternal;
	}

	uint32 GetServerRealTime()
	{
		// Return fake time milliseconds

		return (uint32)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
};