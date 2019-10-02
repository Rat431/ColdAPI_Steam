#pragma once
#include "../public SDK/ISteamFriends010.h"
#include "../Bridge.h"

class SteamFriendsIn010 : public ISteamFriends010
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

	int GetFriendCount(int iFriendFlags)
	{
		return NULL;
	}

	CSteamID GetFriendByIndex(int iFriend, int iFriendFlags)
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

	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t* pFriendGameInfo)
	{
		return false;
	}
	const char* GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
	{
		return "";
	}

	bool HasFriend(CSteamID steamIDFriend, int iFriendFlags)
	{
		return false;
	}

	int GetClanCount()
	{
		return NULL;
	}
	CSteamID GetClanByIndex(int iClan)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	const char* GetClanName(CSteamID steamIDClan)
	{
		return "";
	}
	const char* GetClanTag(CSteamID steamIDClan)
	{
		return "";
	}

	bool GetClanActivityCounts(CSteamID steamID, int* pnOnline, int* pnInGame, int* pnChatting)
	{
		return false;
	}
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int nIds)
	{
		return NULL;
	}

	int GetFriendCountFromSource(CSteamID steamIDSource)
	{
		return NULL;
	}
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int iFriend)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}

	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource)
	{
		return false;
	}

	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking)
	{
		return;
	}

	void ActivateGameOverlay(const char* pchDialog)
	{
		return;
	}

	void ActivateGameOverlayToUser(const char* pchDialog, CSteamID steamID)
	{
		return;
	}

	void ActivateGameOverlayToWebPage(const char* pchURL)
	{
		return;
	}

	void ActivateGameOverlayToStore(AppId_t nAppID)
	{
		return;
	}

	void SetPlayedWith(CSteamID steamIDUserPlayedWith)
	{
		return;
	}

	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby)
	{
		return;
	}

	int GetSmallFriendAvatar(CSteamID steamIDFriend)
	{
		return NULL;
	}

	int GetMediumFriendAvatar(CSteamID steamIDFriend)
	{
		return NULL;
	}

	int GetLargeFriendAvatar(CSteamID steamIDFriend)
	{
		return NULL;
	}

	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly)
	{
		return false;
	}

	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan)
	{
		return NULL;
	}

	CSteamID GetClanOwner(CSteamID steamIDClan)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	int GetClanOfficerCount(CSteamID steamIDClan)
	{
		return NULL;
	}
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int iOfficer)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	EUserRestriction GetUserRestrictions()
	{
		return k_nUserRestrictionNone; // <----- We don't wanna this nah? :D
	}

	bool SetRichPresence(const char* pchKey, const char* pchValue)
	{
		return true;
	}
	void ClearRichPresence()
	{
		return;
	}
	const char* GetFriendRichPresence(CSteamID steamIDFriend, const char* pchKey)
	{
		return "";
	}
	int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend)
	{
		return NULL;
	}
	const char* GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey)
	{
		return "";
	}

	bool InviteUserToGame(CSteamID steamIDFriend, const char* pchConnectString)
	{
		return false;
	}

	int GetCoplayFriendCount()
	{
		return NULL;
	}
	CSteamID GetCoplayFriend(int iCoplayFriend)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	int GetFriendCoplayTime(CSteamID steamIDFriend)
	{
		return NULL;
	}
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend)
	{
		return NULL;
	}
	SteamAPICall_t JoinClanChatRoom(CSteamID groupID)
	{
		return NULL;
	}
	bool LeaveClanChatRoom(CSteamID groupID)
	{
		return false;
	}
	int GetClanChatMemberCount(CSteamID groupID)
	{
		return NULL;
	}
	CSteamID GetChatMemberByIndex(CSteamID groupID, int iIndex)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	bool SendClanChatMessage(CSteamID groupID, const char* cszMessage)
	{
		return false;
	}
	int GetClanChatMessage(CSteamID groupID, int iChatID, void* pvData, int cubData, EChatEntryType* peChatEntryType, CSteamID* pSteamIDChatter)
	{
		return NULL;
	}
	bool IsClanChatAdmin(CSteamID groupID, CSteamID userID)
	{
		return false;
	}
	bool IsClanChatWindowOpenInSteam(CSteamID groupID)
	{
		return false;
	}
	bool OpenClanChatWindowInSteam(CSteamID groupID)
	{
		return false;
	}
	bool CloseClanChatWindowInSteam(CSteamID groupID)
	{
		return false;
	}
	bool SetListenForFriendsMessages(bool bListen)
	{
		return false;
	}
	bool ReplyToFriendMessage(CSteamID friendID, const char* cszMessage)
	{
		return false;
	}
	int GetFriendMessage(CSteamID friendID, int iChatID, void* pvData, int cubData, EChatEntryType* peChatEntryType)
	{
		return NULL;
	}
};
