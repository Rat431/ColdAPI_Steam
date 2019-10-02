#pragma once
#include "../public SDK/ISteamFriends008.h"
#include "../Bridge.h"

class SteamFriendsIn008 : public ISteamFriends008
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

	int GetFriendCount(int eFriendFlags)
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

	bool HasFriend(CSteamID steamIDFriend, int eFriendFlags)
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
	uint32 GetUserRestrictions()
	{
		return k_nUserRestrictionNone; // <----- We don't wanna this nah? :D
	}
};
