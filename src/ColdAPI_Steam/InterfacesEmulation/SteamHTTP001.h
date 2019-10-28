#pragma once
#include "../public SDK/ISteamHTTP001.h"

class SteamHTTPIn001 : public ISteamHTTP001
{
public:
	HTTPRequestHandle CreateHTTPRequest(EHTTPMethod eHTTPRequestMethod, const char* pchAbsoluteURL)
	{
		return NULL;
	}
	bool SetHTTPRequestContextValue(HTTPRequestHandle hRequest, uint64 ulContextValue)
	{
		return false;
	}

	bool SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, uint32 unTimeoutSeconds)
	{
		return false;
	}

	bool SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue)
	{
		return false;
	}

	bool SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue)
	{
		return false;
	}

	bool SendHTTPRequest(HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle)
	{
		return false;
	}

	bool DeferHTTPRequest(HTTPRequestHandle hRequest)
	{
		return false;
	}

	bool PrioritizeHTTPRequest(HTTPRequestHandle hRequest)
	{
		return false;
	}

	bool GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char* pchHeaderName, uint32* unResponseHeaderSize)
	{
		return false;
	}

	bool GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, uint8* pHeaderValueBuffer, uint32 unBufferSize)
	{
		return false;
	}

	bool GetHTTPResponseBodySize(HTTPRequestHandle hRequest, uint32* unBodySize)
	{
		return false;
	}

	bool GetHTTPResponseBodyData(HTTPRequestHandle hRequest, uint8* pBodyDataBuffer, uint32 unBufferSize)
	{
		return false;
	}

	bool ReleaseHTTPRequest(HTTPRequestHandle hRequest)
	{
		return false;
	}

	bool GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float* pflPercentOut)
	{
		return false;
	}

	bool SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char* pchContentType, uint8* pubBody, uint32 unBodyLen)
	{
		return false;
	}
};