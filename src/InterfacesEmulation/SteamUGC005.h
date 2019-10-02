#pragma once
#include "../public SDK/ISteamUGC005.h"

class SteamUGCIn005 : public ISteamUGC005
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

	UGCQueryHandle_t CreateQueryUGCDetailsRequest(PublishedFileId_t* pvecPublishedFileID, uint32 unNumPublishedFileIDs)
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
	bool GetQueryUGCPreviewURL(UGCQueryHandle_t handle, uint32 index, char* pchURL, uint32 cchURLSize)
	{
		return false;
	}
	bool GetQueryUGCMetadata(UGCQueryHandle_t handle, uint32 index, char* pchMetadata, uint32 cchMetadatasize)
	{
		return false;
	}
	bool GetQueryUGCChildren(UGCQueryHandle_t handle, uint32 index, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries)
	{
		return false;
	}
	bool GetQueryUGCStatistic(UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint32* pStatValue)
	{
		return false;
	}
	uint32 GetQueryUGCNumAdditionalPreviews(UGCQueryHandle_t handle, uint32 index)
	{
		return NULL;
	}
	bool GetQueryUGCAdditionalPreview(UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char* pchURLOrVideoID, uint32 cchURLSize, bool* pbIsImage)
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
	bool SetReturnMetadata(UGCQueryHandle_t handle, bool bReturnMetadata)
	{
		return false;
	}
	bool SetReturnChildren(UGCQueryHandle_t handle, bool bReturnChildren)
	{
		return false;
	}
	bool SetReturnAdditionalPreviews(UGCQueryHandle_t handle, bool bReturnAdditionalPreviews)
	{
		return false;
	}
	bool SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly)
	{
		return false;
	}
	bool SetAllowCachedResponse(UGCQueryHandle_t handle, uint32 unMaxAgeSeconds)
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

	SteamAPICall_t RequestUGCDetails(PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds)
	{
		return NULL;
	}

	SteamAPICall_t CreateItem(AppId_t nConsumerAppId, EWorkshopFileType eFileType)
	{
		return NULL;
	}

	UGCUpdateHandle_t StartItemUpdate(AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}

	bool SetItemTitle(UGCUpdateHandle_t handle, const char* pchTitle)
	{
		return false;
	}
	bool SetItemDescription(UGCUpdateHandle_t handle, const char* pchDescription)
	{
		return false;
	}
	bool SetItemMetadata(UGCUpdateHandle_t handle, const char* pchMetaData)
	{
		return false;
	}
	bool SetItemVisibility(UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility)
	{
		return false;
	}
	bool SetItemTags(UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t* pTags)
	{
		return false;
	}
	bool SetItemContent(UGCUpdateHandle_t handle, const char* pszContentFolder)
	{
		return false;
	}
	bool SetItemPreview(UGCUpdateHandle_t handle, const char* pszPreviewFile)
	{
		return false;
	}

	SteamAPICall_t SubmitItemUpdate(UGCUpdateHandle_t handle, const char* pchChangeNote)
	{
		return NULL;
	}
	EItemUpdateStatus GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64* punBytesProcessed, uint64* punBytesTotal)
	{
		return k_EItemUpdateStatusInvalid;
	}

	SteamAPICall_t AddItemToFavorites(AppId_t nAppId, PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}
	SteamAPICall_t RemoveItemFromFavorites(AppId_t nAppId, PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}
	SteamAPICall_t SubscribeItem(PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}
	SteamAPICall_t UnsubscribeItem(PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}
	uint32 GetNumSubscribedItems()
	{
		return NULL;
	}
	uint32 GetSubscribedItems(PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries)
	{
		return NULL;
	}

	uint32 GetItemState(PublishedFileId_t nPublishedFileID)
	{
		return NULL;
	}

	bool GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64* punSizeOnDisk, char* pchFolder, uint32 cchFolderSize, uint32* punTimeStamp)
	{
		return false;
	}

	bool GetItemDownloadInfo(PublishedFileId_t nPublishedFileID, uint64* punBytesDownloaded, uint64* punBytesTotal)
	{
		return false;
	}

	bool DownloadItem(PublishedFileId_t nPublishedFileID, bool bHighPriority)
	{
		return false;
	}
};