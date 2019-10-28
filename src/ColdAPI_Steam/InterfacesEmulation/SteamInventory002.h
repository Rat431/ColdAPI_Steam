#pragma once
#include "../public SDK/ISteamInventory002.h"

class SteamInventoryIn002 : public ISteamInventory002
{
public:
	EResult GetResultStatus(SteamInventoryResult_t resultHandle)
	{
		return k_EResultOK;
	}

	bool GetResultItems(SteamInventoryResult_t resultHandle,
		SteamItemDetails_t* pOutItemsArray,
		uint32* punOutItemsArraySize)
	{
		return false;
	}

	bool GetResultItemProperty(SteamInventoryResult_t resultHandle,
		uint32 unItemIndex,
		const char* pchPropertyName,
		char* pchValueBuffer, uint32* punValueBufferSizeOut)
	{
		return false;
	}

	uint32 GetResultTimestamp(SteamInventoryResult_t resultHandle)
	{
		return NULL;
	}

	bool CheckResultSteamID(SteamInventoryResult_t resultHandle, CSteamID steamIDExpected)
	{
		return false;
	}

	void DestroyResult(SteamInventoryResult_t resultHandle)
	{
		return;
	}


	bool GetAllItems(SteamInventoryResult_t* pResultHandle)
	{
		return false;
	}


	bool GetItemsByID(SteamInventoryResult_t* pResultHandle, const SteamItemInstanceID_t* pInstanceIDs, uint32 unCountInstanceIDs)
	{
		return false;
	}


	bool SerializeResult(SteamInventoryResult_t resultHandle, void* pOutBuffer, uint32* punOutBufferSize)
	{
		return false;
	}

	bool DeserializeResult(SteamInventoryResult_t* pOutResultHandle, const void* pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE = false)
	{
		return false;
	}


	bool GenerateItems(SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, ARRAY_COUNT(unArrayLength) const uint32* punArrayQuantity, uint32 unArrayLength)
	{
		return false;
	}

	
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
		ARRAY_COUNT(unArrayLength) OUT_ARRAY_COUNT(pPrices, List of prices for the given item defs) uint64* pPrices,
		uint32 unArrayLength)
	{
		return false;
	}

	bool GetItemPrice(SteamItemDef_t iDefinition, uint64* pPrice)
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
