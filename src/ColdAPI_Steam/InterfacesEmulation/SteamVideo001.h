#pragma once
#include "../public SDK/ISteamVideo001.h"

class SteamVideoIn001 : public ISteamVideo001
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
};