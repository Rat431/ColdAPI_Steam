#pragma once
#include "../public SDK/ISteamFriends004.h"
#include "../Bridge.h"

class SteamFriendsIn004 : public ISteamFriends004
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

	int GetFriendAvatar(CSteamID steamIDFriend, int eAvatarSize)
	{
		return NULL;
	}

	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64* pulGameID, uint32* punGameIP, uint16* pusGamePort, uint16* pusQueryPort)
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
};
