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
#include "RemoteStorageCommon.h"

#ifndef UGCCOMMON_H
#define UGCCOMMON_H
#ifdef _WIN32
#pragma once
#endif
typedef uint64 UGCQueryHandle_t;
typedef uint64 UGCUpdateHandle_t;

const UGCQueryHandle_t k_UGCQueryHandleInvalid = 0xffffffffffffffffull;
const UGCUpdateHandle_t k_UGCUpdateHandleInvalid = 0xffffffffffffffffull;

// Matching UGC types for queries
enum EUGCMatchingUGCType
{
	k_EUGCMatchingUGCType_Items				 = 0,		// both mtx items and ready-to-use items
	k_EUGCMatchingUGCType_Items_Mtx			 = 1,
	k_EUGCMatchingUGCType_Items_ReadyToUse	 = 2,
	k_EUGCMatchingUGCType_Collections		 = 3,
	k_EUGCMatchingUGCType_Artwork			 = 4,
	k_EUGCMatchingUGCType_Videos			 = 5,
	k_EUGCMatchingUGCType_Screenshots		 = 6,
	k_EUGCMatchingUGCType_AllGuides			 = 7,		// both web guides and integrated guides
	k_EUGCMatchingUGCType_WebGuides			 = 8,
	k_EUGCMatchingUGCType_IntegratedGuides	 = 9,
	k_EUGCMatchingUGCType_UsableInGame		 = 10,		// ready-to-use items and integrated guides
	k_EUGCMatchingUGCType_ControllerBindings = 11,
	k_EUGCMatchingUGCType_GameManagedItems	 = 12,		// game managed items (not managed by users)
	k_EUGCMatchingUGCType_All				 = ~0,		// return everything
};

// Different lists of published UGC for a user.
// If the current logged in user is different than the specified user, then some options may not be allowed.
enum EUserUGCList
{
	k_EUserUGCList_Published,
	k_EUserUGCList_VotedOn,
	k_EUserUGCList_VotedUp,
	k_EUserUGCList_VotedDown,
	k_EUserUGCList_WillVoteLater,
	k_EUserUGCList_Favorited,
	k_EUserUGCList_Subscribed,
	k_EUserUGCList_UsedOrPlayed,
	k_EUserUGCList_Followed,
};

// Sort order for user published UGC lists (defaults to creation order descending)
enum EUserUGCListSortOrder
{
	k_EUserUGCListSortOrder_CreationOrderDesc,
	k_EUserUGCListSortOrder_CreationOrderAsc,
	k_EUserUGCListSortOrder_TitleAsc,
	k_EUserUGCListSortOrder_LastUpdatedDesc,
	k_EUserUGCListSortOrder_SubscriptionDateDesc,
	k_EUserUGCListSortOrder_VoteScoreDesc,
	k_EUserUGCListSortOrder_ForModeration,
};

// Combination of sorting and filtering for queries across all UGC
enum EUGCQuery
{
	k_EUGCQuery_RankedByVote								  = 0,
	k_EUGCQuery_RankedByPublicationDate						  = 1,
	k_EUGCQuery_AcceptedForGameRankedByAcceptanceDate		  = 2,
	k_EUGCQuery_RankedByTrend								  = 3,
	k_EUGCQuery_FavoritedByFriendsRankedByPublicationDate	  = 4,
	k_EUGCQuery_CreatedByFriendsRankedByPublicationDate		  = 5,
	k_EUGCQuery_RankedByNumTimesReported					  = 6,
	k_EUGCQuery_CreatedByFollowedUsersRankedByPublicationDate = 7,
	k_EUGCQuery_NotYetRated									  = 8,
	k_EUGCQuery_RankedByTotalVotesAsc						  = 9,
	k_EUGCQuery_RankedByVotesUp								  = 10,
	k_EUGCQuery_RankedByTextSearch							  = 11,
	k_EUGCQuery_RankedByTotalUniqueSubscriptions			  = 12,
};

