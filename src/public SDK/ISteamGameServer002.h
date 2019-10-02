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

#ifndef ISTEAMGAMESERVER002_H
#define ISTEAMGAMESERVER002_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "GameServerCommon.h"
#include "UserCommon.h"

//-----------------------------------------------------------------------------
// Purpose: Functions for authenticating users via Steam to play on a game server
//-----------------------------------------------------------------------------
abstract_class ISteamGameServer002
{
public:
	// connection functions
	virtual void LogOn() = 0;
	virtual void LogOff() = 0;
	virtual bool BLoggedOn() = 0;

	// user authentication functions
	virtual void SetSpawnCount( uint32 ucSpawn ) = 0;

	virtual bool GetSteam2GetEncryptionKeyToSendToNewClient( void *pvEncryptionKey, uint32 *pcbEncryptionKey, uint32 cbMaxEncryptionKey ) = 0;

	// the IP address and port should be in host order, i.e 127.0.0.1 == 0x7f000001
	// Both Steam2 and Steam3 authentication
	virtual bool SendSteam2UserConnect(  uint32 unUserID, const void *pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie ) = 0;

	// the IP address should be in host order, i.e 127.0.0.1 == 0x7f000001
	// Steam3 only user auth
	virtual bool SendSteam3UserConnect( CSteamID steamID, uint32 unIPPublic, const void *pvCookie, uint32 cubCookie ) = 0;

	virtual bool RemoveUserConnect( uint32 unUserID ) = 0;

	// Should be called whenever a user leaves our game server, this lets Steam internally
	// track which users are currently on which servers for the purposes of preventing a single
	// account being logged into multiple servers, showing who is currently on a server, etc.
	virtual bool SendUserDisconnect( CSteamID steamID, uint32 unUserID ) = 0;

	virtual bool SendUserStatusResponse( CSteamID steamID, int nSecondsConnected, int nSecondsSinceLast ) = 0;

	// obsolete, use UpdateStatus below
	virtual bool Obsolete_GSSetStatus( int32 nAppIdServed, uint32 unServerFlags, int cPlayers, int cPlayersMax, int cBotPlayers, int unGamePort, const char *pchServerName, const char *pchGameDir, const char *pchMapName, const char *pchVersion ) = 0;

	// Updates server status values which shows up in the server browser and matchmaking APIs
	virtual bool UpdateStatus( int cPlayers, int cPlayersMax, int cBotPlayers, const char *pchServerName, const char *pchMapName ) = 0;

	virtual bool BSecure() = 0; 
	STEAMWORKS_STRUCT_RETURN_0(CSteamID, GetSteamID) /*virtual CSteamID GetSteamID() = 0;*/

	// You shouldn't need to call this as it is called internally by SteamGameServer_Init() and can only be called once.
	//
	// To update the data in this call which may change during the servers lifetime see UpdateServerStatus() below.
	//
	// Input:	nGameAppID - The Steam assigned AppID for the game
	//			unServerFlags - Any applicable combination of flags (see k_unServerFlag____ constants below)
	//			unGameIP - The IP Address the server is listening for client connections on (might be INADDR_ANY), note that this is in host order
	//			unGamePort - The port which the server is listening for client connections on
	//			pchGameDir - A unique string identifier for your game
	//			pchVersion - The current version of the server as a string like 1.0.0.0
	//			
	// bugbug jmccaskey - figure out how to remove this from the API and only expose via SteamGameServer_Init... or make this actually used,
	// and stop calling it in SteamGameServer_Init()?
	virtual bool SetServerType( int32 nGameAppId, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char *pchGameDir, const char *pchVersion ) = 0;

	// voided: these functions seem to have been added sometime after this interface was created, probably to keep it viable against the newer interfaces
	//

	// You shouldn't need to call this as it is called internally by SteamGameServer_Init() and can only be called once.
	//
	// To update the data in this call which may change during the servers lifetime see UpdateServerStatus() below.
	//
	// Input:	nGameAppID - The Steam assigned AppID for the game
	//			unServerFlags - Any applicable combination of flags (see k_unServerFlag____ constants below)
	//			unGameIP - The IP Address the server is listening for client connections on (might be INADDR_ANY)
	//			unGamePort - The port which the server is listening for client connections on
	//			unSpectatorPort - the port on which spectators can join to observe the server, 0 if spectating is not supported
	//			usQueryPort - The port which the ISteamMasterServerUpdater API should use in order to listen for matchmaking requests
	//			pchGameDir - A unique string identifier for your game
	//			pchVersion - The current version of the server as a string like 1.0.0.0
	//			bLanMode - Is this a LAN only server?
	//			
	// bugbug jmccaskey - figure out how to remove this from the API and only expose via SteamGameServer_Init... or make this actually used,
	// and stop calling it in SteamGameServer_Init()?
	virtual bool SetServerType2( int32 nGameAppId, uint32 unServerFlags, uint32 unGameIP, uint16 unGamePort, uint16 usSpectatorPort, uint16 usQueryPort, const char *pchGameDir, const char *pchVersion, bool bLANMode ) = 0;

	// Updates server status values which shows up in the server browser and matchmaking APIs

	virtual bool UpdateStatus2( int cPlayers, int cPlayersMax, int cBotPlayers, const char *pchServerName, const char *pSpectatorServerName, const char *pchMapName ) = 0;

	// Creates a fake user (ie, a bot) which will be listed as playing on the server, but skips validation.  
	// 
	// Return Value: Returns a SteamID for the user to be tracked with, you should call HandleUserDisconnect()
	// when this user leaves the server just like you would for a real user.
	virtual bool CreateUnauthenticatedUser( CSteamID *pSteamID ) = 0;

	// Update the data to be displayed in the server browser and matchmaking interfaces for a user
	// currently connected to the server.  For regular users you must call this after you receive a
	// GSUserValidationSuccess callback.
	// 
	// Return Value: true if successful, false if failure (ie, steamIDUser wasn't for an active player)
	virtual bool SetUserData( CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore ) = 0;

	// This can be called if spectator goes away or comes back (passing 0 means there is no spectator server now).
	virtual void UpdateSpectatorPort( uint16 unSpectatorPort ) = 0;

	// Sets a string defining the "gametype" for this server, this is optional, but if it is set
	// it allows users to filter in the matchmaking/server-browser interfaces based on the value
	virtual void SetGameType( const char *pchGameType ) = 0; 
};


#endif // ISTEAMGAMESERVER002_H

