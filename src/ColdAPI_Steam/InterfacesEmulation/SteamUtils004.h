#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUtils004.h"

class SteamUtilsIn004 : public ISteamUtils004
{
public:
	uint32 GetSecondsSinceAppActive()
	{
		return 10;
	}
	uint32 GetSecondsSinceComputerActive()
	{
		return 10;
	}

	EUniverse GetConnectedUniverse()
	{
		return k_EUniverseInternal;
	}

	RTime32 GetServerRealTime()
	{
		// Return fake time milliseconds

		return (uint32)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	const char* GetIPCountry()
	{
		return ColdAPI_General::GetCountryFromLanguage(Steam_Config::Language);
	}

	bool GetImageSize(int iImage, uint32* pnWidth, uint32* pnHeight)
	{
		return false;
	}

	bool GetImageRGBA(int iImage, uint8* pubDest, int nDestBufferSize)
	{
		return false;
	}

	bool GetCSERIPPort(uint32* unIP, uint16* usPort)
	{
		return false;
	}

	uint8 GetCurrentBatteryPower()
	{
		return 10;
	}

	uint32 GetAppID()
	{
		return Steam_Config::AppId;
	}

	void SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
	{
		ColdAPI_General::SetOverlayNotification(eNotificationPosition);
	}

	bool IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool* pbFailed)
	{
		return true;
	}
	ESteamAPICallFailure GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
	{
		return k_ESteamAPICallFailureNone;
	}
	bool GetAPICallResult(SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
	{
		return true;
	}

	void RunFrame()
	{
		return;
	}

	uint32 GetIPCCallCount()
	{
		return 10;
	}

	void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
	{
		return;
	}

	bool IsOverlayEnabled()
	{
		return ColdAPI_General::IsOverlayNeededOrEnabled();
	}
};