#pragma once
#include "../public SDK/ISteamGameSearch001.h"

class SteamGameSearchIn001 : public ISteamGameSearch001
{
public:
	int32_t AddGameSearchParams(const char* pchKeyToFind, const char* pchValuesToFind)
	{
		return 7;
	}

	int32_t SearchForGameWithLobby(CSteamID steamIDLobby, int nPlayerMin, int nPlayerMax)
	{
		return 7;
	}

	int32_t SearchForGameSolo(int nPlayerMin, int nPlayerMax)
	{
		return 7;
	}

	int32_t AcceptGame()
	{
		return 7;
	}
	int32_t DeclineGame()
	{
		return 7;
	}

	int32_t RetrieveConnectionDetails(CSteamID steamIDHost, char* pchConnectionDetails, int cubConnectionDetails)
	{
		return 7;
	}

	int32_t EndGameSearch()
	{
		return 7;
	}

	int32_t SetGameHostParams(const char* pchKey, const char* pchValue)
	{
		return 7;
	}

	int32_t SetConnectionDetails(const char* pchConnectionDetails, int cubConnectionDetails)
	{
		return 7;
	}

	int32_t RequestPlayersForGame(int nPlayerMin, int nPlayerMax, int nMaxTeamSize)
	{
		return 7;
	}

	int32_t HostConfirmGameStart(uint64 ullUniqueGameID)
	{
		return 7;
	}

	int32_t CancelRequestPlayersForGame()
	{
		return 7;
	}

	int32_t SubmitPlayerResult(uint64 ullUniqueGameID, CSteamID steamIDPlayer, int32_t EPlayerResult)
	{
		return 7;
	}

	int32_t EndGame(uint64 ullUniqueGameID)
	{
		return 7;
	}
};