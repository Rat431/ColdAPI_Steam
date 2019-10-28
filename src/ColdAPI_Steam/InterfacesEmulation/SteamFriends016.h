#pragma once
#include "../public SDK/ISteamFriends016.h"
#include "../Bridge.h"

class SteamFriendsIn016 : public ISteamFriends016
{
public:
	const char* GetPersonaName()
	{
		return Steam_Config::Username;
	}
	SteamAPICall_t SetPersonaName(const char* pchPersonaName)
	{
		strcpy(Steam_Config::Username, pchPersonaName);
		return NULL;
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
	bool GetFriendGamePlayed(CSteamID steamID, FriendGameInfo_t* pGamePlayInfo)
	{
		return false;
	}
	const char* GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
	{
		return "";
	}
	int GetFriendSteamLevel(CSteamID steamIDFriend)
	{
		return 10;	// <--- We like 10 :D
	}
	const char* GetPlayerNickname(CSteamID steamIDPlayer)
	{
		return "";
	}
	int GetFriendsGroupCount()
	{
		return NULL;
	}
	int16 GetFriendsGroupIDByIndex(int32)
	{
		return NULL;
	}
	const char* GetFriendsGroupName(int16)
	{
		return "";
	}
	unknown_ret GetFriendsGroupMembersCount(int16)
	{
		return NULL;
	}
	void GetFriendsGroupMembersList(FriendsGroupID_t friendsGroupID, CSteamID* pOutSteamIDMembers, int nMembersCount)
	{
		nMembersCount = NULL;
		return;
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
	void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag)
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
	uint32 GetUserRestrictions()
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
	void RequestFriendRichPresence(CSteamID steamIDFriend)
	{
		return;
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
	SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan)
	{
		return NULL;
	}
	bool LeaveClanChatRoom(CSteamID steamIDClan)
	{
		return false;
	}
	int GetClanChatMemberCount(CSteamID steamIDClan)
	{
		return NULL;
	}
	CSteamID GetChatMemberByIndex(CSteamID steamIDClan, int iUser)
	{
		return CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeIndividual);
	}
	bool SendClanChatMessage(CSteamID steamIDClanChat, const char* pchText)
	{
		return false;
	}
	int GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void* prgchText, int cchTextMax, EChatEntryType* peChatEntryType, CSteamID* pSteamIDChatter)
	{
		return NULL;
	}
	bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser)
	{
		return false;
	}
	bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat)
	{
		return false;
	}
	bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat)
	{
		return false;
	}
	bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat)
	{
		return false;
	}
	bool SetListenForFriendsMessages(bool bInterceptEnabled)
	{
		return false;
	}
	bool ReplyToFriendMessage(CSteamID steamIDFriend, const char* pchMsgToSend)
	{
		return false;
	}
	int GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void* pvData, int cubData, EChatEntryType* peChatEntryType)
	{
		return NULL;
	}
	SteamAPICall_t GetFollowerCount(CSteamID steamID)
	{
		return NULL;
	}
	SteamAPICall_t IsFollowing(CSteamID steamID)
	{
		return NULL;
	}
	SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex)
	{
		return NULL;
	}

	bool IsClanPublic(CSteamID steamIDClan)
	{
		return false;
	}
	bool IsClanOfficialGameGroup(CSteamID steamIDClan)
	{
		return false;
	}

	int GetNumChatsWithUnreadPriorityMessages()
	{
		return NULL;
	}
};