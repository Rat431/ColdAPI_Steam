//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef UTILSCOMMON_H
#define UTILSCOMMON_H
#ifdef _WIN32
#pragma once
#endif



#define CLIENTUTILS_INTERFACE_VERSION "CLIENTUTILS_INTERFACE_VERSION001"

#define STEAMUTILS_INTERFACE_VERSION_001 "SteamUtils001"
#define STEAMUTILS_INTERFACE_VERSION_003 "SteamUtils003"
#define STEAMUTILS_INTERFACE_VERSION_002 "SteamUtils002"
#define STEAMUTILS_INTERFACE_VERSION_004 "SteamUtils004"
#define STEAMUTILS_INTERFACE_VERSION_005 "SteamUtils005"
#define STEAMUTILS_INTERFACE_VERSION_006 "SteamUtils006"
#define STEAMUTILS_INTERFACE_VERSION_007 "SteamUtils007"
#define STEAMUTILS_INTERFACE_VERSION_008 "SteamUtils008"
#define STEAMUTILS_INTERFACE_VERSION_009 "SteamUtils009"


// Steam API call failure results
typedef enum ESteamAPICallFailure
{
	k_ESteamAPICallFailureNone = -1,			// no failure
	k_ESteamAPICallFailureSteamGone = 0,		// the local Steam process has gone away
	k_ESteamAPICallFailureNetworkFailure = 1,	// the network connection to Steam has been broken, or was already broken
	// SteamServersDisconnected_t callback will be sent around the same time
	// SteamServersConnected_t will be sent when the client is able to talk to the Steam servers again
	k_ESteamAPICallFailureInvalidHandle = 2,	// the SteamAPICall_t handle passed in no longer exists
	k_ESteamAPICallFailureMismatchedCallback = 3,// GetAPICallResult() was called with the wrong callback type for this API call
} ESteamAPICallFailure;

typedef enum EConfigStore
{
	k_EConfigStoreInvalid = 0,
	k_EConfigStoreInstall = 1,
	k_EConfigStoreUserRoaming = 2,
	k_EConfigStoreUserLocal = 3,
	k_EConfigStoreMax = 4,
} EConfigStore;

//-----------------------------------------------------------------------------
// results for CheckFileSignature
//-----------------------------------------------------------------------------
enum ECheckFileSignature
{
	k_ECheckFileSignatureInvalidSignature = 0,
	k_ECheckFileSignatureValidSignature = 1,
	k_ECheckFileSignatureFileNotFound = 2,
	k_ECheckFileSignatureNoSignaturesFoundForThisApp = 3,
	k_ECheckFileSignatureNoSignaturesFoundForThisFile = 4,
};

enum ESpewGroup
{
	k_ESpewGroupConsole = 0,
	k_ESpewGroupPublish = 1,
	k_ESpewGroupBootstrap = 2,
	k_ESpewGroupStartup = 3,
	k_ESpewGroupService = 4,
	k_ESpewGroupFileop = 5,
	k_ESpewGroupSystem = 6,
	k_ESpewGroupSmtp = 7,
	k_ESpewGroupAccount = 8,
	k_ESpewGroupJob = 9,
	k_ESpewGroupCrypto = 10,
	k_ESpewGroupNetwork = 11,
	k_ESpewGroupVac = 12,
	k_ESpewGroupClient = 13,
	k_ESpewGroupContent = 14,
	k_ESpewGroupCloud = 15,
	k_ESpewGroupLogon = 16,
	k_ESpewGroupClping = 17,
	k_ESpewGroupThreads = 18,
	k_ESpewGroupBsnova = 19,
	k_ESpewGroupTest = 20,
	k_ESpewGroupFiletx = 21,
	k_ESpewGroupStats = 22,
	k_ESpewGroupSrvping = 23,
	k_ESpewGroupFriends = 24,
	k_ESpewGroupChat = 25,
	k_ESpewGroupGuestpass = 26,
	k_ESpewGroupLicense = 27,
	k_ESpewGroupP2p = 28,
	k_ESpewGroupDatacoll = 29,
	k_ESpewGroupDrm = 30,
	k_ESpewGroupSvcm = 31,
	k_ESpewGroupHttpclient = 32,
	k_ESpewGroupHttpserver = 33,
};

