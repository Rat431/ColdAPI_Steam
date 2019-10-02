#pragma once
#include "../public SDK/ISteamParties002.h"

class SteamPartiesIn002 : public ISteamParties002
{
public:
	uint32 GetNumActiveBeacons()
	{
		return NULL;
	}
	PartyBeaconID_t GetBeaconByIndex(uint32 unIndex)
	{
		return NULL;
	}
	bool GetBeaconDetails(PartyBeaconID_t ulBeaconID, CSteamID* pSteamIDBeaconOwner, SteamPartyBeaconLocation_t* pLocation, char* pchMetadata, int cchMetadata)
	{
		return false;
	}

	SteamAPICall_t JoinParty(PartyBeaconID_t ulBeaconID)
	{
		return NULL;
	}

	bool GetNumAvailableBeaconLocations(uint32* puNumLocations)
	{
		return false;
	}
	bool GetAvailableBeaconLocations(SteamPartyBeaconLocation_t* pLocationList, uint32 uMaxNumLocations)
	{
		return false;
	}

	SteamAPICall_t CreateBeacon(uint32 unOpenSlots, SteamPartyBeaconLocation_t* pBeaconLocation, const char* pchConnectString, const char* pchMetadata)
	{
		return NULL;
	}

	void OnReservationCompleted(PartyBeaconID_t ulBeacon, CSteamID steamIDUser)
	{
		return;
	}

	void CancelReservation(PartyBeaconID_t ulBeacon, CSteamID steamIDUser)
	{
		return;
	}

	SteamAPICall_t ChangeNumOpenSlots(PartyBeaconID_t ulBeacon, uint32 unOpenSlots)
	{
		return NULL;
	}

	bool DestroyBeacon(PartyBeaconID_t ulBeacon)
	{
		return false;
	}

	bool GetBeaconLocationData(SteamPartyBeaconLocation_t BeaconLocation, ESteamPartyBeaconLocationData eData, char* pchDataStringOut, int cchDataStringOut)
	{
		return false;
	}
};