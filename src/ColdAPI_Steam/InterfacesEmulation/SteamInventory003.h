#pragma once
#include "../public SDK/ISteamInventory003.h"

class SteamInventoryIn003 : public ISteamInventory003
{
public:
	METHOD_DESC(Find out the status of an asynchronous inventory result handle.)
		EResult GetResultStatus(SteamInventoryResult_t resultHandle)
	{
		return k_EResultOK;
	}

	// Copies the contents of a result set into a flat array. The specific
	// contents of the result set depend on which query which was used.
	METHOD_DESC(Copies the contents of a result set into a flat array.The specific contents of the result set depend on which query which was used.)
		bool GetResultItems(SteamInventoryResult_t resultHandle,
			OUT_ARRAY_COUNT(punOutItemsArraySize, Output array) SteamItemDetails_t* pOutItemsArray,
			uint32* punOutItemsArraySize)
	{
		return false;
	}

	bool GetResultItemProperty(SteamInventoryResult_t resultHandle,
		uint32 unItemIndex,
		const char* pchPropertyName,
		OUT_STRING_COUNT(punValueBufferSizeOut) char* pchValueBuffer, uint32* punValueBufferSizeOut)
	{
		return false;
	}

	// Returns the server time at which the result was generated. Compare against
	// the value of IClientUtils::GetServerRealTime() to determine age.
	METHOD_DESC(Returns the server time at which the result was generated.Compare against the value of IClientUtils::GetServerRealTime() to determine age.)
		uint32 GetResultTimestamp(SteamInventoryResult_t resultHandle)
	{
		return NULL;
	}

	// Returns true if the result belongs to the target steam ID, false if the
	// result does not. This is important when using DeserializeResult, to verify
	// that a remote player is not pretending to have a different user's inventory.
	METHOD_DESC(Returns true if the result belongs to the target steam ID or false if the result does not.This is important when using DeserializeResult to verify that a remote player is not pretending to have a different users inventory.)
		bool CheckResultSteamID(SteamInventoryResult_t resultHandle, CSteamID steamIDExpected)
	{
		return false;
	}

	// Destroys a result handle and frees all associated memory.
	METHOD_DESC(Destroys a result handleand frees all associated memory.)
		void DestroyResult(SteamInventoryResult_t resultHandle)
	{
		return;
	}


	
	METHOD_DESC(Captures the entire state of the current users Steam inventory.)
		bool GetAllItems(SteamInventoryResult_t* pResultHandle)
	{
		return false;
	}


	// Captures the state of a subset of the current user's Steam inventory,
	// identified by an array of item instance IDs. The results from this call
	// can be serialized and passed to other players to "prove" that the current
	// user owns specific items, without exposing the user's entire inventory.
	// For example, you could call GetItemsByID with the IDs of the user's
	// currently equipped cosmetic items and serialize this to a buffer, and
	// then transmit this buffer to other players upon joining a game.
	METHOD_DESC(Captures the state of a subset of the current users Steam inventory identified by an array of item instance IDs.)
		bool GetItemsByID(SteamInventoryResult_t* pResultHandle, ARRAY_COUNT(unCountInstanceIDs) const SteamItemInstanceID_t* pInstanceIDs, uint32 unCountInstanceIDs)
	{
		return false;
	}


	bool SerializeResult(SteamInventoryResult_t resultHandle, OUT_BUFFER_COUNT(punOutBufferSize) void* pOutBuffer, uint32* punOutBufferSize)
	{
		return false;
	}

	bool DeserializeResult(SteamInventoryResult_t* pOutResultHandle, BUFFER_COUNT(punOutBufferSize) const void* pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE = false)
	{
		return false;
	}


	bool GenerateItems(SteamInventoryResult_t* pResultHandle, ARRAY_COUNT(unArrayLength) const SteamItemDef_t* pArrayItemDefs, ARRAY_COUNT(unArrayLength) const uint32* punArrayQuantity, uint32 unArrayLength)
	{
		return false;
	}

	// GrantPromoItems() checks the list of promotional items for which the user may be eligible
	// and grants the items (one time only).  On success, the result set will include items which
	// were granted, if any. If no items were granted because the user isn't eligible for any
	// promotions, this is still considered a success.
	METHOD_DESC(GrantPromoItems() checks the list of promotional items for which the user may be eligibleand grants the items(one time only).)
		bool GrantPromoItems(SteamInventoryResult_t* pResultHandle)
	{
		return false;
	}

	bool AddPromoItem(SteamInventoryResult_t* pResultHandle, SteamItemDef_t itemDef)
	{
		return false;
	}
	bool AddPromoItems(SteamInventoryResult_t* pResultHandle, ARRAY_COUNT(unArrayLength) const SteamItemDef_t* pArrayItemDefs, uint32 unArrayLength)
	{
		return false;
	}

	
	METHOD_DESC(ConsumeItem() removes items from the inventory permanently.)
		bool ConsumeItem(SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity)
	{
		return false;
	}

