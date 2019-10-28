#pragma once
#include "../public SDK/ISteamController002.h"

class SteamControllerIn002 : public ISteamController002
{
public:
	bool Init()
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

	int GetConnectedControllers(uint64*)
	{
		return NULL;
	}

	void TriggerHapticPulse(uint32 unControllerIndex, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
	{
		return;
	}

	unknown_ret ActivateMode(uint64, int32)
	{
		return NULL;
	}
	int32 GetJoystickForHandle(uint64)
	{
		return NULL;
	}
	uint64 GetHandleForJoystick(int32)
	{
		return NULL;
	}
	unknown_ret GetModeAnalogOutputData(uint64, int32)
	{
		return NULL;
	}
};