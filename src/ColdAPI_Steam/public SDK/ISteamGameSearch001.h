#include "SteamTypes.h"

//-----------------------------------------------------------------------------
// Purpose: Functions for match making services for clients to get to favorites
//			and to operate on game lobbies.
//-----------------------------------------------------------------------------
class ISteamGameSearch001
{
public:
	// =============================================================================================
	// Game Player APIs

	// a keyname and a list of comma separated values: one of which is must be found in order for the match to qualify
	// fails if a search is currently in progress
	virtual int32_t AddGameSearchParams( const char *pchKeyToFind, const char *pchValuesToFind ) = 0;

	// all players in lobby enter the queue and await a SearchForGameNotificationCallback_t callback. fails if another search is currently in progress
	// if not the owner of the lobby or search already in progress this call fails
	// periodic callbacks will be sent as queue time estimates change
	virtual int32_t SearchForGameWithLobby( CSteamID steamIDLobby, int nPlayerMin, int nPlayerMax ) = 0;

	// user enter the queue and await a SearchForGameNotificationCallback_t callback. fails if another search is currently in progress
	// periodic callbacks will be sent as queue time estimates change
	virtual int32_t SearchForGameSolo( int nPlayerMin, int nPlayerMax ) = 0;

	// after receiving SearchForGameResultCallback_t, accept or decline the game
	// multiple SearchForGameResultCallback_t will follow as players accept game until the host starts or cancels the game
	virtual int32_t AcceptGame() = 0;
	virtual int32_t DeclineGame() = 0;

	// after receiving GameStartedByHostCallback_t get connection details to server
	virtual int32_t RetrieveConnectionDetails( CSteamID steamIDHost, char *pchConnectionDetails, int cubConnectionDetails ) = 0;

	// leaves queue if still waiting
	virtual int32_t EndGameSearch() = 0;

	// =============================================================================================
	// Game Host APIs

	// a keyname and a list of comma separated values: all the values you allow
	virtual int32_t SetGameHostParams( const char *pchKey, const char *pchValue ) = 0;

	// set connection details for players once game is found so they can connect to this server
	virtual int32_t SetConnectionDetails( const char *pchConnectionDetails, int cubConnectionDetails ) = 0;

	// mark server as available for more players with nPlayerMin,nPlayerMax desired
	// accept no lobbies with playercount greater than nMaxTeamSize
	// the set of lobbies returned must be partitionable into teams of no more than nMaxTeamSize
	// RequestPlayersForGameNotificationCallback_t callback will be sent when the search has started
	// multple RequestPlayersForGameResultCallback_t callbacks will follow when players are found
	virtual int32_t RequestPlayersForGame( int nPlayerMin, int nPlayerMax, int nMaxTeamSize ) = 0;

	// accept the player list and release connection details to players
	// players will only be given connection details and host steamid when this is called
	// ( allows host to accept after all players confirm, some confirm, or none confirm. decision is entirely up to the host )
	virtual int32_t HostConfirmGameStart( uint64 ullUniqueGameID ) = 0;

	// cancel request and leave the pool of game hosts looking for players
	// if a set of players has already been sent to host, all players will receive SearchForGameHostFailedToConfirm_t
	virtual int32_t CancelRequestPlayersForGame() = 0;

	// submit a result for one player. does not end the game. ullUniqueGameID continues to describe this game
	virtual int32_t SubmitPlayerResult( uint64 ullUniqueGameID, CSteamID steamIDPlayer, int32_t EPlayerResult ) = 0;

	// ends the game. no further SubmitPlayerResults for ullUniqueGameID will be accepted
	// any future requests will provide a new ullUniqueGameID
	virtual int32_t EndGame( uint64 ullUniqueGameID ) = 0;

};
#define STEAMGAMESEARCH_INTERFACE_VERSION001 "SteamMatchGameSearch001"