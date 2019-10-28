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

#ifndef APPSCOMMON_H
#define APPSCOMMON_H
#ifdef _WIN32
#pragma once
#endif



#define CLIENTAPPS_INTERFACE_VERSION "CLIENTAPPS_INTERFACE_VERSION001"
#define CLIENTAPPMANAGER_INTERFACE_VERSION "CLIENTAPPMANAGER_INTERFACE_VERSION001"

#define STEAMAPPS_INTERFACE_VERSION_001 "STEAMAPPS_INTERFACE_VERSION001"
#define STEAMAPPS_INTERFACE_VERSION_002 "STEAMAPPS_INTERFACE_VERSION002"
#define STEAMAPPS_INTERFACE_VERSION_003 "STEAMAPPS_INTERFACE_VERSION003"
#define STEAMAPPS_INTERFACE_VERSION_004 "STEAMAPPS_INTERFACE_VERSION004"
#define STEAMAPPS_INTERFACE_VERSION_005 "STEAMAPPS_INTERFACE_VERSION005"
#define STEAMAPPS_INTERFACE_VERSION_006 "STEAMAPPS_INTERFACE_VERSION006"
#define STEAMAPPS_INTERFACE_VERSION_007 "STEAMAPPS_INTERFACE_VERSION007"
#define STEAMAPPS_INTERFACE_VERSION_008 "STEAMAPPS_INTERFACE_VERSION008"


enum EAppState
{
	k_EAppStateInvalid			= 0,
	k_EAppStateUninstalled		= 1,
	k_EAppStateUpdateRequired	= 2,
	k_EAppStateFullyInstalled	= 4,
	k_EAppStateDataEncrypted	= 8,
	k_EAppStateSharedOnly		= 64,
	k_EAppStateDataLocked		= 16,
	k_EAppStateFilesMissing		= 32,
	k_EAppStateFilesCorrupt		= 128,
	k_EAppStateAppRunning		= 8192,
	k_EAppStateBackupRunning	= 4096,
	k_EAppStateUpdateRunning	= 256,
	k_EAppStateUpdateStopping	= 8388608,
	k_EAppStateUpdatePaused		= 512,
	k_EAppStateUpdateStarted	= 1024,
	k_EAppStateReconfiguring	= 65536,
	k_EAppStateAddingFiles		= 262144,
	k_EAppStateDownloading		= 1048576,
	k_EAppStateStaging			= 2097152,
	k_EAppStateCommitting		= 4194304,
	k_EAppStateUninstalling		= 2048,
	k_EAppStatePreallocating	= 524288,
	k_EAppStateValidating		= 131072,
};

enum EAppEvent
{
	k_EAppEventDownloadComplete = 2,
};

enum EAppInfoSection
{
	k_EAppInfoSectionUnknown = 0,
	k_EAppInfoSectionAll,
	k_EAppInfoSectionCommon,
	k_EAppInfoSectionExtended,
	k_EAppInfoSectionConfig,
	k_EAppInfoSectionStats,
	k_EAppInfoSectionInstall,
	k_EAppInfoSectionDepots,
	k_EAppInfoSectionVac,
	k_EAppInfoSectionDrm,
	k_EAppInfoSectionUfs,
	k_EAppInfoSectionOgg,
	k_EAppInfoSectionItems,
	k_EAppInfoSectionPolicies,
	k_EAppInfoSectionSysreqs,
	k_EAppInfoSectionCommunity
};

#pragma pack( push, 1 )
struct AppUpdateInfo_s
{
	RTime32 m_timeUpdateStart;
	uint64 m_unBytesToDownload;
	uint64 m_unBytesDownloaded;
	uint64 m_unBytesToProcess;
	uint64 m_unBytesProcessed;
	uint32 m_uUnk;
};
#pragma pack( pop )

struct DownloadStats_s
{
	uint32 m_uIsDownloadEnabled;
	uint32 m_unCurrentConnections;
	uint32 m_unCurrentBytesPerSec;
	uint64 m_unTotalBytesDownload;
	CellID_t m_unCurrentCell;
};

enum EAppDownloadPriority
{
	k_EAppDownloadPriorityNone = 0,
	k_EAppDownloadPriorityFirst = 1,
	k_EAppDownloadPriorityUp = 2,
	k_EAppDownloadPriorityDown = 3,
	k_EAppDownloadPriorityLast = 4,
	k_EAppDownloadPriorityPaused = 5,
};

