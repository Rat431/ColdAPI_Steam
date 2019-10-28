#pragma once
#include "../Bridge.h"
#include "../public SDK/ISteamUser005.h"


class SteamUserIn005 : public ISteamUser005
{
public:
	HSteamUser GetHSteamUser()
	{
		return NULL;
	}

	void LogOn(CSteamID steamID)
	{
		return;
	}
	void LogOff()
	{
		return;
	}

	bool BLoggedOn()
	{
		return Steam_Config::OnlineMod;
	}

	ELogonState GetLogonState()
	{
		return k_ELogonStateNotLoggedOn;
	}
	bool BConnected()
	{
		return Steam_Config::OnlineMod;
	}

	CSteamID GetSteamID()
	{
		return CSteamID(Steam_Config::UserID);
	}

	bool IsVACBanned(EVACBan eVACBan)
	{
		return false;
	}

	bool RequireShowVACBannedMessage(EVACBan eVACBan)
	{
		return false;
	}

	void AcknowledgeVACBanning(EVACBan eVACBan)
	{
		return;
	}

	void SetSteam2Ticket(uint8* pubTicket, int cubTicket)
	{
		return;
	}
	OBSOLETE_FUNCTION void AddServerNetAddress(uint32 unIP, uint16 unPort)
	{
		return;
	}

	bool SetEmail(const char* pchEmail)
	{
		return true;
	}


	bool SetRegistryString(ERegistrySubTree eRegistrySubTree, const char* pchKey, const char* pchValue)
	{
		return false;
	}
	bool GetRegistryString(ERegistrySubTree eRegistrySubTree, const char* pchKey, char* pchValue, int cbValue)
	{
		return false;
	}
	bool SetRegistryInt(ERegistrySubTree eRegistrySubTree, const char* pchKey, int iValue)
	{
		return false;
	}
	bool GetRegistryInt(ERegistrySubTree eRegistrySubTree, const char* pchKey, int* piValue)
	{
		return false;
	}

	int InitiateGameConnection(void* pBlob, int cbMaxBlob, CSteamID steamID, CGameID nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure)
	{
		return cbMaxBlob;
	}

	void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
	{
		return;
	}

	void SetSelfAsPrimaryChatDestination()
	{
		return;
	}
	bool IsPrimaryChatDestination()
	{
		return true;
	}

	void RequestLegacyCDKey(AppId_t iAppID)
	{
		return;
	}

	bool SendGuestPassByEmail(const char* pchEmailAccount, GID_t gidGuestPassID, bool bResending)
	{
		return false;
	}
	bool SendGuestPassByAccountID(uint32 uAccountID, GID_t gidGuestPassID, bool bResending)
	{
		return false;
	}

	bool AckGuestPass(const char* pchGuestPassCode)
	{
		return false;
	}
	bool RedeemGuestPass(const char* pchGuestPassCode)
	{
		return false;
	}

	uint32 GetGuestPassToGiveCount()
	{
		return NULL;
	}
	uint32 GetGuestPassToRedeemCount()
	{
		return NULL;
	}
	uint32 GetGuestPassLastUpdateTime()
	{
		return NULL;
	}

	bool GetGuestPassToGiveInfo(uint32 nPassIndex, GID_t* pgidGuestPassID, PackageId_t* pnPackageID, RTime32* pRTime32Created, RTime32* pRTime32Expiration, RTime32* pRTime32Sent, RTime32* pRTime32Redeemed, char* pchRecipientAddress, int cRecipientAddressSize)
	{
		return false;
	}
	bool GetGuestPassToRedeemInfo(uint32 nPassIndex, GID_t* pgidGuestPassID, PackageId_t* pnPackageID, RTime32* pRTime32Created, RTime32* pRTime32Expiration, RTime32* pRTime32Sent, RTime32* pRTime32Redeemed)
	{
		return false;
	}
	bool GetGuestPassToRedeemSenderAddress(uint32 nPassIndex, char* pchSenderAddress, int cSenderAddressSize)
	{
		return false;
	}
	bool GetGuestPassToRedeemSenderName(uint32 nPassIndex, char* pchSenderName, int cSenderNameSize)
	{
		return false;
	}
	void AcknowledgeMessageByGID(const char* pchMessageGID)
	{
		return;
	}

	bool SetLanguage(const char* pchLanguage)
	{
		return (lstrcpyA(Steam_Config::Language, pchLanguage) != NULL);	// Return boolean value (:
	}

	void TrackAppUsageEvent(CGameID gameID, EAppUsageEvent eAppUsageEvent, const char* pchExtraInfo = "")
	{
		return;
	}

	void SetAccountName(const char* pchAccountName)
	{
		return;
	}
	void SetPassword(const char* pchPassword)
	{
		return;
	}

	void SetAccountCreationTime(RTime32 rtime32Time)
	{
		return;
	}
};
