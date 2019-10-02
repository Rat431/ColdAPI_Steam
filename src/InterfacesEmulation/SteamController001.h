#pragma once
#include "../public SDK/ISteamController001.h"

class SteamControllerIn001 : public ISteamController001
{
public:
	bool Init(const char* pchAbsolutePathToControllerConfigVDF)
	{
		return true;
	}
	bool Shutdown()
	{
		return true;
	}

	void RunFrame()
	{
		return;
	}

	bool GetControllerState(uint32 unControllerIndex, SteamControllerState_t* pState)
	{
		return false;
	}

	void TriggerHapticPulse(uint32 unControllerIndex, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
	{
		return;
	}

	void SetOverrideMode(const char* pchMode)
	{
		return;
	}
};
