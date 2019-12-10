#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUser018.h"
class SteamUserIn018 : public ISteamUser018
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

	EVoiceResult GetAvailableVoice(uint32* pcbCompressed, uint32* pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
	{
		return k_EVoiceResultOK;
	}

	EVoiceResult GetVoice(bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32* nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
	{
		return k_EVoiceResultOK;
	}

	EVoiceResult DecompressVoice(const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, uint32 nDesiredSampleRate)
	{
		return k_EVoiceResultOK;
	}

	uint32 GetVoiceOptimalSampleRate()
	{
		return NULL;
	}

	HAuthTicket GetAuthSessionTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket)
	{
		return NULL;
	}

	EBeginAuthSessionResult BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, CSteamID steamID)
	{
		return k_EBeginAuthSessionResultOK;
	}

	void EndAuthSession(CSteamID steamID)
	{
		return;
	}

	void CancelAuthTicket(HAuthTicket hAuthTicket)
	{
		return;
	}

	EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
	{
		return k_EUserHasLicenseResultHasLicense;
	}

	bool BIsBehindNAT()
	{
		return true;
	}

	void AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	
	SteamAPICall_t RequestEncryptedAppTicket(void* pDataToInclude, int cbDataToInclude)
	{

		// Create a new fake ticket
		if (cbDataToInclude < NULL)
			return NULL;
		if (pDataToInclude <= NULL)
			return NULL;

		PublicSafe.lock();

		std::memset(TicketData, 0, sizeof(TicketData));
		std::memcpy(TicketData, pDataToInclude, min(cbDataToInclude, sizeof(TicketData)));

		auto RequestID = SteamCallback::RegisterCall(true);
		auto Response = new EncryptedAppTicketResponse_t();

		Response->m_eResult = k_EResultOK;
		SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);

		PublicSafe.unlock();

		return RequestID;
	}

	bool GetEncryptedAppTicket(void* pTicket, int cbMaxTicket, uint32 * pcbTicket)
	{
		if (pTicket <= NULL)
			return false;
		if (cbMaxTicket < NULL)
			return false;

		PublicSafe.lock();

		std::memcpy(pTicket, TicketData, min(cbMaxTicket, (unsigned int)sizeof(TicketData)));
		if (pcbTicket != NULL && pcbTicket > NULL)
			*pcbTicket = sizeof(TicketData);

		PublicSafe.unlock();

		return true;
	}

	int GetGameBadgeLevel(int nSeries, bool bFoil)
	{
		return NULL;
	}

	int GetPlayerSteamLevel()
	{
		return 10;
	}

	SteamAPICall_t RequestStoreAuthURL(const char* pchRedirectURL)
	{
		return NULL;
	}
};