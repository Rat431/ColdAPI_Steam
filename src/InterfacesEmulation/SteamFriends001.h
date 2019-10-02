#pragma once
#include "../public SDK/ISteamFriends001.h"
#include "../Bridge.h"

class SteamFriendsIn001 : public ISteamFriends001
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

	bool AddFriend(CSteamID steamIDFriend)
	{
		return true;
	}
	bool RemoveFriend(CSteamID steamIDFriend)
	{
		return true;
	}
	bool HasFriend(CSteamID steamIDFriend)
	{
		return false;
	}

	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend)
	{
		return k_EFriendRelationshipNone;
	}
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend)
	{
		return k_EPersonaStateOffline;	// Offline is cool :D
	}

	bool Deprecated_GetFriendGamePlayed(CSteamID steamIDFriend, int32* pnGameID, uint32* punGameIP, uint16* pusGamePort)
	{
		return false;
	}

	const char* GetFriendPersonaName(CSteamID steamIDFriend)
	{
		return "";
	}

	HSteamCall AddFriendByName(const char* pchEmailOrAccountName)
	{
		return NULL;
	}

	int GetFriendCount()
	{
		return NULL;
	}
	CSteamID GetFriendByIndex(int iFriend)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}

	void SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const char* pchMsgBody)
	{
		return;
	}

	void SetFriendRegValue(CSteamID steamIDFriend, const char* pchKey, const char* pchValue)
	{
		return;
	}
	const char* GetFriendRegValue(CSteamID steamIDFriend, const char* pchKey)
	{
		return "";
	}

	const char* GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
	{
		return "";
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

	HSteamCall InviteFriendByEmail(const char* pchEmailOrAccountName)
	{
		return NULL;
	}

	uint32 GetBlockedFriendCount()
	{
		return NULL;
	}

	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64* pulGameID, uint32* punGameIP, uint16* pusGamePort)
	{
		return false;
	}
	bool GetFriendGamePlayed2(CSteamID steamDIFriend, uint64* pulGameID, uint32* punGameIP, uint16* pusGamePort, uint16* pusQueryPort)
	{
		return false;
	}
};
