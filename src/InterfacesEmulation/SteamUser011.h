#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUser011.h"


class SteamUserIn011 : public ISteamUser011
{
public:
	HSteamUser GetHSteamUser()
	{
		return NULL;
	}

	bool BLoggedOn()
	{
		return Steam_Config::OnlineMod;
	}

	CSteamID GetSteamID()
	{
		return CSteamID(Steam_Config::UserID);
	}

	int InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
	{
		return cbMaxAuthBlob;
	}

	void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	void TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char* pchExtraInfo = "")
	{
		return;
	}

	bool GetUserDataFolder(char* pchBuffer, int cubBuffer)
	{
		const char* mydir = ColdAPI_Storage::GetStorageDirectory();

		if (pchBuffer != NULL && pchBuffer > NULL && cubBuffer >= NULL) {
			std::memcpy(pchBuffer, mydir, cubBuffer);
			return true;
		}
		return false;
	}

	void StartVoiceRecording()
	{
		return;
	}

	void StopVoiceRecording()
	{
		return;
	}

	EVoiceResult GetCompressedVoice(void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten)
	{
		return k_EVoiceResultNoData;
	}

	EVoiceResult DecompressVoice(void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten)
	{
		return k_EVoiceResultNoData;
	}
};