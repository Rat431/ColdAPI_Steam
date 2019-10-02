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

#ifndef ISTEAMSCREENSHOTS001_H
#define ISTEAMSCREENSHOTS001_H
#ifdef _WIN32
#pragma once
#endif


#include "SteamTypes.h"
#include "ScreenshotsCommon.h"

//-----------------------------------------------------------------------------
// Purpose: Functions for adding screenshots to the user's screenshot library
//-----------------------------------------------------------------------------
abstract_class ISteamScreenshots001
{

public:
	// Writes a screenshot to the user's screenshot library given the raw image data, which must be in RGB format.
	// The return value is a handle that is valid for the duration of the game process and can be used to apply tags.
	virtual ScreenshotHandle WriteScreenshot( void *pubRGB, uint32 cubRGB, int nWidth, int nHeight ) = 0;

	// Adds a screenshot to the user's screenshot library from disk.  If a thumbnail is provided, it must be 200 pixels wide and the same aspect ratio
	// as the screenshot, otherwise a thumbnail will be generated if the user uploads the screenshot.  The screenshots must be in either JPEG or TGA format.
	// The return value is a handle that is valid for the duration of the game process and can be used to apply tags.
	// JPEG, TGA, and PNG formats are supported.
	virtual ScreenshotHandle AddScreenshotToLibrary( const char *pchFilename, const char *pchThumbnailFilename, int nWidth, int nHeight ) = 0;

	// Causes the Steam overlay to take a screenshot.  If screenshots are being hooked by the game then a ScreenshotRequested_t callback is sent back to the game instead. 
	virtual void TriggerScreenshot() = 0;

	// Toggles whether the overlay handles screenshots when the user presses the screenshot hotkey, or the game handles them.  If the game is hooking screenshots,
	// then the ScreenshotRequested_t callback will be sent if the user presses the hotkey, and the game is expected to call WriteScreenshot or AddScreenshotToLibrary
	// in response.
	virtual void HookScreenshots( bool bHook ) = 0;

	// Sets metadata about a screenshot's location (for example, the name of the map)
	virtual bool SetLocation( ScreenshotHandle hScreenshot, const char *pchLocation ) = 0;

	// Tags a user as being visible in the screenshot
	virtual bool TagUser( ScreenshotHandle hScreenshot, CSteamID steamID ) = 0;
};


#endif // ISTEAMSCREENSHOTS001_H
