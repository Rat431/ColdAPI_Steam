#pragma once
#include "../public SDK/ISteamScreenshots001.h"

class SteamScreenshotsIn001 : public ISteamScreenshots001
{
public:
	ScreenshotHandle WriteScreenshot(void* pubRGB, uint32 cubRGB, int nWidth, int nHeight)
	{
		return INVALID_SCREENSHOT_HANDLE;
	}

	ScreenshotHandle AddScreenshotToLibrary(const char* pchFilename, const char* pchThumbnailFilename, int nWidth, int nHeight)
	{
		return INVALID_SCREENSHOT_HANDLE;
	}

	void TriggerScreenshot()
	{
		return;
	}

	void HookScreenshots(bool bHook)
	{
		return;
	}

	bool SetLocation(ScreenshotHandle hScreenshot, const char* pchLocation)
	{
		return false;
	}

	bool TagUser(ScreenshotHandle hScreenshot, CSteamID steamID)
	{
		return false;
	}
};