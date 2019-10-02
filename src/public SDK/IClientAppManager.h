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

#ifndef ICLIENTAPPMANAGER_H
#define ICLIENTAPPMANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "AppsCommon.h"



abstract_class UNSAFE_INTERFACE IClientAppManager
{
public:
	virtual EAppUpdateError InstallApp( AppId_t unAppID, const char *cszAppDir, int32 iBaseFolder, bool bLegacy ) = 0;
	virtual EAppUpdateError ConvertFromSteam2( AppId_t unAppID, const char *cszPath ) = 0;
	virtual EAppUpdateError UninstallApp( AppId_t unAppID, bool bComplete ) = 0;

	virtual EAppUpdateError LaunchApp( AppId_t unAppID, uint32 uLaunchOption, const char *pszUserArgs ) = 0;
	virtual bool ShutdownApp( AppId_t unAppID, bool bForce ) = 0;

	virtual EAppState GetAppInstallState( AppId_t unAppID ) = 0;
	virtual uint32 GetAppBuildID( AppId_t unAppID ) = 0;

	// /!\ IPC is broken for this function
	virtual bool GetAppSizeOnDisk( AppId_t unAppID, uint64 *pullAppSize, uint64 *pullUnk ) = 0;

	virtual uint32 GetAppInstallDir( AppId_t unAppID, char *pchPath, uint32 cchPath ) = 0;

	virtual bool IsAppDlcInstalled( AppId_t unAppID, AppId_t unDLCAppID ) = 0;
	virtual uint32 GetNumInstalledApps() = 0;
	virtual uint32 GetInstalledApps( uint32 *punAppIDs, uint32 cAppIDsMax ) = 0;

	virtual uint32 GetAppDependency( AppId_t unAppID ) = 0;
	virtual uint32 GetDependentApps( AppId_t unAppID, AppId_t *punAppIDs, int32 cAppIDsMax ) = 0;

	virtual uint32 GetUpdateInfo( AppId_t unAppID, AppUpdateInfo_s *pUpdateInfo ) = 0;

	virtual bool SetContentLocked( AppId_t unAppID, bool bLockContent ) = 0;

	virtual bool SetAppConfig( AppId_t unAppID, uint8 *pchBuffer, int32 cbBuffer, bool bSharedKVSymbols ) = 0;
	virtual int32 GetAppConfigValue( AppId_t unAppID, const char *pchKey, char *pchValue, int32 cchValueMax ) = 0;
	virtual bool SetAppConfigValue( AppId_t unAppID, const char *pchKey, const char *pchValue ) = 0;

	virtual bool BIsAppUpToDate( AppId_t unAppID ) = 0;

	virtual uint32 GetAvailableLaunchOptions( AppId_t unAppID, uint32 puOptions[], uint32 cuOptionsMax ) = 0;
	virtual uint32 GetAvailableLanguages( AppId_t unAppID, bool, char *pchLanguages, uint32 cchLanguagesMax ) = 0;

	virtual bool StartValidatingApp( AppId_t unAppID ) = 0;
	virtual bool MarkContentCorrupt( AppId_t unAppID, bool bCorrupt ) = 0;

	virtual uint32 GetInstalledDepots( AppId_t unAppID, AppId_t puDepots[], uint32 cuDepotsMax ) = 0;

	virtual bool BCacheBetaPassword( AppId_t unAppID, const char *cszBetaKey, const char *cszBetaPassword ) = 0;
	virtual bool BRequestBetaPasswords( AppId_t unAppID ) = 0;
	virtual bool BIsCachedBetaPasswordValid( AppId_t unAppID, const char *cszBetaKey ) = 0;

	virtual bool SetDownloadingEnabled( bool bState ) = 0;
	virtual bool BIsDownloadingEnabled() = 0;

	virtual bool GetDownloadStats( DownloadStats_s *pDownloadStats ) = 0;

	virtual AppId_t GetDownloadingAppID() = 0;
	virtual bool ChangeAppPriority( AppId_t unAppID, EAppDownloadPriority ePriority ) = 0;

	virtual bool BHasLocalContentServer() = 0;

	virtual bool BuildBackup( AppId_t unAppID, uint64 ullMaxFileSize, const char *cszBackupPath ) = 0;
	virtual bool BuildInstaller( const char *cszProjectFile, const char *cszBackupPath, const char * ) = 0;
	virtual bool CancelBackup() = 0;
	virtual EAppUpdateError RestoreApp( AppId_t unAppID, int32 iBaseFolder, char const *cszBackupPath ) = 0;
	virtual bool BNeedsFile( AppId_t unAppID, char const *cszFilePath, uint64 ullFileSize, uint32 uUnk ) = 0;
	virtual bool BAddFileOnDisk( AppId_t unAppID, char const *cszFilePath, uint64 ullFileSize, uint32 uUnk, SHADigestWrapper_t ubSha1 ) = 0;
	virtual uint32 FinishAddingFiles( AppId_t unAppID ) = 0;

	virtual bool GetAppStateInfo( AppId_t unAppID, EAppReleaseState * peReleaseState, EAppOwernshipFlags * peOwernshipFlags, EAppState * peAppState ) = 0;

	virtual int32 GetNumInstallBaseFolders() = 0;
	virtual int32 GetInstallBaseFolder( int32 iBaseFolder, char *pchPath, int32 cbPath ) = 0;
	virtual int32 AddInstallBaseFolder( const char *szPath ) = 0;
	virtual bool RemoveInstallBaseFolder( int32 iBaseFolder ) = 0;
	virtual uint64 GetFreeDiskSpace( int32 iBaseFolder ) = 0;

	virtual int32 GetAppInstallBaseFolder( int32 iBaseFolder ) = 0;
	virtual void ForceInstallDirOverride( const char *cszPath ) = 0;

	virtual bool SetDownloadThrottleRateKbps( int32 iRate ) = 0;
	virtual int32 GetDownloadThrottleRateKbps() = 0;
	virtual void SuspendDownloadThrottling( bool bSuspend ) = 0;
};

#endif // ICLIENTAPPMANAGER_H
