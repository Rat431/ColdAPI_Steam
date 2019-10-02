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

#ifndef ICLIENTUSER_H
#define ICLIENTUSER_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "UserCommon.h"
#include "ContentServerCommon.h"

// Protobuf'ed class
class ClientAppInfo
#ifdef _S4N_
{
	int m_iPadding;
}
#endif
;

abstract_class UNSAFE_INTERFACE IClientUser
{
public:
	virtual HSteamUser GetHSteamUser() = 0;

	virtual void LogOn( bool bInteractive, CSteamID steamID ) = 0;
	virtual void LogOnWithPassword( bool bInteractive, const char * pchLogin, const char * pchPassword ) = 0;
	virtual void LogOnAndCreateNewSteamAccountIfNeeded( bool bInteractive ) = 0;
	virtual void LogOff() = 0;
	virtual bool BLoggedOn() = 0;
	virtual ELogonState GetLogonState() = 0;
	virtual bool BConnected() = 0;
	virtual bool BTryingToLogin() = 0;

	STEAMWORKS_STRUCT_RETURN_0(CSteamID, GetSteamID) /*virtual CSteamID GetSteamID() = 0;*/
		STEAMWORKS_STRUCT_RETURN_0(CSteamID, GetConsoleSteamID) /*virtual CSteamID GetConsoleSteamID() = 0;*/

		virtual bool IsVACBanned( AppId_t nGameID ) = 0;
	virtual bool RequireShowVACBannedMessage( AppId_t nAppID ) = 0;
	virtual void AcknowledgeVACBanning( AppId_t nAppID ) = 0;

	virtual void SetSteam2Ticket( uint8* pubTicket, int32 cubTicket ) = 0;

	virtual bool BExistsSteam2Ticket() = 0;

	virtual bool SetEmail( const char *pchEmail ) = 0;

	virtual bool SetConfigString( ERegistrySubTree eRegistrySubTree, const char *pchKey, const char *pchValue ) = 0;
	virtual bool GetConfigString( ERegistrySubTree eRegistrySubTree, const char *pchKey, char *pchValue, int32 cbValue ) = 0;
	virtual bool SetConfigInt( ERegistrySubTree eRegistrySubTree, const char *pchKey, int32 iValue ) = 0;
	virtual bool GetConfigInt( ERegistrySubTree eRegistrySubTree, const char *pchKey, int32 *pValue ) = 0;

	virtual bool GetConfigStoreKeyName( ERegistrySubTree eRegistrySubTree, const char *pchKey, char *pchStoreName, int32 cbStoreName ) = 0;

	virtual int32 InitiateGameConnection( void *pOutputBlob, int32 cbBlobMax, CSteamID steamIDGS, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure ) = 0;
	virtual int32 InitiateGameConnectionOld( void *pOutputBlob, int32 cbBlobMax, CSteamID steamIDGS, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure, void *pvSteam2GetEncryptionKey, int32 cbSteam2GetEncryptionKey ) = 0;

	virtual void TerminateGameConnection( uint32 unIPServer, uint16 usPortServer ) = 0;

	virtual void SetSelfAsPrimaryChatDestination() = 0;
	virtual bool IsPrimaryChatDestination() = 0;

	virtual void RequestLegacyCDKey( AppId_t iAppID ) = 0;

	virtual bool SendGuestPassByEmail( const char *pchEmailAccount, GID_t gidGuestPassID, bool bResending ) = 0;
	virtual bool SendGuestPassByAccountID( uint32 uAccountID, GID_t gidGuestPassID, bool bResending ) = 0;

	virtual bool AckGuestPass( const char *pchGuestPassCode ) = 0;
	virtual bool RedeemGuestPass( const char *pchGuestPassCode ) = 0;

	virtual uint32 GetGuestPassToGiveCount() = 0;
	virtual uint32 GetGuestPassToRedeemCount() = 0;
	virtual uint32 GetGuestPassLastUpdateTime() = 0;

	virtual bool GetGuestPassToGiveInfo( uint32 nPassIndex, GID_t *pgidGuestPassID, PackageId_t* pnPackageID, RTime32* pRTime32Created, RTime32* pRTime32Expiration, RTime32* pRTime32Sent, RTime32* pRTime32Redeemed, char* pchRecipientAddress, int32 cRecipientAddressSize ) = 0;
	virtual bool GetGuestPassToRedeemInfo( uint32 nPassIndex, GID_t *pgidGuestPassID, PackageId_t* pnPackageID, RTime32* pRTime32Created, RTime32* pRTime32Expiration, RTime32* pRTime32Sent, RTime32* pRTime32Redeemed ) = 0;
	virtual bool GetGuestPassToRedeemSenderAddress( uint32 nPassIndex, char* pchSenderAddress, int32 cSenderAddressSize ) = 0;
	virtual bool GetGuestPassToRedeemSenderName( uint32 nPassIndex, char* pchSenderName, int32 cSenderNameSize ) = 0;

	virtual bool RequestGuestPassTargetList( GID_t gidGuestPassID ) = 0;

	virtual bool RequestGiftTargetList( PackageId_t nPackageID ) = 0;

	virtual void AcknowledgeMessageByGID( const char *pchMessageGID ) = 0;

	virtual bool SetLanguage( const char *pchLanguage ) = 0;

	virtual void TrackAppUsageEvent( CGameID gameID, int32 eAppUsageEvent, const char *pchExtraInfo = "" ) = 0;

	virtual int32 RaiseConnectionPriority( EConnectionPriority eConnectionPriority ) = 0;
	virtual void ResetConnectionPriority( int32 hRaiseConnectionPriorityPrev ) = 0;

	virtual void SetAccountNameFromSteam2( const char *pchAccountName ) = 0;
	virtual bool SetPasswordFromSteam2( const char *pchPassword ) = 0;

	virtual bool SetAccountNameForCachedCredentialLogin( const char *pchAccountName, bool bUnk ) = 0;
	virtual void SetLoginInformation( const char *pchAccountName, const char *pchPassword, bool bRememberPassword ) = 0;
	virtual void SetLauncherType( ELauncherType eLauncherType ) = 0;
	virtual void ClearAllLoginInformation() = 0;

	virtual void SetAccountCreationTime( RTime32 rtime32Time ) = 0;

	virtual SteamAPICall_t RequestWebAuthToken() = 0;
	virtual bool GetCurrentWebAuthToken( char *pchBuffer, int32 cubBuffer ) = 0;

	virtual bool GetLanguage( char* pchLanguage, int32 cbLanguage ) = 0;

	virtual bool BIsCyberCafe() = 0;
	virtual bool BIsAcademicAccount() = 0;

	virtual void CreateAccount( const char *pchAccountName, const char *pchNewPassword, const char *pchNewEmail, int32 iQuestion, const char *pchNewQuestion, const char *pchNewAnswer ) = 0;

	virtual SteamAPICall_t ResetPassword( const char *pchAccountName, const char *pchOldPassword, const char *pchNewPassword, const char *pchValidationCode, const char *pchAnswer ) = 0;

	virtual void TrackNatTraversalStat( const CNatTraversalStat *pNatStat ) = 0;

	virtual PackageId_t GetPackageIDForGuestPassToRedeemByGID( GID_t gid ) = 0;

	virtual void TrackSteamUsageEvent( ESteamUsageEvent eSteamUsageEvent, const uint8 *pubKV, uint32 cubKV ) = 0;
	virtual void TrackSteamGUIUsage( const char * ) = 0;

	virtual void SetComputerInUse() = 0;

	virtual bool BIsGameRunning( CGameID gameID ) = 0;


	virtual uint64 GetCurrentSessionToken() = 0;

	virtual bool BUpdateAppOwnershipTicket( AppId_t nAppID, bool bOnlyUpdateIfStale, bool bIsDepot ) = 0;

	virtual bool RequestCustomBinary( const char *pszAbsolutePath, AppId_t nAppID, bool bForceUpdate, bool bAppLaunchRequest ) = 0;
	virtual EResult GetCustomBinariesState( AppId_t unAppID, uint32 *punProgress ) = 0;
	virtual EResult RequestCustomBinaries( AppId_t unAppID, bool, bool, uint32 * ) = 0;

	virtual void SetCellID( CellID_t cellID ) = 0;
	virtual void SetWinningPingTimeForCellID( uint32 uPing ) = 0;

	virtual const char *GetUserBaseFolder() = 0;

	virtual bool GetUserDataFolder( CGameID gameID, char* pchBuffer, int32 cubBuffer ) = 0;
	virtual bool GetUserConfigFolder( char *pchBuffer, int32 cubBuffer ) = 0;

	virtual bool GetAccountName( char* pchAccountName, uint32 cb ) = 0;
	virtual bool IsPasswordRemembered() = 0;

	virtual bool RequiresLegacyCDKey( AppId_t nAppID ) = 0;
	virtual bool GetLegacyCDKey( AppId_t nAppID, char* pchKeyData, int32 cbKeyData ) = 0;
	virtual bool HasLegacyCDKey( AppId_t nAppID ) = 0;
	virtual bool SetLegacyCDKey( AppId_t nAppID, const char* pchKeyData ) = 0;
	virtual void RemoveLegacyCDKey( AppId_t nAppID ) = 0;
	virtual void RequestLegacyCDKeyFromApp( AppId_t nMainAppID, AppId_t nDLCAppID ) = 0;

	virtual bool BIsAnyGameRunning() = 0;

	virtual void TestAvailablePassword( const uint8 *pubDigestPassword, int32 cubDigestPassword ) = 0;
	virtual void GetSteamGuardDetails() = 0;

	virtual void ChangePassword( const char *pchOldPassword, const char *pchNewPassword ) = 0;
	virtual void ChangeEmail( const char *, const char *pchEmail ) = 0;
	virtual void ChangeSecretQuestionAndAnswer( const char *, int32 iQuestion, const char *pchNewQuestion, const char *pchNewAnswer ) = 0;

	virtual void SetSteam2FullASTicket( uint8* pubTicket, int32 cubTicket ) = 0;
	virtual int32 GetSteam2FullASTicket( uint8* pubTicket, int32 cubTicket ) = 0;

	virtual bool GetEmail( char* pchEmail, int32 cchEmail, bool* pbValidated ) = 0;

	virtual void RequestForgottenPasswordEmail( const char *pchAccountName, const char *pchTriedPassword ) = 0;

	virtual void FindAccountsByEmailAddress( const char *pchEmailAddress ) = 0;
	virtual void FindAccountsByCdKey( const char *pchCdKey ) = 0;
	virtual void GetNumAccountsWithEmailAddress( const char * pchEmailAddress ) = 0;
	virtual void IsAccountNameInUse( const char * pchAccountName ) = 0;

	virtual void Test_FakeConnectionTimeout() = 0;

	virtual bool RunInstallScript( AppId_t *pAppIDs, int32 cAppIDs, const char *pchInstallPath, const char *pchLanguage, bool bUninstall ) = 0;

	virtual AppId_t IsInstallScriptRunning() = 0;

	virtual bool GetInstallScriptState( char* pchDescription, uint32 cchDescription, uint32* punNumSteps, uint32* punCurrStep ) = 0;

	virtual bool SpawnProcess( void *lpVACBlob, uint32 cbBlobSize, const char *lpApplicationName, const char *lpCommandLine, uint32 dwCreationFlags, const char *lpCurrentDirectory, CGameID gameID, AppId_t nAppID, const char *pchGameName, bool bAlwaysUseShellExec ) = 0;

	virtual uint32 GetAppOwnershipTicketLength( uint32 nAppID ) = 0;
	virtual uint32 GetAppOwnershipTicketData( uint32 nAppID, void *pvBuffer, uint32 cbBufferLength ) = 0;

	virtual uint32 GetAppOwnershipTicketExtendedData( uint32 nAppID, void *pvBuffer, uint32 cbBufferLength, uint32* piAppId, uint32* piSteamId, uint32* piSignature, uint32* pcbSignature ) = 0;

	virtual int32 GetMarketingMessageCount() = 0;
	virtual bool GetMarketingMessage( int32 cMarketingMessage, GID_t* gidMarketingMessageID, char* pubMsgUrl, int32 cubMessageUrl, EMarketingMessageFlags *eMarketingMssageFlags ) = 0;

	virtual HAuthTicket GetAuthSessionTicket( void *pMyAuthTicket, int32 cbMaxMyAuthTicket, uint32* pcbAuthTicket ) = 0;

	virtual EBeginAuthSessionResult BeginAuthSession( void const* pTheirAuthTicket, int32 cbTicket, CSteamID steamID ) = 0;
	virtual void EndAuthSession( CSteamID steamID ) = 0;

	virtual void CancelAuthTicket( HAuthTicket hAuthTicket ) = 0;

	virtual EUserHasLicenseForAppResult IsUserSubscribedAppInTicket( CSteamID steamID, AppId_t appID ) = 0;

	virtual void AdvertiseGame( CGameID gameID, CSteamID steamIDGameServer, uint32 unIPServer , uint16 usPortServer ) = 0;

	virtual SteamAPICall_t RequestEncryptedAppTicket( const void *pUserData, int32 cbUserData ) = 0;
	virtual bool GetEncryptedAppTicket( void *pTicket, int32 cbMaxTicket, uint32 *pcbTicket ) = 0;

	virtual void SetAccountLimited( bool bAccountLimited ) = 0;
	virtual bool BIsAccountLimited() = 0;

	virtual void SetAccountCommunityBanned( bool bBanned ) = 0;
	virtual bool BIsAccountCommunityBanned() = 0;

	virtual void SendValidationEmail() = 0;
	virtual bool BGameConnectTokensAvailable() = 0;

	virtual int32 NumGamesRunning() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CGameID, GetRunningGameID, int32, iGame) /*virtual CGameID GetRunningGameID( int32 iGame ) = 0;*/

		virtual uint32 GetAccountSecurityPolicyFlags() = 0;

	virtual void RequestChangeEmail( const char *pchPassword, int32 eRequestType ) = 0;
	virtual void ChangePasswordWithCode( const char *pchOldPassword, const char *pchCode, const char *pchNewPassword ) = 0;
	virtual void ChangeEmailWithCode( const char *pchPassword, const char *pchCode, const char *pchEmail, bool bFinal ) = 0;
	virtual void ChangeSecretQuestionAndAnswerWithCode( const char *pchPassword, const char *pchCode, const char *pchNewQuestion, const char *pchNewAnswer ) = 0;

	virtual void SetClientStat( EClientStat eStat, int64 llValue, AppId_t nAppID, DepotId_t nDepotID, CellID_t nCellID ) = 0;

	virtual void VerifyPassword( const char *pchPassword ) = 0;

	virtual bool BSupportUser() = 0;

	virtual bool BIsAppOverlayEnabled( AppId_t nAppID ) = 0;

	virtual bool BIsBehindNAT() = 0;

	virtual AppId_t GetMicroTxnAppID( GID_t gidTransID ) = 0;
	virtual uint64 GetMicroTxnOrderID( GID_t gidTransID ) = 0;

	virtual bool BGetMicroTxnPrice( GID_t gidTransID, CAmount *pamtTotal, CAmount *pamtTax, bool *pbVat ) = 0;

	virtual int32 GetMicroTxnLineItemCount( GID_t gidTransID ) = 0;

	virtual bool BGetMicroTxnLineItem( GID_t gidTransID, uint32 unLineItem, CAmount *pamt, uint32 *punQuantity, char *pchDescription, uint32 cubDescriptionLength, int32 *pRecurringTimeUnit, uint8 *pRecurringFrequency, CAmount *pRecurringAmount, bool * pbUnk ) = 0;

	virtual bool BIsSandboxMicroTxn( GID_t gidTransID, bool* pbSandbox ) = 0;

	virtual bool BMicroTxnRequiresCachedPmtMethod( GID_t gidTransID, bool *pbRequired ) = 0;

	virtual SteamAPICall_t AuthorizeMicroTxn( GID_t gidTransID, EMicroTxnAuthResponse eMicroTxnAuthResponse ) = 0;

	virtual bool BGetWalletBalance( bool *pbHasWallet, CAmount *pamtBalance ) = 0;

	virtual SteamAPICall_t RequestMicroTxnInfo( GID_t gidTransID ) = 0;

	virtual bool BGetAppMinutesPlayed( AppId_t nAppId, int32 *pnForever, int32 *pnLastTwoWeeks ) = 0;
	virtual uint32 GetAppLastPlayedTime( AppId_t nAppId ) = 0;

	virtual bool BGetGuideURL( AppId_t uAppID, char *pchURL, uint32 cchURL ) = 0;

	virtual void GetClientAppListResponse_AddApp( const ClientAppInfo * pClientAppInfo ) = 0;
	virtual void GetClientAppListResponse_AddDLC( AppId_t nAppId, bool bInstalled ) = 0;
	virtual void GetClientAppListResponse_Done( uint64 ulBytesFreeOnDrive ) = 0;
	virtual void PostUIResultToClientJob( uint64 ulJobID, EResult eResult ) = 0;

	virtual bool BPromptToVerifyEmail() = 0;
	virtual bool BPromptToChangePassword() = 0;
	virtual bool BAccountLocked() = 0;
	virtual bool BAccountShouldShowLockUI() = 0;
	virtual bool BAccountLockedByIPT() = 0;
	virtual int32 GetCountAuthedComputers() = 0;

	virtual ESteamGuardProvider GetSteamGuardProvider() = 0;
	virtual bool GetSteamGuardRequireCodeByDefault() = 0;
	virtual bool ShowSteamGuardProviderOptions() = 0;
	virtual bool SteamGuardProviderMobileIsOption() = 0;

	virtual bool BSteamGuardNewMachineNotification() = 0;
	virtual RTime32 GetSteamGuardEnabledTime() = 0;
	virtual bool GetSteamGuardHistoryEntry( int32 iEntryIndex, RTime32 *puTimestamp, uint32 *puIP, bool *pbIsRemembered, char *pchGeolocInfo, int32 cchGeolocInfo ) = 0;
	virtual void SetSteamGuardNewMachineDialogResponse( bool bIsApproved, bool bIsWizardComplete ) = 0;

	virtual bool BAccountCanUseIPT() = 0;
	virtual void ChangeTwoFactorAuthOptions( int32 eOption ) = 0;
	virtual void ChangeSteamGuardOptions( ESteamGuardProvider eProvider, bool bRequireCode ) = 0;
	virtual void Set2ndFactorAuthCode( const char* pchAuthCode, bool bDontRememberComputer ) = 0;
	virtual bool BAccountHasIPTConfig() = 0;

	virtual bool GetEmailDomainFromLogonFailure( char * pchEmailDomain, int32 cbEmailDomain ) = 0;

	virtual bool BIsSubscribedApp( AppId_t nAppId ) = 0;
	virtual SteamAPICall_t RegisterActivationCode( const char * pchActivationCode ) = 0;

	virtual void OptionalDLCInstallation( AppId_t nAppID, bool bInstall ) = 0;

	virtual void AckSystemIM( uint64 ) = 0;

	// Result returned by RequestSpecialSurveyResult_t callback
	virtual SteamAPICall_t RequestSpecialSurvey( uint32 uSurveyId ) = 0;
	// Result returned by SendSpecialSurveyResponseResult_t callback
	virtual SteamAPICall_t SendSpecialSurveyResponse( uint32 uSurveyId, const uint8 * pubData, uint32 cubData ) = 0;

	virtual void RequestNotifications() = 0;

	virtual bool GetAppOwnershipInfo( AppId_t unAppId, RTime32* pRTime32Created, char* pchCountry ) = 0; // Use a 3 bytes buffer for the country

	virtual void SendGameWebCallback( AppId_t unAppId, const char *szData ) = 0;

	virtual bool BIsCurrentlyStreaming() = 0;
	virtual void RequestStopStreaming() = 0;
	virtual void OnBigPictureStreamingResult( bool, void * ) = 0;
	virtual void OnBigPictureStreamingDone() = 0;
	virtual void OnBigPictureStreamRestarting() = 0;
};

#endif // ICLIENTUSER_H
