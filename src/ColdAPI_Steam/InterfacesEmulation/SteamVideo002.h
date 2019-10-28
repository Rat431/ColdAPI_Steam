#pragma once
#include "../public SDK/ISteamVideo002.h"

class SteamVideoIn002 : public ISteamVideo002
{
public:
	void GetVideoURL(AppId_t unVideoAppID)
	{
		return;
	}

	bool IsBroadcasting(int* pnNumViewers)
	{
		return false;
	}

	void GetOPFSettings(AppId_t unVideoAppID)
	{
		return;
	}
	bool GetOPFStringForApp(AppId_t unVideoAppID, char* pchBuffer, int32* pnBufferSize)
	{
		return false;
	}
};