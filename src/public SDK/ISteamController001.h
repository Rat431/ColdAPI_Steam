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

#ifndef ISTEAMCONTROLLER001_H
#define ISTEAMCONTROLLER001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "ControllerCommon.h"

//-----------------------------------------------------------------------------
// Purpose: Native Steam controller support API
//-----------------------------------------------------------------------------
class ISteamController001
{
public:

	//
	// Native controller support API
	//

	// Must call init and shutdown when starting/ending use of the interface
	virtual bool Init( const char *pchAbsolutePathToControllerConfigVDF ) = 0;
	virtual bool Shutdown() = 0;

	// Pump callback/callresult events, SteamAPI_RunCallbacks will do this for you, 
	// normally never need to call directly.
	virtual void RunFrame() = 0;

	// Get the state of the specified controller, returns false if that controller is not connected
	virtual bool GetControllerState( uint32 unControllerIndex, SteamControllerState_t *pState ) = 0;

	// Trigger a haptic pulse on the controller
	virtual void TriggerHapticPulse( uint32 unControllerIndex, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec ) = 0;

	// Set the override mode which is used to choose to use different base/legacy bindings from your config file
	virtual void SetOverrideMode( const char *pchMode ) = 0;
};


#endif // ISTEAMCONTROLLER001_H