enum EAppUpdateError
{
	k_EAppErrorNone = 0,
	k_EAppErrorUnspecified = 1,
	k_EAppErrorPaused = 2,
	k_EAppErrorCanceled = 3,
	k_EAppErrorSuspended = 4,
	k_EAppErrorNoSubscription = 5,
	k_EAppErrorNoConnection = 6,
	k_EAppErrorTimeout = 7,
	k_EAppErrorMissingKey = 8,
	k_EAppErrorMissingConfig = 9,
	k_EAppErrorDiskReadFailure = 10,
	k_EAppErrorDiskWriteFailure = 11,
	k_EAppErrorCorruptContent = 13,
	k_EAppErrorWaitingForDisk = 14,
	k_EAppErrorInvalidInstallPath = 15,
	k_EAppErrorApplicationRunning = 16,
	k_EAppErrorDependencyFailure = 17,
	k_EAppErrorNotInstalled = 18,
	k_EAppErrorUpdateRequired = 19,
	k_EAppErrorStillBusy = 20,
	k_EAppErrorNoConnectionToContentServers = 21,
	k_EAppErrorInvalidApplicationConfiguration = 22,
	k_EAppErrorInvalidContentConfiguration = 23,
	k_EAppErrorMissingManifest = 24,
	k_EAppErrorNotReleased = 25,
	k_EAppErrorRegionRestricted = 26,
	k_EAppErrorCorruptDepotCache = 27,
	k_EAppErrorMissingExecutable = 28,
	k_EAppErrorInvalidPlatform = 29,
	k_EAppErrorInvalidFileSystem = 30,
	k_EAppErrorCorruptUpdateFiles = 31,
};

//-----------------------------------------------------------------------------
// Purpose: possible results when registering an activation code
//-----------------------------------------------------------------------------
enum ERegisterActivactionCodeResult
{
	k_ERegisterActivactionCodeResultOK = 0,
	k_ERegisterActivactionCodeResultFail = 1,
	k_ERegisterActivactionCodeResultAlreadyRegistered = 2,
	k_ERegisterActivactionCodeResultTimeout = 3,
	k_ERegisterActivactionCodeAlreadyOwned = 4
};

enum EAppOwernshipFlags
{
	k_EAppOwnershipFlags_None				= 0x0000,	// unknown
	k_EAppOwnershipFlags_OwnsLicense		= 0x0001,	// owns license for this game
	k_EAppOwnershipFlags_FreeLicense		= 0x0002,	// not paid for game
	k_EAppOwnershipFlags_RegionRestricted	= 0x0004,	// owns app, but not allowed to play in current region
	k_EAppOwnershipFlags_LowViolence		= 0x0008,	// only low violence version
	k_EAppOwnershipFlags_InvalidPlatform	= 0x0010,	// app not supported on current platform
	k_EAppOwnershipFlags_SharedLicense		= 0x0020,	// license was granted by authorized local device
	k_EAppOwnershipFlags_FreeWeekend		= 0x0040,	// owned by a free weekend licenses
	k_EAppOwnershipFlags_RetailLicense		= 0x0080,	// has a retail license for game, (CD-Key etc)
	k_EAppOwnershipFlags_LicenseLocked		= 0x0100,	// shared license is locked (in use) by other user
	k_EAppOwnershipFlags_LicensePending		= 0x0200,	// owns app, but transaction is still pending. Can't install or play
	k_EAppOwnershipFlags_LicenseExpired		= 0x0400,	// doesn't own app anymore since license expired
	k_EAppOwnershipFlags_LicensePermanent	= 0x0800,	// permanent license, not borrowed, or guest or freeweekend etc
	k_EAppOwnershipFlags_LicenseRecurring	= 0x1000,	// Recurring license, user is charged periodically
	k_EAppOwnershipFlags_LicenseCanceled	= 0x2000,	// Mark as canceled, but might be still active if recurring
	k_EAppOwnershipFlags_AutoGrant			= 0x4000,	// Ownership is based on any kind of autogrant license
	k_EAppOwnershipFlags_PendingGift		= 0x8000,	// user has pending gift to redeem
};

enum EAppReleaseState
{
	k_EAppReleaseStateUnknown = 0,
	k_EAppReleaseStateUnavailable,
	k_EAppReleaseStatePrerelease,
	k_EAppReleaseStatePreloadonly,
	k_EAppReleaseStateReleased,
};

