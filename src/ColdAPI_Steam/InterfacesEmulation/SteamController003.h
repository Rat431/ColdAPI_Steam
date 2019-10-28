#pragma once
#include "../public SDK/ISteamController003.h"

class SteamControllerIn003 : public ISteamController003
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

	int GetConnectedControllers(ControllerHandle_t* handlesOut)
	{
		return NULL;
	}

	bool ShowBindingPanel(ControllerHandle_t controllerHandle)
	{
		return false;
	}

	ControllerActionSetHandle_t GetActionSetHandle(const char* pszActionSetName)
	{
		return NULL;
	}

	void ActivateActionSet(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle)
	{
		return;
	}
	ControllerActionSetHandle_t GetCurrentActionSet(ControllerHandle_t controllerHandle)
	{
		return NULL;
	}

	ControllerDigitalActionHandle_t GetDigitalActionHandle(const char* pszActionName)
	{
		return NULL;
	}

	ControllerDigitalActionData003_t GetDigitalActionData(ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle)
	{
		ControllerDigitalActionData003_t contr;
		contr.bActive = false;
		contr.bState = false;
		return contr;
	}

	int GetDigitalActionOrigins(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin* originsOut)
	{
		return NULL;
	}

	ControllerAnalogActionHandle_t GetAnalogActionHandle(const char* pszActionName)
	{
		return NULL;
	}

	ControllerAnalogActionData003_t GetAnalogActionData(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle)
	{
		ControllerAnalogActionData003_t control;
		control.bActive = false;
		control.eMode = k_EControllerSourceMode_None;
		control.x = 0;
		control.y = 0;
		return control;
	}

	int GetAnalogActionOrigins(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin* originsOut)
	{
		return NULL;
	}



	void StopAnalogActionMomentum(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction)
	{
		return;
	}

	void TriggerHapticPulse(ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
	{
		return;
	}
};