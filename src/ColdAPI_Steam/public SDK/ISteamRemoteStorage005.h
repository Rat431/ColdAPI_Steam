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

#ifndef ISTEAMREMOTESTORAGE005_H
#define ISTEAMREMOTESTORAGE005_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "RemoteStorageCommon.h"

//-----------------------------------------------------------------------------
// Purpose: Functions for accessing, reading and writing files stored remotely 
//			and cached locally
//-----------------------------------------------------------------------------
abstract_class ISteamRemoteStorage005
{
public:
public:
	// NOTE
	//
	// Filenames are case-insensitive, and will be converted to lowercase automatically.
	// So "foo.bar" and "Foo.bar" are the same file, and if you write "Foo.bar" then
	// iterate the files, the filename returned will be "foo.bar".
	//

	// file operations
	virtual bool	FileWrite( const char *pchFile, const void *pvData, int32 cubData ) = 0;
	virtual int32	FileRead( const char *pchFile, void *pvData, int32 cubDataToRead ) = 0;
	virtual bool	FileForget( const char *pchFile ) = 0;
	virtual bool	FileDelete( const char *pchFile ) = 0;
	virtual SteamAPICall_t FileShare( const char *pchFile ) = 0;
	virtual bool	SetSyncPlatforms( const char *pchFile, ERemoteStoragePlatform eRemoteStoragePlatform ) = 0;

	// file information
	virtual bool	FileExists( const char *pchFile ) = 0;
	virtual bool	FilePersisted( const char *pchFile ) = 0;
	virtual int32	GetFileSize( const char *pchFile ) = 0;
	virtual int64	GetFileTimestamp( const char *pchFile ) = 0;
	virtual ERemoteStoragePlatform GetSyncPlatforms( const char *pchFile ) = 0;

	// iteration
	virtual int32 GetFileCount() = 0;
	virtual const char *GetFileNameAndSize( int iFile, int32 *pnFileSizeInBytes ) = 0;

	// configuration management
	virtual bool GetQuota( int32 *pnTotalBytes, int32 *puAvailableBytes ) = 0;
	virtual bool IsCloudEnabledForAccount() = 0;
	virtual bool IsCloudEnabledForApp() = 0;
	virtual void SetCloudEnabledForApp( bool bEnabled ) = 0;

	// user generated content
	virtual SteamAPICall_t UGCDownload( UGCHandle_t hContent ) = 0;
	virtual bool	GetUGCDetails( UGCHandle_t hContent, AppId_t *pnAppID, char **ppchName, int32 *pnFileSizeInBytes, CSteamID *pSteamIDOwner ) = 0;
	virtual int32	UGCRead( UGCHandle_t hContent, void *pvData, int32 cubDataToRead ) = 0;

	// user generated content iteration
	virtual int32	GetCachedUGCCount() = 0;
	virtual	UGCHandle_t GetCachedUGCHandle( int32 iCachedContent ) = 0;

	// The following functions are only necessary on the Playstation 3. On PC & Mac, the Steam client will handle these operations for you
	// On Playstation 3, the game controls which files are stored in the cloud, via FilePersist, FileFetch, and FileForget.

#if defined(_PS3) || defined(_SERVER)
	// Connect to Steam and get a list of files in the Cloud - results in a RemoteStorageAppSyncStatusCheck_t callback
	virtual void GetFileListFromServer() = 0;
	// Indicate this file should be downloaded in the next sync
	virtual bool FileFetch( const char *pchFile ) = 0;
	// Indicate this file should be persisted in the next sync
	virtual bool FilePersist( const char *pchFile ) = 0;
	// Pull any requested files down from the Cloud - results in a RemoteStorageAppSyncedClient_t callback
	virtual bool SynchronizeToClient() = 0;
	// Upload any requested files to the Cloud - results in a RemoteStorageAppSyncedServer_t callback
	virtual bool SynchronizeToServer() = 0;
	// Reset any fetch/persist/etc requests
	virtual bool ResetFileRequestState() = 0;
#endif

	// publishing UGC
	virtual SteamAPICall_t	PublishFile( const char *pchFile, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags ) = 0;
	virtual SteamAPICall_t	PublishWorkshopFile( const char *pchFile, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, SteamParamStringArray_t *pTags ) = 0;
	virtual SteamAPICall_t	UpdatePublishedFile( RemoteStorageUpdatePublishedFileRequest_t updatePublishedFileRequest ) = 0;
	virtual SteamAPICall_t	GetPublishedFileDetails( PublishedFileId_t unPublishedFileId ) = 0;
	virtual SteamAPICall_t	DeletePublishedFile( PublishedFileId_t unPublishedFileId ) = 0;
	virtual SteamAPICall_t	EnumerateUserPublishedFiles( uint32 unStartIndex ) = 0;
	virtual SteamAPICall_t	SubscribePublishedFile( PublishedFileId_t unPublishedFileId ) = 0;
	virtual SteamAPICall_t	EnumerateUserSubscribedFiles( uint32 unStartIndex ) = 0;
	virtual SteamAPICall_t	UnsubscribePublishedFile( PublishedFileId_t unPublishedFileId ) = 0;
};

#endif // ISTEAMREMOTESTORAGE005_H