enum EAppType
{
	k_EAppType_Invalid				= 0x000,	// unknown / invalid
	k_EAppType_Game					= 0x001,	// playable game, default type
	k_EAppType_Application			= 0x002,	// software application
	k_EAppType_Tool					= 0x004,	// SDKs, editors & dedicated servers
	k_EAppType_Demo					= 0x008,	// game demo
	k_EAppType_Media_DEPRECATED		= 0x010,	// legacy - was used for game trailers, which are now just videos on the web
	k_EAppType_DLC					= 0x020,	// down loadable content
	k_EAppType_Guide				= 0x040,	// game guide, PDF etc
	k_EAppType_Driver				= 0x080,	// hardware driver updater (ATI, Razor etc)
	k_EAppType_Config				= 0x100,	// hidden app used to config Steam features (backpack, sales, etc)
	k_EAppType_Hardware				= 0x200,	// a hardware device (Steam Machine, Steam Controller, Steam Link, etc.)
	// 0x400 is up for grabs here
	k_EAppType_Video				= 0x800,	// A video component of either a Film or TVSeries (may be the feature, an episode, preview, making-of, etc)
	k_EAppType_Plugin				= 0x1000,	// Plug-in types for other Apps
	k_EAppType_Music				= 0x2000,	// Music files

	k_EAppType_Shortcut				= 0x40000000,	// just a shortcut, client side only
	k_EAppType_DepotOnly			= 0x80000000,	// placeholder since depots and apps share the same namespace
};

struct SHADigestWrapper_t
{
	uint32 A;
	uint32 B;
	uint32 C;
	uint32 D;
	uint32 E;
};

const int k_cubAppProofOfPurchaseKeyMax = 64;			// max bytes of a legacy cd key we support

#pragma pack( push, 8 )
//-----------------------------------------------------------------------------
// Purpose: called when new information about an app has arrived
//-----------------------------------------------------------------------------
struct AppDataChanged_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 1 };

	AppId_t m_nAppID;

	bool m_bBySteamUI;
	bool m_bCDDBUpdate;
};

struct RequestAppCallbacksComplete_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 2 };
};

struct AppInfoUpdateComplete_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 3 };

	EResult m_EResult;
	uint32 m_cAppsUpdated;
	bool m_bSteam2CDDBChanged;
};

struct AppEventTriggered_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 4 };

	AppId_t m_nAppID;
	EAppEvent m_eAppEvent;
};

//-----------------------------------------------------------------------------
// Purpose: posted after the user gains ownership of DLC & that DLC is installed
//-----------------------------------------------------------------------------
struct DlcInstalled_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 5 };

	AppId_t m_nAppID;		// AppID of the DLC
};

struct AppEventStateChange_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 6 };

	AppId_t m_nAppID;
	uint32 m_eOldState;
	uint32 m_eNewState;
	EAppUpdateError m_eAppError;
};

struct AppValidationComplete_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 7 };

	AppId_t m_nAppID;
	bool m_bFinished;

	uint64 m_TotalBytesValidated;
	uint64 m_TotalBytesFailed;
	uint32 m_TotalFilesValidated;
	uint32 m_TotalFilesFailed;
	uint32 m_TotalFilesFailedCEGFiles;
};

//-----------------------------------------------------------------------------
// Purpose: response to RegisterActivationCode()
//-----------------------------------------------------------------------------
struct RegisterActivationCodeResponse_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 8 };

	ERegisterActivactionCodeResult m_eResult;
	uint32 m_unPackageRegistered;						// package that was registered. Only set on success
};

struct DownloadScheduleChanged_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 9 };

	bool m_bDownloadEnabled;
	uint32 m_nTotalAppsScheduled;
	unsigned int m_rgunAppSchedule[32];
};

struct DlcInstallRequest_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 10 };

	AppId_t m_nAppID;
	bool m_bInstall;
};

struct AppLaunchTenFootOverlay_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 11 };

	CGameID m_GameID;
	uint64 m_nPid;
	bool m_bCanShareSurfaces;
};

struct AppBackupStatus_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 12 };

	AppId_t m_nAppID;
	EResult m_eResult;
	
	uint64 m_unBytesToProcess;
	uint64 m_unBytesProcessed;
	uint64 m_unTotalBytesWritten;
	uint64 m_unBytesFailed;
};

struct RequestAppProofOfPurchaseKeyResponse_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 13 };

	EResult m_eResult;
	AppId_t m_nAppID;
	char m_rgchKey[ k_cubAppProofOfPurchaseKeyMax ];	
};

//---------------------------------------------------------------------------------
// Purpose: posted after the user gains executes a steam url with query parameters
// such as steam://run/<appid>//?param1=value1;param2=value2;param3=value3; etc
// while the game is already running.  The new params can be queried
// with GetLaunchQueryParam.
//---------------------------------------------------------------------------------
struct NewLaunchQueryParameters_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 14 };
};
#pragma pack( pop )

#endif // APPSCOMMON_H
