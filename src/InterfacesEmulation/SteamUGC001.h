#pragma once
#include "../public SDK/ISteamUGC001.h"

class SteamUGCIn001 : public ISteamUGC001
{
public:
	UGCQueryHandle_t CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
	{
		return NULL;
	}

	UGCQueryHandle_t CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
	{
		return NULL;
	}

	SteamAPICall_t SendQueryUGCRequest(UGCQueryHandle_t handle)
	{
		return NULL;
	}

	bool GetQueryUGCResult(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t* pDetails)
	{
		return false;
	}

	bool ReleaseQueryUGCRequest(UGCQueryHandle_t handle)
	{
		return false;
	}

	bool AddRequiredTag(UGCQueryHandle_t handle, const char* pTagName)
	{
		return false;
	}
	bool AddExcludedTag(UGCQueryHandle_t handle, const char* pTagName)
	{
		return false;
	}
	bool SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription)
	{
		return false;
	}
	bool SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly)
	{
		return false;
	}

	bool SetCloudFileNameFilter(UGCQueryHandle_t handle, const char* pMatchCloudFileName)
	{
		return false;
	}

	bool SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag)
	{
		return false;
	}
	bool SetSearchText(UGCQueryHandle_t handle, const char* pSearchText)
	{
		return false;
	}
	bool SetRankedByTrendDays(UGCQueryHandle_t handle, uint32 unDays)
	{
		return false;
	}

	SteamAPICall_t RequestUGCDetails(PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}
};