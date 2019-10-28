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

#ifndef VIDEOCOMMON_H
#define VIDEOCOMMON_H
#ifdef _WIN32
#pragma once
#endif
#define STEAMVIDEO_INTERFACE_VERSION_001 "STEAMVIDEO_INTERFACE_V001"
#define STEAMVIDEO_INTERFACE_VERSION_002 "STEAMVIDEO_INTERFACE_V002"

//-----------------------------------------------------------------------------
// Purpose: Broadcast upload result details
//-----------------------------------------------------------------------------
enum EBroadcastUploadResult
{
	k_EBroadcastUploadResultNone = 0,	// broadcast state unknown
	k_EBroadcastUploadResultOK = 1,		// broadcast was good, no problems
	k_EBroadcastUploadResultInitFailed = 2,	// broadcast init failed
	k_EBroadcastUploadResultFrameFailed = 3,	// broadcast frame upload failed
	k_EBroadcastUploadResultTimeout = 4,	// broadcast upload timed out
	k_EBroadcastUploadResultBandwidthExceeded = 5,	// broadcast send too much data
	k_EBroadcastUploadResultLowFPS = 6,	// broadcast FPS too low
	k_EBroadcastUploadResultMissingKeyFrames = 7,	// broadcast sending not enough key frames
	k_EBroadcastUploadResultNoConnection = 8,	// broadcast client failed to connect to relay
	k_EBroadcastUploadResultRelayFailed = 9,	// relay dropped the upload
	k_EBroadcastUploadResultSettingsChanged = 10,	// the client changed broadcast settings 
	k_EBroadcastUploadResultMissingAudio = 11,	// client failed to send audio data
	k_EBroadcastUploadResultTooFarBehind = 12,	// clients was too slow uploading
	k_EBroadcastUploadResultTranscodeBehind = 13,	// server failed to keep up with transcode
};



#pragma pack( push, 8 )

DEFINE_CALLBACK( BroadcastUploadStart_t, k_iClientVideoCallbacks + 4 )
END_DEFINE_CALLBACK_0()

DEFINE_CALLBACK( BroadcastUploadStop_t, k_iClientVideoCallbacks + 5 )
	CALLBACK_MEMBER( 0, EBroadcastUploadResult, m_eResult )
END_DEFINE_CALLBACK_1()

DEFINE_CALLBACK( GetVideoURLResult_t, k_iClientVideoCallbacks + 11 )
	CALLBACK_MEMBER( 0, EResult, m_eResult )
	CALLBACK_MEMBER( 1, AppId_t, m_unVideoAppID )
	CALLBACK_MEMBER( 2, char, m_rgchURL[256] )
END_DEFINE_CALLBACK_1()

#pragma pack( pop )


#endif // VIDEOCOMMON_H