	bool ExchangeItems(SteamInventoryResult_t* pResultHandle,
		ARRAY_COUNT(unArrayGenerateLength) const SteamItemDef_t* pArrayGenerate, ARRAY_COUNT(unArrayGenerateLength) const uint32* punArrayGenerateQuantity, uint32 unArrayGenerateLength,
		ARRAY_COUNT(unArrayDestroyLength) const SteamItemInstanceID_t* pArrayDestroy, ARRAY_COUNT(unArrayDestroyLength) const uint32* punArrayDestroyQuantity, uint32 unArrayDestroyLength)
	{
		return false;
	}


	bool TransferItemQuantity(SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest)
	{
		return false;
	}

	METHOD_DESC(Deprecated method.Playtime accounting is performed on the Steam servers.)
		void SendItemDropHeartbeat()
	{
		return;
	}

	
	METHOD_DESC(Playtime credit must be consumedand turned into item drops by your game.)
		bool TriggerItemDrop(SteamInventoryResult_t* pResultHandle, SteamItemDef_t dropListDefinition)
	{
		return false;
	}


	bool TradeItems(SteamInventoryResult_t* pResultHandle, CSteamID steamIDTradePartner,
		ARRAY_COUNT(nArrayGiveLength) const SteamItemInstanceID_t* pArrayGive, ARRAY_COUNT(nArrayGiveLength) const uint32* pArrayGiveQuantity, uint32 nArrayGiveLength,
		ARRAY_COUNT(nArrayGetLength) const SteamItemInstanceID_t* pArrayGet, ARRAY_COUNT(nArrayGetLength) const uint32* pArrayGetQuantity, uint32 nArrayGetLength)
	{
		return false;
	}

	METHOD_DESC(LoadItemDefinitions triggers the automatic loadand refresh of item definitions.)
		bool LoadItemDefinitions()
	{
		return false;
	}

	bool GetItemDefinitionIDs(
		OUT_ARRAY_COUNT(punItemDefIDsArraySize, List of item definition IDs) SteamItemDef_t* pItemDefIDs,
		DESC(Size of array is passed inand actual size used is returned in this param) uint32* punItemDefIDsArraySize)
	{
		return false;
	}

	bool GetItemDefinitionProperty(SteamItemDef_t iDefinition, const char* pchPropertyName,
		OUT_STRING_COUNT(punValueBufferSizeOut) char* pchValueBuffer, uint32* punValueBufferSizeOut)
	{
		return false;
	}

	SteamAPICall_t RequestEligiblePromoItemDefinitionsIDs(CSteamID steamID)
	{
		return NULL;
	}

	bool GetEligiblePromoItemDefinitionIDs(
		CSteamID steamID,
		OUT_ARRAY_COUNT(punItemDefIDsArraySize, List of item definition IDs) SteamItemDef_t* pItemDefIDs,
		DESC(Size of array is passed inand actual size used is returned in this param) uint32* punItemDefIDsArraySize)
	{
		return false;
	}

	SteamAPICall_t StartPurchase(ARRAY_COUNT(unArrayLength) const SteamItemDef_t* pArrayItemDefs, ARRAY_COUNT(unArrayLength) const uint32* punArrayQuantity, uint32 unArrayLength)
	{
		return NULL;
	}

	SteamAPICall_t RequestPrices()
	{
		return NULL;
	}

	uint32 GetNumItemsWithPrices()
	{
		return NULL;
	}

	bool GetItemsWithPrices(ARRAY_COUNT(unArrayLength) OUT_ARRAY_COUNT(pArrayItemDefs, Items with prices) SteamItemDef_t* pArrayItemDefs,
		ARRAY_COUNT(unArrayLength) OUT_ARRAY_COUNT(pPrices, List of prices for the given item defs) uint64* pCurrentPrices,
		ARRAY_COUNT(unArrayLength) OUT_ARRAY_COUNT(pPrices, List of prices for the given item defs) uint64* pBasePrices,
		uint32 unArrayLength)
	{
		return false;
	}

	bool GetItemPrice(SteamItemDef_t iDefinition, uint64* pCurrentPrice, uint64* pBasePrice)
	{
		return false;
	}

	SteamInventoryUpdateHandle_t StartUpdateProperties()
	{
		return NULL;
	}
	bool RemoveProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName)
	{
		return false;
	}
	bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, const char* pchPropertyValue)
	{
		return false;
	}
	bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, bool bValue)
	{
		return false;
	}
	bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, int64 nValue)
	{
		return false;
	}
	bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, float flValue)
	{
		return false;
	}
	bool SubmitUpdateProperties(SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t* pResultHandle)
	{
		return false;
	}
};