enum EItemUpdateStatus
{
	k_EItemUpdateStatusInvalid 				= 0, // The item update handle was invalid, job might be finished, listen too SubmitItemUpdateResult_t
	k_EItemUpdateStatusPreparingConfig 		= 1, // The item update is processing configuration data
	k_EItemUpdateStatusPreparingContent		= 2, // The item update is reading and processing content files
	k_EItemUpdateStatusUploadingContent		= 3, // The item update is uploading content changes to Steam
	k_EItemUpdateStatusUploadingPreviewFile	= 4, // The item update is uploading new preview file image
	k_EItemUpdateStatusCommittingChanges	= 5  // The item update is committing all changes
};

enum EItemState
{
	k_EItemStateNone			= 0,	// item not tracked on client
	k_EItemStateSubscribed		= 1,	// current user is subscribed to this item. Not just cached.
	k_EItemStateLegacyItem		= 2,	// item was created with ISteamRemoteStorage
	k_EItemStateInstalled		= 4,	// item is installed and usable (but maybe out of date)
	k_EItemStateNeedsUpdate		= 8,	// items needs an update. Either because it's not installed yet or creator updated content
	k_EItemStateDownloading		= 16,	// item update is currently downloading
	k_EItemStateDownloadPending	= 32,	// DownloadItem() was called for this item, content isn't available until DownloadItemResult_t is fired
};

enum EItemStatistic
{
	k_EItemStatistic_NumSubscriptions		= 0,
	k_EItemStatistic_NumFavorites			= 1,
	k_EItemStatistic_NumFollowers			= 2,
	k_EItemStatistic_NumUniqueSubscriptions = 3,
	k_EItemStatistic_NumUniqueFavorites		= 4,
	k_EItemStatistic_NumUniqueFollowers		= 5,
	k_EItemStatistic_NumUniqueWebsiteViews	= 6,
	k_EItemStatistic_ReportScore			= 7,
};

const uint32 kNumUGCResultsPerPage = 50;
const uint32 k_cchDeveloperMetadataMax = 5000;

// Details for a single published file/UGC
struct SteamUGCDetails_t
{
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;												// The result of the operation.	
	EWorkshopFileType m_eFileType;									// Type of the file
	AppId_t m_nCreatorAppID;										// ID of the app that created this file.
	AppId_t m_nConsumerAppID;										// ID of the app that will consume this file.
	char m_rgchTitle[k_cchPublishedDocumentTitleMax];				// title of document
	char m_rgchDescription[k_cchPublishedDocumentDescriptionMax];	// description of document
	uint64 m_ulSteamIDOwner;										// Steam ID of the user who created this content.
	uint32 m_rtimeCreated;											// time when the published file was created
	uint32 m_rtimeUpdated;											// time when the published file was last updated
	uint32 m_rtimeAddedToUserList;									// time when the user added the published file to their list (not always applicable)
	ERemoteStoragePublishedFileVisibility m_eVisibility;			// visibility
	bool m_bBanned;													// whether the file was banned
	bool m_bAcceptedForUse;											// developer has specifically flagged this item as accepted in the Workshop
	bool m_bTagsTruncated;											// whether the list of tags was too long to be returned in the provided buffer
	char m_rgchTags[k_cchTagListMax];								// comma separated list of all tags associated with this file	
	// file/url information
	UGCHandle_t m_hFile;											// The handle of the primary file
	UGCHandle_t m_hPreviewFile;										// The handle of the preview file
	char m_pchFileName[k_cchFilenameMax];							// The cloud filename of the primary file
	int32 m_nFileSize;												// Size of the primary file
	int32 m_nPreviewFileSize;										// Size of the preview file
	char m_rgchURL[k_cchPublishedFileURLMax];						// URL (for a video or a website)
	// voting information
	uint32 m_unVotesUp;												// number of votes up
	uint32 m_unVotesDown;											// number of votes down
	float m_flScore;												// calculated score
	uint32 m_unNumChildren;											// if m_eFileType == k_EWorkshopFileTypeCollection, then this number will be the number of children contained within the collection
};


