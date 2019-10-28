//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef ISTEAMMATCHMAKING001_H
#define ISTEAMMATCHMAKING001_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "MatchmakingCommon.h"


//-----------------------------------------------------------------------------
// Purpose: Functions for match making services for clients to get to favorites
//-----------------------------------------------------------------------------
abstract_class ISteamMatchmaking001
{
public:
	virtual int GetFavoriteGameCount() = 0;
	
	// Obsolete. Use the ...2 versions of these functions, which take separate connection and query ports.
	virtual bool GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer ) = 0;
	virtual int AddFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ) =0;
    virtual bool RemoveFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags ) = 0;


	// returns the details of the game server
	// iGame is of range [0,iGame)
	virtual bool GetFavoriteGame2( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer ) = 0;

    // returns the new index of the game
	virtual int AddFavoriteGame2( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ) =0;
	
	// removes the game; returns true if one was removed
    virtual bool RemoveFavoriteGame2( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags ) = 0;

	///////
	// Game lobby functions

	// Get a list of relevant lobbies
	virtual void RequestLobbyList( uint64 ulGameID, MatchMakingKeyValuePair_t *pFilters, uint32 nFilters ) = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetLobbyByIndex, int, iLobby) /*virtual CSteamID GetLobbyByIndex( int iLobby ) = 0;*/
	// Create a lobby - you'll get the SteamID of it on success
	virtual void CreateLobby( uint64 ulGameID, bool bPrivate ) = 0;
	// Join a lobby
	virtual void JoinLobby( CSteamID steamIDLobby ) = 0;
	// Leave a lobby
	virtual void LeaveLobby( CSteamID steamIDLobby ) = 0;
	// Invite someone to the lobby
	virtual bool InviteUserToLobby( CSteamID steamIDLobby, CSteamID steamIDInvitee ) = 0;
	// List users in this lobby
	virtual int GetNumLobbyMembers( CSteamID steamIDLobby ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetLobbyMemberByIndex, CSteamID, steamIDLobby, int, iMember) /*virtual CSteamID GetLobbyMemberByIndex( CSteamID steamIDLobby, int iMember ) = 0;*/
	// Get data associated with this lobby
	virtual const char *GetLobbyData( CSteamID SteamIDLobby, const char *pchKey ) = 0;
	// Update lobby data (Admin only)
	virtual void SetLobbyData( CSteamID steamIDLobby, const char *pchKey, const char *pchValue ) = 0;
	// Get per-user data for someone in this lobby
	virtual const char *GetLobbyMemberData( CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey ) = 0;
	// Update user data (for you only)
	virtual void SetLobbyMemberData( CSteamID steamIDLobby, const char *pchKey, const char *pchValue ) = 0;
	// change the lobby Admin (Admin only)
	virtual void ChangeLobbyAdmin( CSteamID steamIDLobby, CSteamID steamIDNewAdmin ) = 0;
	// Send a chat message to the lobby
	virtual bool SendLobbyChatMsg( CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody ) = 0;
	// Get a chat message entry
	virtual int GetLobbyChatEntry( CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType ) = 0;

	// this was added in an updated version apparently
	//

	// Refreshes metadata for a lobby you're not necessarily in right now
	// you never do this for lobbies you're a member of, only if your
	// this will send down all the metadata associated with a lobby
	// this is an asynchronous call
	// returns false if the local user is not connected to the Steam servers
	// restart are returned by a LobbyDataUpdate_t callback
	virtual bool RequestLobbyData( CSteamID steamIDLobby ) = 0;
};



#endif // ISTEAMMATCHMAKING001_H
