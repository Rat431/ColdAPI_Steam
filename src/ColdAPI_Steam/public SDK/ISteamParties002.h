#include "SteamTypes.h"

typedef uint64 PartyBeaconID_t;
enum { k_iSteamPartiesCallbacks = 5300 };
struct JoinPartyCallback_t
{
	enum { k_iCallback = k_iSteamPartiesCallbacks + 1 };

	EResult m_eResult;
	PartyBeaconID_t m_ulBeaconID;
	CSteamID m_SteamIDBeaconOwner;
	char m_rgchConnectString[256];
};
enum ESteamPartyBeaconLocationType
{
	k_ESteamPartyBeaconLocationType_Invalid = 0,
	k_ESteamPartyBeaconLocationType_ChatGroup = 1,

	k_ESteamPartyBeaconLocationType_Max,
};
struct SteamPartyBeaconLocation_t
{
	ESteamPartyBeaconLocationType m_eType;
	uint64 m_ulLocationID;
};
struct CreateBeaconCallback_t
{
	enum { k_iCallback = k_iSteamPartiesCallbacks + 2 };

	EResult m_eResult;
	PartyBeaconID_t m_ulBeaconID;
};
struct ChangeNumOpenSlotsCallback_t
{
	enum { k_iCallback = k_iSteamPartiesCallbacks + 4 };

	EResult m_eResult;
};
enum ESteamPartyBeaconLocationData
{
	k_ESteamPartyBeaconLocationDataInvalid = 0,
	k_ESteamPartyBeaconLocationDataName = 1,
	k_ESteamPartyBeaconLocationDataIconURLSmall = 2,
	k_ESteamPartyBeaconLocationDataIconURLMedium = 3,
	k_ESteamPartyBeaconLocationDataIconURLLarge = 4,
};
class ISteamParties002
{
public:

	// =============================================================================================
	// Party Client APIs

	// Enumerate any active beacons for parties you may wish to join
	virtual uint32 GetNumActiveBeacons() = 0;
	virtual PartyBeaconID_t GetBeaconByIndex(uint32 unIndex) = 0;
	virtual bool GetBeaconDetails(PartyBeaconID_t ulBeaconID, CSteamID* pSteamIDBeaconOwner, SteamPartyBeaconLocation_t* pLocation, char* pchMetadata, int cchMetadata) = 0;

	// Join an open party. Steam will reserve one beacon slot for your SteamID,
	// and return the necessary JoinGame string for you to use to connect
	virtual SteamAPICall_t JoinParty(PartyBeaconID_t ulBeaconID) = 0;

	// =============================================================================================
	// Party Host APIs

	// Get a list of possible beacon locations
	virtual bool GetNumAvailableBeaconLocations(uint32* puNumLocations) = 0;
	virtual bool GetAvailableBeaconLocations(SteamPartyBeaconLocation_t* pLocationList, uint32 uMaxNumLocations) = 0;

	// Create a new party beacon and activate it in the selected location.
	// unOpenSlots is the maximum number of users that Steam will send to you.
	// When people begin responding to your beacon, Steam will send you
	// PartyReservationCallback_t callbacks to let you know who is on the way.
	virtual SteamAPICall_t CreateBeacon(uint32 unOpenSlots, SteamPartyBeaconLocation_t* pBeaconLocation, const char* pchConnectString, const char* pchMetadata) = 0;

	// Call this function when a user that had a reservation (see callback below) 
	// has successfully joined your party.
	// Steam will manage the remaining open slots automatically.
	virtual void OnReservationCompleted(PartyBeaconID_t ulBeacon, CSteamID steamIDUser) = 0;

	// To cancel a reservation (due to timeout or user input), call this.
	// Steam will open a new reservation slot.
	// Note: The user may already be in-flight to your game, so it's possible they will still connect and try to join your party.
	virtual void CancelReservation(PartyBeaconID_t ulBeacon, CSteamID steamIDUser) = 0;

	// Change the number of open beacon reservation slots.
	// Call this if, for example, someone without a reservation joins your party (eg a friend, or via your own matchmaking system).
	virtual SteamAPICall_t ChangeNumOpenSlots(PartyBeaconID_t ulBeacon, uint32 unOpenSlots) = 0;

	// Turn off the beacon. 
	virtual bool DestroyBeacon(PartyBeaconID_t ulBeacon) = 0;

	// Utils
	virtual bool GetBeaconLocationData(SteamPartyBeaconLocation_t BeaconLocation, ESteamPartyBeaconLocationData eData, char* pchDataStringOut, int cchDataStringOut) = 0;

};
#define STEAMPARTIES_INTERFACE_VERSION002 "SteamParties002"