//-----------------------------------------------------------------------------
// Purpose: codes for well defined launch options
//-----------------------------------------------------------------------------
enum ELaunchOptionType
{
	k_ELaunchOptionType_None		= 0,	// unknown what launch option does
	k_ELaunchOptionType_Default		= 1,	// runs the game, app, whatever in default mode
	k_ELaunchOptionType_SafeMode	= 2,	// runs the game in safe mode
	k_ELaunchOptionType_Multiplayer = 3,	// runs the game in multiplayer mode
	k_ELaunchOptionType_Config		= 4,	// runs config tool for this game
	k_ELaunchOptionType_VR			= 5,	// runs game in VR mode
	k_ELaunchOptionType_Server		= 6,	// runs dedicated server for this game
	k_ELaunchOptionType_Editor		= 7,	// runs game editor
	k_ELaunchOptionType_Manual		= 8,	// shows game manual
	k_ELaunchOptionType_Benchmark	= 9,	// runs game benchmark
	k_ELaunchOptionType_Option1		= 10,	// generic run option, uses description field for game name
	k_ELaunchOptionType_Option2		= 11,	// generic run option, uses description field for game name
	k_ELaunchOptionType_Option3     = 12,	// generic run option, uses description field for game name


	k_ELaunchOptionType_Dialog 		= 1000, // show launch options dialog
};

enum EUIMode
{
	k_EUIModeNormal = 0,
	k_EUIModeTenFoot = 1,
};

enum EGamepadTextInputMode
{
	// TODO: Reverse this enum
};

enum EGamepadTextInputLineMode
{
	// TODO: Reverse this enum
};

enum EWindowType
{
	// TODO: Reverse this enum
};

#pragma pack( push, 8 )
//-----------------------------------------------------------------------------
// Purpose: The country of the user changed
//-----------------------------------------------------------------------------
struct IPCountry_t
{
	enum { k_iCallback = k_iSteamUtilsCallbacks + 1 };
};


//-----------------------------------------------------------------------------
// Purpose: Fired when running on a laptop and less than 10 minutes of battery is left, fires then every minute
//-----------------------------------------------------------------------------
struct LowBatteryPower_t
{
	enum { k_iCallback = k_iSteamUtilsCallbacks + 2 };

	uint8 m_nMinutesBatteryLeft;
};

//-----------------------------------------------------------------------------
// Purpose: called when a SteamAsyncCall_t has completed (or failed)
//-----------------------------------------------------------------------------
struct SteamAPICallCompleted_t
{
	enum { k_iCallback = k_iSteamUtilsCallbacks + 3 };

	SteamAPICall_t m_hAsyncCall;
};

//-----------------------------------------------------------------------------
// called when Steam wants to shutdown
//-----------------------------------------------------------------------------
struct SteamShutdown_t
{
	enum { k_iCallback = k_iSteamUtilsCallbacks + 4 };
};

//-----------------------------------------------------------------------------
// callback for CheckFileSignature
//-----------------------------------------------------------------------------
struct CheckFileSignature_t
{
	enum { k_iCallback = k_iSteamUtilsCallbacks + 5 };

	ECheckFileSignature m_eCheckFileSignature;
};

struct SteamConfigStoreChanged_t
{
	enum { k_iCallback = k_iSteamUtilsCallbacks + 11 };

	EConfigStore m_eConfigStore;
	char m_szRootOfChanges[ 255 ];
};



// k_iClientUtilsCallbacks



struct CellIDChanged_t
{
	enum { k_iCallback = k_iClientUtilsCallbacks + 3 };

	CellID_t m_nCellID;
};

#pragma pack( pop )


#endif // UTILSCOMMON_H
