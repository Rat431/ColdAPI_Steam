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

#ifndef MUSICREMOTECOMMON_H
#define MUSICREMOTECOMMON_H
#ifdef _WIN32
#pragma once
#endif

#define STEAMMUSICREMOTE_INTERFACE_VERSION_001 "STEAMMUSICREMOTE_INTERFACE_VERSION001"

#define k_SteamMusicNameMaxLength 255
#define k_SteamMusicPNGMaxLength 65535


#pragma pack( push, 8 )

struct MusicPlayerRemoteWillActivate_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 1 };
};

struct MusicPlayerRemoteWillDeactivate_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 2 };
};

struct MusicPlayerRemoteToFront_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 3 };
};

struct MusicPlayerWillQuit_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 4 };
};

struct MusicPlayerWantsPlay_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 5 };
};

struct MusicPlayerWantsPause_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 6 };
};

struct MusicPlayerWantsPlayPrevious_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 7 };
};

struct MusicPlayerWantsPlayNext_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 8 };
};

struct MusicPlayerWantsShuffled_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 9 };
	bool m_bShuffled;
};

struct MusicPlayerWantsLooped_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 10 };
	bool m_bLooped;
};

struct MusicPlayerWantsVolume_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 11 };
	float m_flNewVolume;
};

struct MusicPlayerSelectsQueueEntry_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 12 };
	int nID;
};

struct MusicPlayerSelectsPlaylistEntry_t
{
	enum { k_iCallback = k_iSteamMusicRemoteCallbacks + 13 };
	int nID;
};

#pragma pack( pop )

#endif // MUSICREMOTECOMMON_H
