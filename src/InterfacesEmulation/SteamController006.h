#pragma once
#include "../public SDK/ISteamController006.h"

class SteamControllerIn006 : public ISteamController006
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

	void ActivateActionSetLayer(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle)
	{
		return;
	}
	void DeactivateActionSetLayer(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle)
	{
		return;
	}
	void DeactivateAllActionSetLayers(ControllerHandle_t controllerHandle)
	{
		return;
	}
	int GetActiveActionSetLayers(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t* handlesOut)
	{
		return NULL;
	}


	ControllerDigitalActionHandle_t GetDigitalActionHandle(const char* pszActionName)
	{
		return NULL;
	}

	ControllerDigitalActionData_t GetDigitalActionData(ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle)
	{
		ControllerDigitalActionData_t dt;
		dt.bActive = false;
		dt.bState = false;
		return dt;
	}

	int GetDigitalActionOrigins(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin* originsOut)
	{
		return NULL;
	}

	ControllerAnalogActionHandle_t GetAnalogActionHandle(const char* pszActionName)
	{
		return NULL;
	}

	ControllerAnalogActionData_t GetAnalogActionData(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle)
	{
		ControllerAnalogActionData_t ct;
		ct.bActive = false;
		ct.eMode = k_EControllerSourceMode_None;
		ct.x = 0;
		ct.y = 0;
		return ct;
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

	void TriggerRepeatedHapticPulse(ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags)
	{
		return;
	}

	void TriggerVibration(ControllerHandle_t controllerHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed)
	{
		return;
	}

	void SetLEDColor(ControllerHandle_t controllerHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags)
	{
		return;
	}

	int GetGamepadIndexForController(ControllerHandle_t ulControllerHandle)
	{
		return NULL;
	}

	ControllerHandle_t GetControllerForGamepadIndex(int nIndex)
	{
		return NULL;
	}

	ControllerMotionData_t GetMotionData(ControllerHandle_t controllerHandle)
	{
		ControllerMotionData_t ctd;
		ctd = { 0 };
		return ctd;
	}

	bool ShowDigitalActionOrigins(ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle, float flScale, float flXPosition, float flYPosition)
	{
		return false;
	}
	bool ShowAnalogActionOrigins(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle, float flScale, float flXPosition, float flYPosition)
	{
		return false;
	}

	const char* GetStringForActionOrigin(EControllerActionOrigin eOrigin)
	{
		return "";
	}

	const char* GetGlyphForActionOrigin(EControllerActionOrigin eOrigin)
	{
		return "";
	}

	ESteamInputType GetInputTypeForHandle(ControllerHandle_t controllerHandle)
	{
		return k_ESteamInputType_Unknown;
	}
};