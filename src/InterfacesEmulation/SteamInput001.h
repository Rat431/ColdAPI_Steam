#pragma once
#include "../public SDK/ISteamImput001.h"

class SteamInputIn001 : public ISteamInput001
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

	int GetConnectedControllers(InputHandle_t* handlesOut)
	{
		return NULL;
	}

	InputActionSetHandle_t GetActionSetHandle(const char* pszActionSetName)
	{
		return NULL;
	}

	void ActivateActionSet(InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle)
	{
		return;
	}
	InputActionSetHandle_t GetCurrentActionSet(InputHandle_t inputHandle)
	{
		return NULL;
	}

	void ActivateActionSetLayer(InputHandle_t inputHandle, InputActionSetHandle_t actionSetLayerHandle)
	{
		return;
	}
	void DeactivateActionSetLayer(InputHandle_t inputHandle, InputActionSetHandle_t actionSetLayerHandle)
	{
		return;
	}
	void DeactivateAllActionSetLayers(InputHandle_t inputHandle)
	{
		return;
	}
	int GetActiveActionSetLayers(InputHandle_t inputHandle, InputActionSetHandle_t* handlesOut)
	{
		return NULL;
	}

	InputDigitalActionHandle_t GetDigitalActionHandle(const char* pszActionName)
	{
		return NULL;
	}

	InputDigitalActionData_t GetDigitalActionData(InputHandle_t inputHandle, InputDigitalActionHandle_t digitalActionHandle)
	{
		InputDigitalActionData_t dt;
		dt.bActive = false;
		dt.bState = false;
		return dt;
	}

	int GetDigitalActionOrigins(InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputDigitalActionHandle_t digitalActionHandle, EInputActionOrigin* originsOut)
	{
		return NULL;
	}

	InputAnalogActionHandle_t GetAnalogActionHandle(const char* pszActionName)
	{
		return NULL;
	}

	InputAnalogActionData_t GetAnalogActionData(InputHandle_t inputHandle, InputAnalogActionHandle_t analogActionHandle)
	{
		InputAnalogActionData_t dt;
		dt.bActive = false;
		dt.eMode = k_EInputSourceMode_None;
		dt.x = 0;
		dt.y = 0;
		return dt;
	}

	int GetAnalogActionOrigins(InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputAnalogActionHandle_t analogActionHandle, EInputActionOrigin* originsOut)
	{
		return NULL;
	}

	const char* GetGlyphForActionOrigin(EInputActionOrigin eOrigin)
	{
		return "";
	}

	const char* GetStringForActionOrigin(EInputActionOrigin eOrigin)
	{
		return "";
	}

	void StopAnalogActionMomentum(InputHandle_t inputHandle, InputAnalogActionHandle_t eAction)
	{
		return;
	}

	InputMotionData_t GetMotionData(InputHandle_t inputHandle)
	{
		InputMotionData_t dt;
		dt = { 0 };
		return dt;
	}

	void TriggerVibration(InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed)
	{
		return;
	}

	void SetLEDColor(InputHandle_t inputHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags)
	{
		return;
	}

	void TriggerHapticPulse(InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
	{
		return;
	}

	void TriggerRepeatedHapticPulse(InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags)
	{
		return;
	}

	bool ShowBindingPanel(InputHandle_t inputHandle)
	{
		return false;
	}

	ESteamInputType GetInputTypeForHandle(InputHandle_t inputHandle)
	{
		return k_ESteamInputType_Unknown;
	}

	InputHandle_t GetControllerForGamepadIndex(int nIndex)
	{
		return NULL;
	}

	int GetGamepadIndexForController(InputHandle_t ulinputHandle)
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

	EInputActionOrigin GetActionOriginFromXboxOrigin(InputHandle_t inputHandle, EXboxOrigin eOrigin)
	{
		return k_EInputActionOrigin_None;
	}

	EInputActionOrigin TranslateActionOrigin(ESteamInputType eDestinationInputType, EInputActionOrigin eSourceOrigin)
	{
		return k_EInputActionOrigin_None;
	}
};