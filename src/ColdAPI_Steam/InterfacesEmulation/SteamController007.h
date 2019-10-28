#pragma once
#include "../public SDK/ISteamController007.h"

class SteamControllerIn007 : public ISteamController007
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

	const char* GetGlyphForActionOrigin(EControllerActionOrigin eOrigin)
	{
		return "";
	}

	const char* GetStringForActionOrigin(EControllerActionOrigin eOrigin)
	{
		return "";
	}

	void StopAnalogActionMomentum(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction)
	{
		return;
	}

	ControllerMotionData_t GetMotionData(ControllerHandle_t controllerHandle)
	{
		ControllerMotionData_t ctd;
		ctd = { 0 };
		return ctd;
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

	bool ShowBindingPanel(ControllerHandle_t controllerHandle)
	{
		return false;
	}

	ESteamInputType GetInputTypeForHandle(ControllerHandle_t controllerHandle)
	{
		return k_ESteamInputType_Unknown;
	}

	ControllerHandle_t GetControllerForGamepadIndex(int nIndex)
	{
		return NULL;
	}

	int GetGamepadIndexForController(ControllerHandle_t ulControllerHandle)
	{
		return NULL;
	}

	const char* GetStringForXboxOrigin(EXboxOrigin eOrigin)
	{
		return "";
	}

	const char* GetGlyphForXboxOrigin(EXboxOrigin eOrigin)
	{
		return "";
	}

	EControllerActionOrigin GetActionOriginFromXboxOrigin(ControllerHandle_t controllerHandle, EXboxOrigin eOrigin)
	{
		return k_EControllerActionOrigin_None;
	}

	EControllerActionOrigin TranslateActionOrigin(ESteamInputType eDestinationInputType, EControllerActionOrigin eSourceOrigin)
	{
		return k_EControllerActionOrigin_None;
	}
};