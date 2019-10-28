#pragma once
#include "../public SDK/ISteamUnifiedMessages001.h"

class SteamUnifiedMessagesIn001 : public ISteamUnifiedMessages001
{
public:
	ClientUnifiedMessageHandle SendMethod(const char* pchServiceMethod, const void* pRequestBuffer, uint32 unRequestBufferSize, uint64 unContext)
	{
		return NULL;
	}

	bool GetMethodResponseInfo(ClientUnifiedMessageHandle hHandle, uint32* punResponseSize, EResult* peResult)
	{
		return false;
	}

	bool GetMethodResponseData(ClientUnifiedMessageHandle hHandle, void* pResponseBuffer, uint32 unResponseBufferSize, bool bAutoRelease)
	{
		return false;
	}

	bool ReleaseMethod(ClientUnifiedMessageHandle hHandle)
	{
		return false;
	}

	bool SendNotification(const char* pchServiceNotification, const void* pNotificationBuffer, uint32 unNotificationBufferSize)
	{
		return false;
	}
};