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

#ifndef ISTEAMMUSICREMOTE001_H
#define ISTEAMMUSICREMOTE001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "MusicCommon.h"
#include "MusicRemoteCommon.h"

//-----------------------------------------------------------------------------
// Purpose: interface to user independent utility functions
//-----------------------------------------------------------------------------
abstract_class ISteamMusicRemote001
{
public:
	// Service Definition
	virtual bool RegisterSteamMusicRemote( const char *pchName ) = 0;
	virtual bool DeregisterSteamMusicRemote() = 0;
	virtual bool BIsCurrentMusicRemote() = 0;
	virtual bool BActivationSuccess( bool bValue ) = 0;

	virtual bool SetDisplayName( const char *pchDisplayName ) = 0;
	virtual bool SetPNGIcon_64x64( void *pvBuffer, uint32 cbBufferLength ) = 0;

	// Abilities for the user interface
	virtual bool EnablePlayPrevious(bool bValue) = 0;
	virtual bool EnablePlayNext( bool bValue ) = 0;
	virtual bool EnableShuffled( bool bValue ) = 0;
	virtual bool EnableLooped( bool bValue ) = 0;
	virtual bool EnableQueue( bool bValue ) = 0;
	virtual bool EnablePlaylists( bool bValue ) = 0;

	// Status
	virtual bool UpdatePlaybackStatus( AudioPlayback_Status nStatus ) = 0;
	virtual bool UpdateShuffled( bool bValue ) = 0;
	virtual bool UpdateLooped( bool bValue ) = 0;
	virtual bool UpdateVolume( float flValue ) = 0; // volume is between 0.0 and 1.0

	// Current Entry
	virtual bool CurrentEntryWillChange() = 0;
	virtual bool CurrentEntryIsAvailable( bool bAvailable ) = 0;
	virtual bool UpdateCurrentEntryText( const char *pchText ) = 0;
	virtual bool UpdateCurrentEntryElapsedSeconds( int nValue ) = 0;
	virtual bool UpdateCurrentEntryCoverArt( void *pvBuffer, uint32 cbBufferLength ) = 0;
	virtual bool CurrentEntryDidChange() = 0;

	// Queue
	virtual bool QueueWillChange() = 0;
	virtual bool ResetQueueEntries() = 0;
	virtual bool SetQueueEntry( int nID, int nPosition, const char *pchEntryText ) = 0;
	virtual bool SetCurrentQueueEntry( int nID ) = 0;
	virtual bool QueueDidChange() = 0;

	// Playlist
	virtual bool PlaylistWillChange() = 0;
	virtual bool ResetPlaylistEntries() = 0;
	virtual bool SetPlaylistEntry( int nID, int nPosition, const char *pchEntryText ) = 0;
	virtual bool SetCurrentPlaylistEntry( int nID ) = 0;
	virtual bool PlaylistDidChange() = 0;
};

#endif // ISTEAMMUSICREMOTE001_H

