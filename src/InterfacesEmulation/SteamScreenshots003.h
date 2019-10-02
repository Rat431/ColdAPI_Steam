#pragma once
#include "../public SDK/ISteamScreenshots003.h"

class SteamScreenshotsIn003 : public ISteamScreenshots003
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

	bool TagPublishedFile(ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileID)
	{
		return false;
	}

	bool IsScreenshotsHooked()
	{
		return false;
	}

	ScreenshotHandle AddVRScreenshotToLibrary(int eType, const char* pchFilename, const char* pchVRFilename)
	{
		return INVALID_SCREENSHOT_HANDLE;
	}
};