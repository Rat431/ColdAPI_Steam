#include "SteamTypes.h"

enum ESteamDeviceFormFactor
{
	k_ESteamDeviceFormFactorUnknown,
	k_ESteamDeviceFormFactorPhone,
	k_ESteamDeviceFormFactorTablet,
	k_ESteamDeviceFormFactorComputer,
	k_ESteamDeviceFormFactorTV,
};


//-----------------------------------------------------------------------------
// Purpose: Functions to provide information about Steam Remote Play sessions
//-----------------------------------------------------------------------------
class ISteamRemotePlay001
{
public:
	// Get the number of currently connected Steam Remote Play sessions
	virtual uint32 GetSessionCount() = 0;

	// Get the currently connected Steam Remote Play session ID at the specified index. Returns zero if index is out of bounds.
	virtual uint32 GetSessionID(int iSessionIndex) = 0;

	// Get the SteamID of the connected user
	virtual CSteamID GetSessionSteamID(uint32 unSessionID) = 0;

	// Get the name of the session client device
	// This returns NULL if the sessionID is not valid
	virtual const char* GetSessionClientName(uint32 unSessionID) = 0;

	// Get the form factor of the session client device
	virtual ESteamDeviceFormFactor GetSessionClientFormFactor(uint32 unSessionID) = 0;

	// Get the resolution, in pixels, of the session client device
	// This is set to 0x0 if the resolution is not available
	virtual bool BGetSessionClientResolution(uint32 unSessionID, int* pnResolutionX, int* pnResolutionY) = 0;
};

#define STEAMREMOTEPLAY_INTERFACE_VERSION001 "STEAMREMOTEPLAY_INTERFACE_VERSION001"