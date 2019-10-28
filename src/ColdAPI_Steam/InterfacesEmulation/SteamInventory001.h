#pragma once
#include "../public SDK/ISteamInventory001.h"

class SteamInventoryIn001 : public ISteamInventory001
{
public:
	EResult GetResultStatus(SteamInventoryResult_t resultHandle)
	{
		return k_EResultOK;
	}

	bool GetResultItems(SteamInventoryResult_t resultHandle,
		OUT_ARRAY_COUNT(punOutItemsArraySize, Output array) SteamItemDetails_t* pOutItemsArray,
		uint32* punOutItemsArraySize)
	{
		return false;
	}

	uint32 GetResultTimestamp(SteamInventoryResult_t resultHandle)
	{
		return NULL;
	}

	bool CheckResultSteamID(SteamInventoryResult_t resultHandle, CSteamID steamIDExpected)
	{
		return true;
	}

	void DestroyResult(SteamInventoryResult_t resultHandle)
	{
		return;
	}


	bool GetAllItems(SteamInventoryResult_t* pResultHandle)
	{
		return false;
	}


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


	void SendItemDropHeartbeat()
	{
		return;
	}

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
		OUT_STRING_COUNT(punValueBufferSize) char* pchValueBuffer, uint32* punValueBufferSize)
	{
		return false;
	}
};