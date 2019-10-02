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

#ifndef ICLIENTMUSIC_H
#define ICLIENTMUSIC_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "MusicCommon.h"

enum MediaController_Status
{
	// TODO: Reverse this enum
};

#define CLIENTMUSIC_INTERFACE_VERSION "CLIENTMUSIC_INTERFACE_VERSION001"

abstract_class UNSAFE_INTERFACE IClientMusic
{
public:
	virtual bool BIsEnabled() = 0;
	virtual void Enable( bool bUnk ) = 0;
	virtual void EnableCrawlLogging( bool bUnk ) = 0;
	virtual bool BIsPlaying() = 0;

	virtual int32 GetQueueCount() = 0;
	virtual int32 GetCurrentQueueEntry() = 0;
	virtual bool GetQueueEntryURI( int32 iIndex, char *, int32) = 0;
	virtual bool GetQueueEntryData( int32 iIndex, char *, int32, char *, int32, char *, int32 ) = 0;
	virtual void EmptyQueue() = 0;
	virtual void RemoveQueueEntry( int32 iIndex, bool bUnk ) = 0;
	virtual void AddAlbumToQueue( const char *, bool, bool ) = 0;
	virtual void AddTrackToQueue( const char *, bool, bool, bool ) = 0;

	virtual AudioPlayback_Status GetPlaybackStatus() = 0;

	virtual void SetPlayingLooped( bool bPlayingLooped ) = 0;
	virtual bool IsPlayingLooped() = 0;
	virtual void SetPlayingShuffled( bool bPlayingShuffled ) = 0;
	virtual bool IsPlayingShuffled() = 0;

	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual void PlayPrevious() = 0;
	virtual void PlayEntry( int32 ) = 0;

	virtual void SetVolume( float flVolume ) = 0;
	virtual float GetVolume() = 0;

	virtual void ResetLocalLibrary() = 0;

	virtual MediaController_Status GetStatusLocalLibrary() = 0;
	virtual void SaveLocalLibraryDirectorySettings() = 0;
	
	virtual int32 GetLocalLibraryDirectoryEntryCount() = 0;
	virtual bool GetLocalLibraryDirectoryEntry( int32, char *, int32 ) = 0;
	virtual void AddLocalLibraryDirectoryEntry( const char * ) = 0;
	virtual void ResetLocalLibraryDirectories( bool ) = 0;
	virtual bool GetDefaultLocalLibraryDirectory( char *, int32 );

	virtual void LocalLibraryStopCrawling() = 0;
	virtual void UpdateLocalLibraryDirectoriesToCrawl() = 0;
	virtual bool BLocalLibraryIsCrawling() = 0;
	virtual void CrawlAlbum( const char * ) = 0;
	virtual void CrawlTrack( const char * ) = 0;

	virtual int32 GetLocalLibraryAlbumCount() = 0;
	virtual bool GetLocalLibraryAlbumKey( int32, char *, int32 ) = 0;

	virtual bool GetLocalLibraryAlbumEntry( const char *, char *, int32, char *, int32, int32 *, bool * ) = 0;
	virtual bool GetLocalLibraryAlbumTrackEntry( const char *, int32, char *, int32, int32 *, char *, int32 ) = 0;
	virtual int32 GetLocalLibraryTrackCount() = 0;
	virtual bool GetLocalLibraryAlbumTrackKey( const char *, int32, char *, int32 ) = 0;
	virtual int32 GetLocalLibraryTrackCountForAlbum( const char * ) = 0;
	virtual int32 GetLocalLibraryArtistCount() = 0;
	virtual bool GetLocalLibraryArtistName( int32, char *, int32 ) = 0;
	virtual int32 GetLocalLibraryAlbumCountForArtistName( const char * ) = 0;
	virtual bool GetLocalLibraryArtistAlbumKey( const char *, int32, char *, int32 ) = 0;

	virtual void StartUsingSpotify() = 0;
	virtual void StopUsingSpotify() = 0;
	virtual MediaController_Status GetStatusSpotify() = 0;
	virtual void LoginSpotify( const char *, const char * ) = 0;
	virtual void ReloginSpotify() = 0;
	virtual const char * GetCurrentUserSpotify() = 0;
	virtual void ForgetCurrentUserSpotify() = 0;
	virtual void LogoutSpotify() = 0;
	virtual void DumpStatusToConsole() = 0;
};

#endif // ICLIENTMUSIC_H