#define STEAMUGC_INTERFACE_VERSION001 "STEAMUGC_INTERFACE_VERSION001"
#define STEAMUGC_INTERFACE_VERSION002 "STEAMUGC_INTERFACE_VERSION002"
#define STEAMUGC_INTERFACE_VERSION003 "STEAMUGC_INTERFACE_VERSION003"
#define STEAMUGC_INTERFACE_VERSION004 "STEAMUGC_INTERFACE_VERSION004"
#define STEAMUGC_INTERFACE_VERSION005 "STEAMUGC_INTERFACE_VERSION005"
#define STEAMUGC_INTERFACE_VERSION006 "STEAMUGC_INTERFACE_VERSION006"
#define STEAMUGC_INTERFACE_VERSION007 "STEAMUGC_INTERFACE_VERSION007"
#define STEAMUGC_INTERFACE_VERSION008 "STEAMUGC_INTERFACE_VERSION008"
#define STEAMUGC_INTERFACE_VERSION009 "STEAMUGC_INTERFACE_VERSION009"
#define STEAMUGC_INTERFACE_VERSION010 "STEAMUGC_INTERFACE_VERSION010"
#define STEAMUGC_INTERFACE_VERSION012 "STEAMUGC_INTERFACE_VERSION012"
#define STEAMUGC_INTERFACE_VERSION013 "STEAMUGC_INTERFACE_VERSION013"


#pragma pack( push, 8 )

//-----------------------------------------------------------------------------
// Purpose: Callback for querying UGC
//-----------------------------------------------------------------------------
struct SteamUGCQueryCompleted_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 1 };
	UGCQueryHandle_t m_handle;
	EResult m_eResult;
	uint32 m_unNumResultsReturned;
	uint32 m_unTotalMatchingResults;
	bool m_bCachedData;	// indicates whether this data was retrieved from the local on-disk cache
};


//-----------------------------------------------------------------------------
// Purpose: Callback for requesting details on one piece of UGC
//-----------------------------------------------------------------------------
struct SteamUGCRequestUGCDetailsResult_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 2 };
	SteamUGCDetails_t m_details;
	bool m_bCachedData; // indicates whether this data was retrieved from the local on-disk cache
};


//-----------------------------------------------------------------------------
// Purpose: result for ISteamUGC::CreateItem() 
//-----------------------------------------------------------------------------
struct CreateItemResult_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 3 };
	EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId; // new item got this UGC PublishFileID
	bool m_bUserNeedsToAcceptWorkshopLegalAgreement;
};


//-----------------------------------------------------------------------------
// Purpose: result for ISteamUGC::SubmitItemUpdate() 
//-----------------------------------------------------------------------------
struct SubmitItemUpdateResult_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 4 };
	EResult m_eResult;
	bool m_bUserNeedsToAcceptWorkshopLegalAgreement;
};


//-----------------------------------------------------------------------------
// Purpose: a new Workshop item has been installed or updated
//-----------------------------------------------------------------------------
struct ItemInstalled_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 5 };
	AppId_t m_unAppID;
	PublishedFileId_t m_nPublishedFileId;
};


//-----------------------------------------------------------------------------
// Purpose: result of DownloadItem(), existing item files can be accessed again
//-----------------------------------------------------------------------------
struct DownloadItemResult_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 6 };
	AppId_t m_unAppID;
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;
};


//-----------------------------------------------------------------------------
// Purpose: result of AddItemToFavorites() or RemoveItemFromFavorites()
//-----------------------------------------------------------------------------
struct UserFavoriteItemsListChanged_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 7 };
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;
	bool m_bWasAddRequest;
};


//-----------------------------------------------------------------------------
// Purpose: The result of a call to SetUserItemVote()
//-----------------------------------------------------------------------------
struct SetUserItemVoteResult_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 8 };
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;
	bool m_bVoteUp;
};


//-----------------------------------------------------------------------------
// Purpose: The result of a call to GetUserItemVote()
//-----------------------------------------------------------------------------
struct GetUserItemVoteResult_t
{
	enum { k_iCallback = k_iClientUGCCallbacks + 9 };
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;
	bool m_bVotedUp;
	bool m_bVotedDown;
	bool m_bVoteSkipped;
};

#pragma pack( pop )

#endif // UGCCOMMON_H
