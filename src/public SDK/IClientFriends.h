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

#ifndef ICLIENTFRIENDS_H
#define ICLIENTFRIENDS_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "FriendsCommon.h"


abstract_class UNSAFE_INTERFACE IClientFriends
{
public:

	// returns the local players name - guaranteed to not be NULL.
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName( const char *pchPersonaName ) = 0;
	virtual SteamAPICall_t SetPersonaNameEx( const char *pchPersonaName, bool bSendCallback ) = 0;

	virtual bool IsPersonaNameSet() = 0;

	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	virtual void SetPersonaState( EPersonaState ePersonaState ) = 0;

	virtual bool NotifyUIOfMenuChange( bool bShowAvatars, bool bSortByName, bool bShowOnlineOnly, bool bShowUntaggedFriends ) = 0;

	// friend iteration
	virtual int32 GetFriendCount( EFriendFlags iFriendFlags ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32, iFriend, EFriendFlags, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int32 iFriend, EFriendFlags iFriendFlags ) = 0;*/

		virtual int32 GetOnlineFriendCount() = 0;

	// gets the relationship to a user
	virtual EFriendRelationship GetFriendRelationship( CSteamID steamIDFriend ) = 0;
	virtual EPersonaState GetFriendPersonaState( CSteamID steamIDFriend ) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName( CSteamID steamIDFriend ) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int32 GetSmallFriendAvatar( CSteamID steamIDFriend ) = 0;
	virtual int32 GetMediumFriendAvatar( CSteamID steamIDFriend ) = 0;
	virtual int32 GetLargeFriendAvatar( CSteamID steamIDFriend ) = 0;

	// steam registry, accessed by friend
	virtual void SetFriendRegValue( CSteamID steamIDFriend, const char *pchKey, const char *pchValue ) = 0;
	virtual const char *GetFriendRegValue( CSteamID steamIDFriend, const char *pchKey ) = 0;

	virtual bool DeleteFriendRegValue( CSteamID steamID, const char *pchKey ) = 0;

	virtual bool GetFriendGamePlayed( CSteamID steamID, FriendGameInfo_t *pGamePlayInfo ) = 0;
	virtual const char *GetFriendGamePlayedExtraInfo( CSteamID steamIDFriend ) = 0;

	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetFriendGameServer, CSteamID, steamIDFriend) /*virtual CSteamID GetFriendGameServer( CSteamID steamIDFriend ) = 0;*/

		virtual EPersonaStateFlag GetFriendPersonaStateFlags( CSteamID steamIDFriend ) = 0;
	virtual bool IsFriendGameOnConsole( CSteamID steamIDFriend ) = 0;
	STEAMWORKS_STRUCT_RETURN_1(FriendSessionStateInfo_t, GetFriendSessionStateInfo, CSteamID, steamIDFriend) /*virtual FriendSessionStateInfo_t GetFriendSessionStateInfo( CSteamID steamIDFriend ) = 0;*/
		virtual EUserRestriction GetFriendRestrictions( CSteamID steamIDFriend ) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory( CSteamID steamIDFriend, int32 iPersonaName ) = 0;

	virtual SteamAPICall_t RequestPersonaNameHistory( CSteamID steamIDFriend ) = 0;
	virtual const char * GetFriendPersonaNameHistoryAndDate( CSteamID steamIDFriend, int32 iPersonaName, RTime32 * puTime ) = 0;

	virtual bool AddFriend( CSteamID steamID ) = 0;
	virtual bool RemoveFriend( CSteamID steamID ) = 0;
	virtual bool HasFriend( CSteamID steamID, EFriendFlags iFriendFlags ) = 0;

	// adds a friend by email address or account name - value returned in callback
	virtual HSteamCall AddFriendByName( const char *pchEmailOrAccountName ) = 0;

	virtual bool InviteFriendByEmail( const char *pchEmailAddress ) = 0;

	virtual bool RequestUserInformation( CSteamID steamIDUser, bool bRequireNameOnly ) = 0;

	virtual bool SetIgnoreFriend( CSteamID steamIDFriend, bool bIgnore ) = 0;

	virtual bool ReportChatDeclined( CSteamID steamID ) = 0;


	virtual bool CreateFriendsGroup( const char* pchGroupName ) = 0;
	virtual bool DeleteFriendsGroup( int16 iGroupID ) = 0;
	virtual bool RenameFriendsGroup( const char* pchNewGroupName, int16 iGroupID ) = 0;
	virtual bool AddFriendToGroup( CSteamID steamID, int16 iGroupID ) = 0;
	virtual bool RemoveFriendFromGroup( CSteamID steamID, int16 iGroupID ) = 0;
	virtual bool IsFriendMemberOfFriendsGroup( CSteamID steamID, int16 iGroupID ) = 0;
	virtual int16 GetFriendsGroupCount() = 0;
	virtual int16 GetFriendsGroupIDByIndex( int16 iGroupIndex ) = 0;
	virtual const char * GetFriendsGroupName( int16 iGroupID ) = 0;
	virtual int16 GetFriendsGroupMembershipCount( int16 iGroupID ) = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetFirstFriendsGroupMember, int16, iGroupID) /*virtual CSteamID GetFirstFriendsGroupMember( int16 iGroupID ) = 0;*/
		STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetNextFriendsGroupMember, int16, iGroupID) /*virtual CSteamID GetNextFriendsGroupMember( int16 iGroupID ) = 0;*/
		virtual int16 GetGroupFriendsMembershipCount( CSteamID steamID ) = 0;
	virtual int16 GetFirstGroupFriendsMember( CSteamID steamID ) = 0;
	virtual int16 GetNextGroupFriendsMember( CSteamID steamID ) = 0;

	virtual const char * GetPlayerNickname( CSteamID playerSteamID ) = 0;
	virtual bool SetPlayerNickname( CSteamID playerSteamID, const char *cszNickname ) = 0;

	virtual uint32 GetFriendsSteamLevel( CSteamID steamIDFriend ) = 0;

	virtual int32 GetChatMessagesCount( CSteamID steamIDFriend ) = 0;
	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	virtual int32 GetChatMessage( CSteamID steamIDFriend, int32 iChatID, void *pvData, int32 cubData, EChatEntryType *peChatEntryType, CSteamID* pSteamIDChatter, RTime32 *puTime ) = 0;

	// generic friend->friend message sending, takes a sized buffer
	virtual bool SendMsgToFriend( CSteamID steamIDFriend, EChatEntryType eChatEntryType, const void *pvMsgBody, int32 cubMsgBody ) = 0;

	// clears the chat history - should be called when a chat dialog closes
	virtual void ClearChatHistory( CSteamID steamIDFriend ) = 0;

	virtual int32 GetKnownClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetKnownClanByIndex, int32, iClan) /*virtual CSteamID GetKnownClanByIndex( int32 iClan ) = 0;*/
		virtual int32 GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int32, iClan) /*virtual CSteamID GetClanByIndex( int32 iClan ) = 0;*/

		virtual const char *GetClanName( CSteamID steamIDClan ) = 0;
	virtual const char *GetClanTag( CSteamID steamIDClan ) = 0;

	virtual bool GetFriendActivityCounts( int32 *pnOnline, int32 *pnInGame, bool bExcludeTaggedFriends ) = 0;
	virtual bool GetClanActivityCounts( CSteamID steamID, int32 *pnOnline, int32 *pnInGame, int32 *pnChatting ) = 0;

	virtual SteamAPICall_t DownloadClanActivityCounts( CSteamID groupIDs[], int32 nIds ) = 0;
	virtual bool GetFriendsGroupActivityCounts( int16 iGroupID, int32 *pnOnline, int32 *pnInGame ) = 0;

	virtual bool IsClanPublic( CSteamID steamID ) = 0;
	virtual bool IsClanLarge( CSteamID steamID ) = 0;

	virtual void SubscribeToPersonaStateFeed( CSteamID steamID, bool bSubscribed ) = 0;

	virtual SteamAPICall_t JoinClanChatRoom( CSteamID groupID ) = 0;
	virtual bool LeaveClanChatRoom( CSteamID groupID ) = 0;
	virtual int32 GetClanChatMemberCount( CSteamID groupID ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatMemberByIndex, CSteamID, groupID, int32, iIndex) /*virtual CSteamID GetChatMemberByIndex( CSteamID groupID, int32 iIndex ) = 0;*/
		virtual bool SendClanChatMessage( CSteamID groupID, const char *cszMessage ) = 0;
	virtual int32 GetClanChatMessage( CSteamID groupID, int32 iChatID, void *pvData, int32 cubData, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter ) = 0;
	virtual bool IsClanChatAdmin( CSteamID groupID, CSteamID userID ) = 0;
	virtual bool IsClanChatWindowOpenInSteam( CSteamID groupID ) = 0;
	virtual bool OpenClanChatWindowInSteam( CSteamID groupID ) = 0;
	virtual bool CloseClanChatWindowInSteam( CSteamID groupID ) = 0;
	virtual bool SetListenForFriendsMessages( bool bListen ) = 0;
	virtual bool ReplyToFriendMessage( CSteamID friendID, const char *cszMessage ) = 0;
	virtual int32 GetFriendMessage( CSteamID friendID, int32 iChatID, void *pvData, int32 cubData, EChatEntryType *peChatEntryType ) = 0;

	virtual bool InviteFriendToClan( CSteamID steamIDfriend, CSteamID steamIDclan ) = 0;
	virtual bool AcknowledgeInviteToClan( CSteamID steamID, bool bAcceptOrDenyClanInvite ) = 0;

	// iterators for any source
	virtual int32 GetFriendCountFromSource( CSteamID steamIDSource ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int32, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int32 iFriend ) = 0;*/
		virtual bool IsUserInSource( CSteamID steamIDUser, CSteamID steamIDSource ) = 0;

	virtual int32 GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int32, iCoplayEvent) /*virtual CSteamID GetCoplayFriend( int32 iCoplayEvent ) = 0;*/

		virtual RTime32 GetFriendCoplayTime( CSteamID steamIDFriend ) = 0;
	virtual AppId_t GetFriendCoplayGame( CSteamID steamIDFriend ) = 0;

	virtual bool SetRichPresence( AppId_t nAppId, const char *pchKey, const char *pchValue ) = 0;
	virtual void ClearRichPresence( AppId_t nAppId ) = 0;
	virtual const char* GetFriendRichPresence( AppId_t nAppId, CSteamID steamIDFriend, const char *pchKey ) = 0;
	virtual int32 GetFriendRichPresenceKeyCount( AppId_t nAppId, CSteamID steamIDFriend ) = 0;
	virtual const char* GetFriendRichPresenceKeyByIndex( AppId_t nAppId, CSteamID steamIDFriend, int32 iIndex ) = 0;

	virtual void RequestFriendRichPresence( AppId_t nAppId, CSteamID steamIDFriend ) = 0;

	virtual bool JoinChatRoom( CSteamID steamIDChat ) = 0;
	virtual void LeaveChatRoom( CSteamID steamIDChat ) = 0;

	virtual bool InviteUserToChatRoom( CSteamID steamIDChat, CSteamID steamIDInvitee ) = 0;

	virtual bool SendChatMsg( CSteamID steamIDChat, EChatEntryType eChatEntryType, const void *pvMsgBody, int32 cubMsgBody ) = 0;

	virtual int32 GetChatRoomMessagesCount( CSteamID steamIDChat ) = 0;

	virtual int32 GetChatRoomEntry( CSteamID steamIDChat, int32 iChatID, CSteamID *steamIDuser, void *pvData, int32 cubData, EChatEntryType *peChatEntryType ) = 0;

	virtual void ClearChatRoomHistory( CSteamID steamID ) = 0;

	virtual bool SerializeChatRoomDlg( CSteamID steamIDChat, void const* pvHistory, int32 cubHistory ) = 0;
	virtual int32 GetSizeOfSerializedChatRoomDlg( CSteamID steamIDChat ) = 0;
	virtual bool GetSerializedChatRoomDlg( CSteamID steamIDChat, void* pvHistory, int32 cubBuffer, int32* pcubData ) = 0;
	virtual bool ClearSerializedChatRoomDlg( CSteamID steamIDChat ) = 0;

	virtual bool KickChatMember( CSteamID steamIDChat, CSteamID steamIDUserToActOn ) = 0;
	virtual bool BanChatMember( CSteamID steamIDChat, CSteamID steamIDUserToActOn ) = 0;
	virtual bool UnBanChatMember( CSteamID steamIDChat, CSteamID steamIDUserToActOn ) = 0;

	virtual bool SetChatRoomType( CSteamID steamIDChat, ELobbyType eLobbyType ) = 0;
	virtual bool GetChatRoomLockState( CSteamID steamIDChat, bool *pbLocked ) = 0;
	virtual bool GetChatRoomPermissions( CSteamID steamIDChat, uint32 *prgfChatRoomPermissions ) = 0;

	virtual bool SetChatRoomModerated( CSteamID steamIDChat, bool bModerated ) = 0;
	virtual bool BChatRoomModerated( CSteamID steamIDChat ) = 0;

	virtual bool NotifyChatRoomDlgsOfUIChange( CSteamID steamIDChat, bool bShowAvatars, bool bBeepOnNewMsg, bool bShowSteamIDs, bool bShowTimestampOnNewMsg ) = 0;

	virtual bool TerminateChatRoom( CSteamID steamIDChat ) = 0;

	virtual int32 GetChatRoomCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetChatRoomByIndex, int32, iChatRoom) /*virtual CSteamID GetChatRoomByIndex( int32 iChatRoom ) = 0;*/

		virtual const char *GetChatRoomName( CSteamID steamIDChat ) = 0;

	virtual bool BGetChatRoomMemberDetails( CSteamID steamIDChat, CSteamID steamIDUser, uint32* prgfChatMemberDetails, uint32* prgfChatMemberDetailsLocal ) = 0;

	virtual void CreateChatRoom( EChatRoomType eType, uint64 ulGameID, const char *pchName, ELobbyType eLobbyType, CSteamID steamIDClan, CSteamID steamIDFriendChat, CSteamID steamIDInvited, uint32 rgfChatPermissionOfficer, uint32 rgfChatPermissionMember, uint32 rgfChatPermissionAll ) = 0;

	virtual void VoiceCall( CSteamID steamIDLocalPeer, CSteamID steamIDRemotePeer ) = 0;
	virtual void VoiceHangUp( HVoiceCall hVoiceCall ) = 0;

	virtual void SetVoiceSpeakerVolume( float flVolume ) = 0;
	virtual void SetVoiceMicrophoneVolume( float flVolume ) = 0;

	virtual void SetAutoAnswer( bool bAutoAnswer ) = 0;

	virtual void VoiceAnswer( HVoiceCall hVoiceCall ) = 0;

	virtual void VoicePutOnHold( HVoiceCall HVoiceCall, bool bLocalHold ) = 0;
	virtual bool BVoiceIsLocalOnHold( HVoiceCall hVoiceCall ) = 0;
	virtual bool BVoiceIsRemoteOnHold( HVoiceCall hVoiceCall ) = 0;

	virtual void SetDoNotDisturb( bool bDoNotDisturb ) = 0;

	virtual void EnableVoiceNotificationSounds( bool bEnable ) = 0;

	virtual void SetPushToTalkEnabled( bool bEnable ) = 0;
	virtual bool IsPushToTalkEnabled() = 0;

	virtual void SetPushToTalkKey( int32 nVirtualKey ) = 0;
	virtual int32 GetPushToTalkKey() = 0;

	virtual bool IsPushToTalkKeyDown() = 0;

	virtual void EnableVoiceCalibration( bool bState ) = 0;
	virtual bool IsVoiceCalibrating() = 0;
	virtual float GetVoiceCalibrationSamplePeak() = 0;

	virtual void SetMicBoost( bool bBoost ) = 0;
	virtual bool GetMicBoost() = 0;

	virtual bool HasHardwareMicBoost() = 0;

	virtual const char *GetMicDeviceName() = 0;

	virtual void StartTalking( HVoiceCall hVoiceCall ) = 0;
	virtual void EndTalking( HVoiceCall hVoiceCall ) = 0;

	virtual bool VoiceIsValid( HVoiceCall hVoiceCall ) = 0;

	virtual void SetAutoReflectVoice( bool bState ) = 0;

	virtual ECallState GetCallState( HVoiceCall hVoiceCall ) = 0;

	virtual float GetVoiceMicrophoneVolume() = 0;
	virtual float GetVoiceSpeakerVolume() = 0;

	virtual float TimeSinceLastVoiceDataReceived( HVoiceCall hVoiceCall ) = 0;
	virtual float TimeSinceLastVoiceDataSend( HVoiceCall hVoiceCall ) = 0;

	virtual bool BCanSend( HVoiceCall hVoiceCall ) = 0;
	virtual bool BCanReceive( HVoiceCall hVoiceCall ) = 0;

	virtual float GetEstimatedBitsPerSecond( HVoiceCall hVoiceCall, bool bIncoming ) = 0;
	virtual float GetPeakSample( HVoiceCall hVoiceCall, bool bIncoming ) = 0;

	virtual void SendResumeRequest( HVoiceCall hVoiceCall ) = 0;

	virtual void OpenChatDialog( CSteamID steamID ) = 0;

	virtual void StartChatRoomVoiceSpeaking( CSteamID steamIDChat, CSteamID steamIDMember ) = 0;
	virtual void EndChatRoomVoiceSpeaking( CSteamID steamIDChat, CSteamID steamIDMember ) = 0;

	virtual RTime32 GetFriendLastLogonTime( CSteamID steamIDFriend ) = 0;
	virtual RTime32 GetFriendLastLogoffTime( CSteamID steamIDFriend ) = 0;

	virtual int32 GetChatRoomVoiceTotalSlotCount( CSteamID steamIDChat ) = 0;
	virtual int32 GetChatRoomVoiceUsedSlotCount( CSteamID steamIDChat ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatRoomVoiceUsedSlot, CSteamID, steamIDChat, int32, iSlot) /*virtual CSteamID GetChatRoomVoiceUsedSlot( CSteamID steamIDChat, int32 iSlot ) = 0;*/
		virtual EChatRoomVoiceStatus GetChatRoomVoiceStatus( CSteamID steamIDChat, CSteamID steamIDSpeaker ) = 0;

	virtual bool BChatRoomHasAvailableVoiceSlots( CSteamID steamIDChat ) = 0;

	virtual bool BIsChatRoomVoiceSpeaking( CSteamID steamIDChat, CSteamID steamIDSpeaker ) = 0;

	virtual float GetChatRoomPeakSample( CSteamID steamIDChat, CSteamID steamIDSpeaker, bool bIncoming ) = 0;

	virtual void ChatRoomVoiceRetryConnections( CSteamID steamIDChat ) = 0;

	virtual void SetPortTypes( uint32 unFlags ) = 0;

	virtual void ReinitAudio() = 0;

	virtual void SetInGameVoiceSpeaking( CSteamID steamIDUser, bool bSpeaking ) = 0;

	virtual bool IsInGameVoiceSpeaking() = 0;

	virtual void ActivateGameOverlay( const char *pchDialog ) = 0;
	virtual void ActivateGameOverlayToUser( const char *pchDialog, CSteamID steamID ) = 0;
	virtual void ActivateGameOverlayToWebPage( const char *pchURL ) = 0;
	virtual void ActivateGameOverlayToStore( AppId_t nAppId, EOverlayToStoreFlag eFlag ) = 0;
	virtual void ActivateGameOverlayInviteDialog( CSteamID steamIDLobby ) = 0;

	virtual void NotifyGameOverlayStateChanged( bool bActive ) = 0;
	virtual void NotifyGameServerChangeRequested( const char *pchServerAddress, const char *pchPassword ) = 0;
	virtual bool NotifyLobbyJoinRequested( AppId_t nAppId, CSteamID steamIDLobby, CSteamID steamIDFriend ) = 0;
	virtual bool NotifyRichPresenceJoinRequested( AppId_t nAppId, CSteamID steamIDFriend, const char *pchConnectString ) = 0;

	virtual EClanRelationship GetClanRelationship( CSteamID steamIDclan ) = 0;

	virtual EClanRank GetFriendClanRank( CSteamID steamIDUser, CSteamID steamIDClan ) = 0;

	virtual bool VoiceIsAvailable() = 0;

	virtual void TestVoiceDisconnect( HVoiceCall hVoiceCall ) = 0;
	virtual void TestChatRoomPeerDisconnect( CSteamID steamIDChat, CSteamID steamIDSpeaker ) = 0;
	virtual void TestVoicePacketLoss( float flFractionOfIncomingPacketsToDrop ) = 0;

	virtual HVoiceCall FindFriendVoiceChatHandle( CSteamID steamIDFriend ) = 0;

	virtual void RequestFriendsWhoPlayGame( CGameID gameID ) = 0;
	virtual uint32 GetCountFriendsWhoPlayGame( CGameID gameID ) = 0;

	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendWhoPlaysGame, uint32, iIndex, CGameID, gameID) /*virtual CSteamID GetFriendWhoPlaysGame( uint32 iIndex, CGameID gameID ) = 0;*/
		virtual void SetPlayedWith( CSteamID steamIDUserPlayedWith ) = 0;

	virtual SteamAPICall_t RequestClanOfficerList( CSteamID steamIDClan ) = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		virtual int32 GetClanOfficerCount( CSteamID steamIDClan ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int32, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int32 iOfficer ) = 0;*/

		virtual EUserRestriction GetUserRestrictions() = 0;

	virtual SteamAPICall_t RequestFriendProfileInfo( CSteamID steamIDFriend ) = 0;
	// Available keys: TimeCreated, RealName, CityName, StateName, CountryName, Headline, Playtime, Summary
	virtual const char* GetFriendProfileInfo( CSteamID steamIDFriend, const char* pchKey ) = 0;

	virtual bool InviteUserToGame( CSteamID steamIDFriend, const char *pchConnectString ) = 0;

	virtual int32 GetOnlineConsoleFriendCount() = 0;

	virtual SteamAPICall_t RequestTrade( CSteamID steamIDPartner ) = 0;
	virtual void TradeResponse( uint32 unTradeRequestID, bool bAccept ) = 0;
	virtual void CancelTradeRequest( CSteamID steamIDPartner ) = 0;

	virtual bool HideFriend( CSteamID steamIDFriend, bool bHide ) = 0;
	virtual const char * GetFriendFacebookName( CSteamID steamIDFriend ) = 0;
	virtual uint64 GetFriendFacebookID( CSteamID steamIDFriend ) = 0;

	virtual SteamAPICall_t GetFollowerCount( CSteamID steamID ) = 0;
	virtual SteamAPICall_t IsFollowing( CSteamID steamID ) = 0;
	virtual SteamAPICall_t EnumerateFollowingList( uint32 uStartIndex ) = 0;

	virtual bool BOfflineMessagesEnabled() = 0;
	virtual void RequestFriendMessageHistory( CSteamID steamIDFriend ) = 0;
	virtual void RequestFriendMessageHistoryForOfflineMessages() = 0;

	virtual void RequestEmoticonList() = 0;
	virtual int32 GetEmoticonCount() = 0;
	virtual const char *GetEmoticonName( int32 iEmoticon ) = 0;
};

#endif // ICLIENTFRIENDS_H
