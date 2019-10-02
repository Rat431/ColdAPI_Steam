#pragma once
#include "../public SDK/ISteamHTMLSurface005.h"


class SteamHTMLSurfaceIn005 : public ISteamHTMLSurface005
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

	SteamAPICall_t CreateBrowser(const char* pchUserAgent, const char* pchUserCSS)
	{
		return NULL;
	}

	void RemoveBrowser(HHTMLBrowser unBrowserHandle)
	{
		return;
	}

	void LoadURL(HHTMLBrowser unBrowserHandle, const char* pchURL, const char* pchPostData)
	{
		return;
	}
	
	void SetSize(HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight)
	{
		return;
	}

	void StopLoad(HHTMLBrowser unBrowserHandle)
	{
		return;
	}
	void Reload(HHTMLBrowser unBrowserHandle)
	{
		return;
	}
	void GoBack(HHTMLBrowser unBrowserHandle)
	{
		return;
	}
	void GoForward(HHTMLBrowser unBrowserHandle)
	{
		return;
	}

	void AddHeader(HHTMLBrowser unBrowserHandle, const char* pchKey, const char* pchValue)
	{
		return;
	}
	void ExecuteJavascript(HHTMLBrowser unBrowserHandle, const char* pchScript)
	{
		return;
	}

	void MouseUp(HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton)
	{
		return;
	}
	void MouseDown(HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton)
	{
		return;
	}
	void MouseDoubleClick(HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton)
	{
		return;
	}
	void MouseMove(HHTMLBrowser unBrowserHandle, int x, int y)
	{
		return;
	}
	void MouseWheel(HHTMLBrowser unBrowserHandle, int32 nDelta)
	{
		return;
	}

	void KeyDown(HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers, bool bIsSystemKey = false)
	{
		return;
	}
	void KeyUp(HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers)
	{
		return;
	}
	void KeyChar(HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar, EHTMLKeyModifiers eHTMLKeyModifiers)
	{
		return;
	}

	void SetHorizontalScroll(HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll)
	{
		return;
	}
	void SetVerticalScroll(HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll)
	{
		return;
	}

	void SetKeyFocus(HHTMLBrowser unBrowserHandle, bool bHasKeyFocus)
	{
		return;
	}

	void ViewSource(HHTMLBrowser unBrowserHandle)
	{
		return;
	}
	void CopyToClipboard(HHTMLBrowser unBrowserHandle)
	{
		return;
	}
	void PasteFromClipboard(HHTMLBrowser unBrowserHandle)
	{
		return;
	}

	void Find(HHTMLBrowser unBrowserHandle, const char* pchSearchStr, bool bCurrentlyInFind, bool bReverse)
	{
		return;
	}
	void StopFind(HHTMLBrowser unBrowserHandle)
	{
		return;
	}

	void GetLinkAtPosition(HHTMLBrowser unBrowserHandle, int x, int y)
	{
		return;
	}

	void SetCookie(const char* pchHostname, const char* pchKey, const char* pchValue, const char* pchPath = "/", RTime32 nExpires = 0, bool bSecure = false, bool bHTTPOnly = false)
	{
		return;
	}

	void SetPageScaleFactor(HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY)
	{
		return;
	}

	void SetBackgroundMode(HHTMLBrowser unBrowserHandle, bool bBackgroundMode)
	{
		return;
	}

	void SetDPIScalingFactor(HHTMLBrowser unBrowserHandle, float flDPIScaling)
	{
		return;
	}

	void OpenDeveloperTools(HHTMLBrowser unBrowserHandle)
	{
		return;
	}

	void AllowStartRequest(HHTMLBrowser unBrowserHandle, bool bAllowed)
	{
		return;
	}

	void JSDialogResponse(HHTMLBrowser unBrowserHandle, bool bResult)
	{
		return;
	}

	void FileLoadDialogResponse(HHTMLBrowser unBrowserHandle, const char** pchSelectedFiles)
	{
		return;
	}
};