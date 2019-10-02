#pragma once
#include "../public SDK/ISteamMusicRemote001.h"

class SteamMusicRemoteIn001 : public ISteamMusicRemote001
{
public:
	bool RegisterSteamMusicRemote(const char* pchName)
	{
		return false;
	}
	bool DeregisterSteamMusicRemote()
	{
		return false;
	}
	bool BIsCurrentMusicRemote()
	{
		return false;
	}
	bool BActivationSuccess(bool bValue)
	{
		return false;
	}

	bool SetDisplayName(const char* pchDisplayName)
	{
		return false;
	}
	bool SetPNGIcon_64x64(void* pvBuffer, uint32 cbBufferLength)
	{
		return false;
	}

	bool EnablePlayPrevious(bool bValue)
	{
		return false;
	}
	bool EnablePlayNext(bool bValue)
	{
		return false;
	}
	bool EnableShuffled(bool bValue)
	{
		return false;
	}
	bool EnableLooped(bool bValue)
	{
		return false;
	}
	bool EnableQueue(bool bValue)
	{
		return false;
	}
	bool EnablePlaylists(bool bValue)
	{
		return false;
	}

	bool UpdatePlaybackStatus(AudioPlayback_Status nStatus)
	{
		return false;
	}
	bool UpdateShuffled(bool bValue)
	{
		return false;
	}
	bool UpdateLooped(bool bValue)
	{
		return false;
	}
	bool UpdateVolume(float flValue)
	{
		return false;
	}

	bool CurrentEntryWillChange()
	{
		return false;
	}
	bool CurrentEntryIsAvailable(bool bAvailable)
	{
		return false;
	}
	bool UpdateCurrentEntryText(const char* pchText)
	{
		return false;
	}
	bool UpdateCurrentEntryElapsedSeconds(int nValue)
	{
		return false;
	}
	bool UpdateCurrentEntryCoverArt(void* pvBuffer, uint32 cbBufferLength)
	{
		return false;
	}
	bool CurrentEntryDidChange()
	{
		return false;
	}

	bool QueueWillChange()
	{
		return false;
	}
	bool ResetQueueEntries()
	{
		return false;
	}
	bool SetQueueEntry(int nID, int nPosition, const char* pchEntryText)
	{
		return false;
	}
	bool SetCurrentQueueEntry(int nID)
	{
		return false;
	}
	bool QueueDidChange()
	{
		return false;
	}

	bool PlaylistWillChange()
	{
		return false;
	}
	bool ResetPlaylistEntries()
	{
		return false;
	}
	bool SetPlaylistEntry(int nID, int nPosition, const char* pchEntryText)
	{
		return false;
	}
	bool SetCurrentPlaylistEntry(int nID)
	{
		return false;
	}
	bool PlaylistDidChange()
	{
		return false;
	}
};