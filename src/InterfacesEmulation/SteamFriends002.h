#pragma once
#include "../public SDK/ISteamFriends002.h"
#include "../Bridge.h"

class SteamFriendsIn002 : public ISteamFriends002
{
public:
	const char* GetPersonaName()
	{
		return Steam_Config::Username;
	}
	void SetPersonaName(const char* pchPersonaName)
	{
		strcpy(Steam_Config::Username, pchPersonaName);
		return;
	}

	EPersonaState GetPersonaState()
	{
		return k_EPersonaStateOffline;
	}
	void SetPersonaState(EPersonaState ePersonaState)
	{
		return;
	}

	int GetFriendCount(EFriendFlags iFriendFlags)
	{
		return NULL;
	}
	CSteamID GetFriendByIndex(int iFriend, EFriendFlags iFriendFlags)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}

	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend)
	{
		return k_EFriendRelationshipNone;
	}
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend)
	{
		return k_EPersonaStateOffline;	// Offline is cool :D
	}
	const char* GetFriendPersonaName(CSteamID steamIDFriend)
	{
		return "";
	}

	void SetFriendRegValue(CSteamID steamIDFriend, const char* pchKey, const char* pchValue)
	{
		return;
	}
	const char* GetFriendRegValue(CSteamID steamIDFriend, const char* pchKey)
	{
		return "";
	}

	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64* pulGameID, uint32* punGameIP, uint16* pusGamePort, uint16* pusQueryPort)
	{
		return false;
	}

	const char* GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
	{
		return "";
	}

	bool AddFriend(CSteamID steamIDFriend)
	{
		return true;
	}
	bool RemoveFriend(CSteamID steamIDFriend)
	{
		return true;
	}

	bool HasFriend(CSteamID steamIDFriend, EFriendFlags iFriendFlags)
	{
		return false;
	}

	HSteamCall AddFriendByName(const char* pchEmailOrAccountName)
	{
		return NULL;
	}

	bool InviteFriendByEmail(const char* emailAddr)
	{
		return false;
	}

	int GetChatMessage(CSteamID steamIDFriend, int iChatID, void* pvData, int cubData, EChatEntryType* peFriendMsgType)
	{
		return NULL;
	}

	bool SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const void* pvMsgBody, int cubMsgBody)
	{
		return false;
	}

	OBSOLETE_FUNCTION int GetChatIDOfChatHistoryStart(CSteamID steamIDFriend)
	{
		return NULL;
	}
	OBSOLETE_FUNCTION void SetChatHistoryStart(CSteamID steamIDFriend, int iChatID)
	{
		return;
	}
	void ClearChatHistory(CSteamID steamIDFriend)
	{
		return;
	}

	int GetClanCount()
	{
		return 0;
	}
	CSteamID GetClanByIndex(int iClan)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	const char* GetClanName(CSteamID steamIDClan)
	{
		return "";
	}

	bool InviteFriendToClan(CSteamID steamIDfriend, CSteamID steamIDclan)
	{
		return false;
	}
	bool AcknowledgeInviteToClan(CSteamID steamID, bool)
	{
		return false;
	}

	int GetFriendCountFromSource(CSteamID steamIDSource)
	{
		return NULL;
	}
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int iFriend)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
};
