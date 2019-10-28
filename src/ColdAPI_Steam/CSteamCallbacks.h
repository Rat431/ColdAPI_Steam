#pragma once
#include "Bridge.h"

class CCallbackBase
{
public:
	CCallbackBase() { m_nCallbackFlags = 0; m_iCallback = 0; }
	// don't add a virtual destructor because we export this binary interface across dll's
	virtual void Run(void* pvParam) = 0;
	virtual void Run(void* pvParam, bool bIOFailure, unsigned long long hSteamAPICall) = 0;
	int GetICallback() { return m_iCallback; }
	// Change current callback ID.
	void SetICallback(int b) { m_iCallback = b; }	
	virtual int GetCallbackSizeBytes() = 0;

protected:
	enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
	unsigned char m_nCallbackFlags;
	int m_iCallback;
	friend class CCallbackMgr;

private:
	CCallbackBase(const CCallbackBase&);
	CCallbackBase& operator=(const CCallbackBase&);
};

typedef struct
{
	void* Data;
	int32_t Size;
	int32_t Type;
	uint64_t Call;
} CSteamAPIResult_t;
struct CCallbackMsg_t
{
	int32_t m_hSteamUser;
	int m_iCallback;
	unsigned char* m_pubParam;
	int m_cubParam;
};
struct CCSteamAPICallCompleted_t
{
	enum { k_iCallback = 700 + 3 };
	uint64_t m_hAsyncCall;
	int m_iCallback;
	uint32_t m_cubParam;
};

namespace SteamCallback
{
	void RunCallbacks();
	void RegisterCallback(CCallbackBase* handler, int callback);
	void RegisterCallResult(CCallbackBase* result, uint64_t call);
	void UnregisterCallback(CCallbackBase* handler, int callback);
	void UnregisterCallResult(CCallbackBase* result, uint64_t call);
	uint64_t RegisterCall(bool MarkActive);
	void CreateNewRequest(void* data, int size, int type, uint64_t call);
	const char* GetCallbackName(int ID);

	bool CCGetCallBack(void* pCallbackMsg);
	bool CCGetAPICallResult(uint64_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed);
	void FreeCB();
}