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

#ifndef ISTEAM005_H
#define ISTEAM005_H
#ifdef _WIN32
#pragma once
#endif


abstract_class ISteam005
{
public:
	#if defined(_WIN32) && defined(__GNUC__) && !defined(_S4N_)
		// We can't use the real destructor name here because gcc will put 2 destructors in the vtable.
		virtual void _ISteam005() = 0;
	#else
		virtual ~ISteam005() = 0;
	#endif

	virtual SteamCallHandle_t ChangePassword(const char* cszCurrentPassphrase, const char* cszNewPassphrase, TSteamError* pError) = 0;
	virtual int GetCurrentEmailAddress(char* szEmailaddress, unsigned int uBufSize, unsigned int* puEmailaddressChars, TSteamError* pError) = 0;
	virtual SteamCallHandle_t ChangePersonalQA(const char* cszCurrentPassphrase, const char* cszNewPersonalQuestion, const char* cszNewAnswerToQuestion, TSteamError* pError) = 0;
	virtual SteamCallHandle_t ChangeEmailAddress(const char* cszNewEmailAddress, TSteamError* pError) = 0;
	virtual SteamCallHandle_t VerifyEmailAddress(const char* cszEmailAddress, TSteamError* pError) = 0;
	virtual SteamCallHandle_t RequestEmailAddressVerificationEmail(TSteamError* pError) = 0;
	virtual SteamCallHandle_t ChangeAccountName(const char* cszCurrentPassphrase, const char* cszNewAccountName, TSteamError* pError) = 0;
	virtual int MountAppFilesystem(TSteamError* pError) = 0;
	virtual int UnmountAppFilesystem(TSteamError* pError) = 0;
	virtual SteamHandle_t MountFilesystem(unsigned int uAppId, const char* szMountPath, TSteamError* pError) = 0;
	virtual int UnmountFilesystem(SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual int Stat(const char* cszName, TSteamElemInfo* pInfo, TSteamError* pError) = 0;
	virtual int SetvBuf(SteamHandle_t hFile, void* pBuf, ESteamBufferMethod eMethod, unsigned int uBytes, TSteamError* pError) = 0;
	virtual int FlushFile(SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual SteamHandle_t OpenFile(const char* cszName, const char* cszMode, TSteamError* pError) = 0;
	virtual SteamHandle_t OpenFileEx(const char* cszFileName, const char* cszMode, unsigned int* puFileSize, TSteamError* pError) = 0;
	virtual SteamHandle_t OpenTmpFile(TSteamError* pError) = 0;
	virtual void ClearError(TSteamError* pError) = 0;
	virtual int GetVersion(char* szVersion, unsigned int uVersionBufSize) = 0;
	virtual int GetOfflineStatus(TSteamOfflineStatus* pSteamOfflineStatus, TSteamError* pError) = 0;
	virtual int ChangeOfflineStatus(TSteamOfflineStatus* pSteamOfflineStatus, TSteamError* pError) = 0;
	virtual int ProcessCall(SteamCallHandle_t handle, TSteamProgress* pProgress, TSteamError* pError) = 0;
	virtual int AbortCall(SteamCallHandle_t handle, TSteamError* pError) = 0;
	virtual int BlockingCall(SteamCallHandle_t handle, unsigned int uiProcessTickMS, TSteamError* pError) = 0;
	virtual int SetMaxStallCount(unsigned int uNumStalls, TSteamError* pError) = 0;
	virtual int CloseFile(SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual unsigned int ReadFile(void* pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual unsigned int WriteFile(const void* pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual int Getc(SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual int Putc(int cChar, SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual int SeekFile(SteamHandle_t hFile, long lOffset, ESteamSeekMethod eMethod, TSteamError* pError) = 0;
	virtual long TellFile(SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual int SizeFile(SteamHandle_t hFile, TSteamError* pError) = 0;
	virtual SteamHandle_t FindFirst(const char* cszPattern, ESteamFindFilter eFilter, TSteamElemInfo* pFindInfo, TSteamError* pError) = 0;
	virtual int FindNext(SteamHandle_t hFind, TSteamElemInfo* pFindInfo, TSteamError* pError) = 0;
	virtual int FindClose(SteamHandle_t hFind, TSteamError* pError) = 0;
	virtual int GetLocalFileCopy(const char* cszName, TSteamError* pError) = 0;
	virtual int IsFileImmediatelyAvailable(const char* cszName, TSteamError* pError) = 0;
	virtual int HintResourceNeed(const char* cszMasterList, int bForgetEverything, TSteamError* pError) = 0;
	virtual int ForgetAllHints(TSteamError* pError) = 0;
	virtual int PauseCachePreloading(TSteamError* pError) = 0;
	virtual int ResumeCachePreloading(TSteamError* pError) = 0;
	virtual SteamCallHandle_t WaitForResources(const char* cszMasterList, TSteamError* pError) = 0;
	virtual int StartEngine(TSteamError* pError) = 0;
	virtual int ShutdownEngine(TSteamError* pError) = 0;
	virtual int Startup(unsigned int uUsingMask, TSteamError* pError) = 0;
	virtual int Cleanup(TSteamError* pError) = 0;
	virtual unsigned int NumAppsRunning(TSteamError* pError) = 0;
	virtual SteamCallHandle_t CreateAccount(const char* cszUser, const char* cszEmailAddress, const char* cszPassphrase, const char* cszCreationKey, const char* cszPersonalQuestion, const char* cszAnswerToQuestion, int* pbCreated, TSteamError* pError) = 0;
	virtual SteamCallHandle_t GenerateSuggestedAccountNames(const char* cszAccountNameToSelectMasterAS, const char* cszGenerateNamesLikeAccountName, char* pSuggestedNamesBuf, unsigned int uBufSize, unsigned int* puNumSuggestedChars, TSteamError* pError) = 0;
	virtual int IsLoggedIn(int* pbIsLoggedIn, TSteamError* pError) = 0;
	virtual SteamCallHandle_t Logout(TSteamError* pError) = 0;
	virtual int IsSecureComputer(int* pbIsSecureComputer, TSteamError* pError) = 0;
	virtual SteamHandle_t CreateLogContext(const char* cszName) = 0;
	virtual int Log(SteamHandle_t hContext, const char* cszMsg) = 0;
	virtual void LogResourceLoadStarted(const char* cszMsg) = 0;
	virtual void LogResourceLoadFinished(const char* cszMsg) = 0;
	virtual SteamCallHandle_t RefreshLogin(const char* cszPassphrase, int bIsSecureComputer, TSteamError* pError) = 0;
	virtual int VerifyPassword(const char* cszPassphrase, int* pbCorrect, TSteamError* pError) = 0;
	virtual int GetUserType(unsigned int* puUserTypeFlags, TSteamError* pError) = 0;
	virtual int GetAppStats(TSteamAppStats* pAppStats, TSteamError* pError) = 0;
	virtual SteamCallHandle_t IsAccountNameInUse(const char* cszAccountName, int* pbIsUsed, TSteamError* pError) = 0;
	virtual int GetAppIds(unsigned int puIds[], unsigned int uMaxIds, TSteamError* pError) = 0;
	virtual int GetSubscriptionStats(TSteamSubscriptionStats* pSubscriptionStats, TSteamError* pError) = 0;
	virtual SteamCallHandle_t RefreshAccountInfo(int bContentDescriptionOnly, TSteamError* pError) = 0;
	virtual SteamCallHandle_t Subscribe(unsigned int uSubscriptionId, const TSteamSubscriptionBillingInfo* pSubscriptionBillingInfo, TSteamError* pError) = 0;
	virtual SteamCallHandle_t Unsubscribe(unsigned int uSubscriptionId, TSteamError* pError) = 0;
	virtual int GetSubscriptionReceipt(unsigned int uSubscriptionId , TSteamSubscriptionReceipt* pSteamSubscriptionReceipt, TSteamError* pError) = 0;
	virtual int GetAccountStatus(unsigned int* puAccountStatusFlags, TSteamError* pError) = 0;
	virtual SteamCallHandle_t SetUser(const char* cszUser, int* pbUserSet, TSteamError* pError) = 0;
	virtual int GetUser(char* szUser, unsigned int uBufSize, unsigned int* puUserChars, TSteamGlobalUserID* pOptionalReceiveUserID, TSteamError* pError) = 0;
	virtual SteamCallHandle_t Login(const char* cszUser, const char* cszPassphrase, int bIsSecureComputer, TSteamError* pError) = 0;
	virtual SteamCallHandle_t AckSubscriptionReceipt(unsigned int uSubscriptionId, TSteamError* pError) = 0;
	virtual int IsAppSubscribed(unsigned int uAppId, int* pbIsAppSubscribed, int* pbIsSubscriptionPending, TSteamError* pError) = 0;
	virtual int GetSubscriptionIds(unsigned int puIds[], unsigned int uMaxIds, TSteamError* pError) = 0;
	virtual int EnumerateSubscription(unsigned int uSubscriptionId, TSteamSubscription* pSubscription, TSteamError* pError) = 0;
	virtual int EnumerateSubscriptionDiscount(unsigned int uSubscriptionId, unsigned int uDiscountIndex, TSteamSubscriptionDiscount* pSteamSubscriptionDiscount, TSteamError* pError) = 0;
	virtual int EnumerateSubscriptionDiscountQualifier(unsigned int uSubscriptionId, unsigned int uDiscountIndex, unsigned int uQualifierIndex, TSteamDiscountQualifier* pSteamDiscountQualifier, TSteamError* pError) = 0;
	virtual int EnumerateApp(unsigned int uAppId, TSteamApp* pApp, TSteamError* pError) = 0;
	virtual int EnumerateAppLaunchOption(unsigned int uAppId, unsigned int uLaunchOptionIndex, TSteamAppLaunchOption* pLaunchOption, TSteamError* pError) = 0;
	virtual SteamCallHandle_t DeleteAccount(TSteamError* pError) = 0;
	virtual int EnumerateAppIcon(unsigned int uAppId, unsigned int uIconIndex, unsigned char* pIconData, unsigned int uIconDataBufSize,  unsigned int* puSizeOfIconData, TSteamError* pError) = 0;
	virtual SteamCallHandle_t LaunchApp(unsigned int uAppId, unsigned int uLaunchOption, const char* cszArgs, TSteamError* pError) = 0;
	virtual int GetCacheFilePath(unsigned int uAppId,  char* szFilePath, unsigned int uBufferLength, unsigned int* puRecievedLength, TSteamError* pError) = 0;
	virtual int EnumerateAppVersion(unsigned int uAppId, unsigned int uVersionIndex, TSteamAppVersion* pAppVersion, TSteamError* pError) = 0;
	virtual int EnumerateAppDependency(unsigned int uAppId, unsigned int uIndex, TSteamAppDependencyInfo* pDependencyInfo, TSteamError* pError) = 0;
	virtual SteamCallHandle_t StartLoadingCache(unsigned int uAppId, TSteamError* pError) = 0;
	virtual int InsertAppDependency(unsigned int uAppId, unsigned int uFileSystemIndex, TSteamAppDependencyInfo* pDependencyInfo, TSteamError* pError) = 0;
	virtual int RemoveAppDependency(unsigned int uAppId, unsigned int uFileSystemIndex, TSteamError* pError) = 0;
	virtual int FindApp(const char* cszAppName, unsigned int* puAppId, TSteamError* pError) = 0;
	virtual int GetAppDependencies(unsigned int uAppId, unsigned int puCacheIds[], unsigned int uMaxIds, TSteamError* pError) = 0;
	virtual int IsSubscribed(unsigned int uSubscriptionId, int* pbIsSubscribed, int* pbIsSubscriptionPending, TSteamError* pError) = 0;
	virtual int GetAppUserDefinedInfo(unsigned int uAppId, const char* cszPropertyName, char* szPropertyValue, unsigned int uBufSize, unsigned int* puPropertyValueLength, TSteamError* pError) = 0;
	virtual SteamCallHandle_t WaitForAppReadyToLaunch(unsigned int uAppId, TSteamError* pError) = 0;
	virtual int IsCacheLoadingEnabled(unsigned int uAppId, int* pbIsLoading, TSteamError* pError) = 0;
	virtual SteamCallHandle_t StopLoadingCache(unsigned int uAppId, TSteamError* pError) = 0;
	virtual ESteamError GetEncryptedUserIDTicket(const void* pEncryptionKeyReceivedFromAppServer, unsigned int uEncryptionKeyLength, void* pOutputBuffer, unsigned int uSizeOfOutputBuffer, unsigned int* pReceiveSizeOfEncryptedTicket, TSteamError* pError) = 0;
	virtual SteamCallHandle_t FlushCache(unsigned int uAppId, TSteamError* pError) = 0;
	virtual SteamCallHandle_t RepairOrDecryptCaches(unsigned int uAppId, int bForceValidation, TSteamError* pError) = 0;
	virtual SteamCallHandle_t LoadCacheFromDir(unsigned int uAppId, const char* cszPath, TSteamError* pError) = 0;
	virtual int GetCacheDefaultDirectory(char* szPath, TSteamError* pError) = 0;
	virtual int SetCacheDefaultDirectory(const char* cszPath, TSteamError* pError) = 0;
	virtual int GetAppDir(unsigned int uAppId, char* szAppDir, TSteamError* pError) = 0;
	virtual SteamCallHandle_t MoveApp(unsigned int uAppId, const char* szPath, TSteamError* pError) = 0;
	virtual SteamCallHandle_t GetAppCacheSize(unsigned int uAppId, unsigned int* puCacheSizeInMb, TSteamError* pError) = 0;
	virtual SteamCallHandle_t SetAppCacheSize(unsigned int uAppId, unsigned int uCacheSizeInMb, TSteamError* pError) = 0;
	virtual SteamCallHandle_t SetAppVersion(unsigned int uAppId, unsigned int uAppVersionId, TSteamError* pError) = 0;
	virtual SteamCallHandle_t Uninstall(TSteamError* pError) = 0;
	virtual int SetNotificationCallback(SteamNotificationCallback_t pCallbackFunction, TSteamError* pError) = 0;
	virtual SteamCallHandle_t ChangeForgottenPassword(const char* cszUser, const char* cszAnswerToQuestion, const char* cszEmailVerificationKey, const char* cszNewPassphrase, int* pbChanged, TSteamError* pError) = 0;
	virtual SteamCallHandle_t RequestForgottenPasswordEmail(const char* cszUser, char* ReceivePersonalQuestion, TSteamError* pError) = 0;
	virtual SteamCallHandle_t RequestAccountsByEmailAddressEmail(const char* cszEmailAddress, TSteamError* pError) = 0;
	virtual SteamCallHandle_t RequestAccountsByCdKeyEmail(const char* cszCdKey, TSteamError* pError) = 0;
	virtual SteamCallHandle_t GetNumAccountsWithEmailAddress(const char *cszEmailAddress, unsigned int *puNumAccounts, TSteamError* pError) = 0;
	virtual SteamCallHandle_t UpdateAccountBillingInfo(const TSteamPaymentCardInfo* pPaymentCardInfo, TSteamError* pError) = 0;
	virtual SteamCallHandle_t UpdateSubscriptionBillingInfo(unsigned int uSubscriptionId, const TSteamSubscriptionBillingInfo* pSubscriptionBillingInfo, TSteamError* pError) = 0;
	virtual int GetSponsorUrl(unsigned int uAppId, char* szUrl, unsigned int uBufSize, unsigned int* pUrlChars, TSteamError* pError) = 0;
	virtual int GetContentServerInfo(unsigned int uAppId, unsigned int* puServerId, unsigned int* puServerIpAddress, TSteamError* pError) = 0;
	virtual SteamCallHandle_t GetAppUpdateStats(unsigned int uAppOrCacheId, ESteamAppUpdateStatsQueryType eQueryType, TSteamUpdateStats* pUpdateStats, TSteamError* pError) = 0;
	virtual int GetTotalUpdateStats(TSteamUpdateStats* pUpdateStats, TSteamError* pError) = 0;
	virtual SteamCallHandle_t CreateCachePreloaders(TSteamError* pError) = 0;
	
	// ISteam004
	virtual void Win32SetMiniDumpComment(const char* cszComment) = 0;
	virtual void Win32SetMiniDumpSourceControlId(unsigned int uSourceControlId) = 0;
	virtual void Win32SetMiniDumpEnableFullMemory() = 0;
	virtual void Win32WriteMiniDump(const char* szErrorOrAssertType, const char* szDescriptionOrAssertName, const char* szAssertExpr, const char* szAssertFilename, unsigned int uAssertLineNumber) = 0;
	virtual int GetCurrentAppId(unsigned int* puAppId, TSteamError* pError) = 0;
	virtual int GetAppPurchaseCountry(unsigned int uAppId, char* szCountryCode, unsigned int uBufferLength, int* piRecievedLength, TSteamError* pError) = 0;
	
	// ISteam005
	virtual int GetLocalClientVersion(unsigned int* puBootStrapperVersionNum, unsigned int* puClientAppVersionNum, TSteamError* pError) = 0;
	virtual int IsFileNeededByCache(unsigned int uCacheId, const char* cszFileName, unsigned int uFileSize, TSteamError* pError) = 0;
	virtual int LoadFileToCache(unsigned int uCacheId, const char* pchFileName, const void* pubDataChunk, unsigned int cubDataChunk, unsigned int cubDataOffset, TSteamError* pError) = 0;
	virtual int GetCacheDecryptionKey(unsigned int uAppId, char* szCacheDecryptionKey, unsigned int uBufferLength, unsigned int* puRecievedLength, TSteamError* pError) = 0;
	virtual int GetSubscriptionExtendedInfo(unsigned int uSubscriptionId, const char* cszKeyName, char* szKeyValue, unsigned int uBufferLength, unsigned int* puRecievedLength, TSteamError* pError) = 0;
	virtual int GetSubscriptionPurchaseCountry(unsigned int uSubscriptionId, char* szCountry, unsigned int uBufSize , int* pPurchaseTime, TSteamError* pError) = 0;
	virtual int GetAppUserDefinedRecord(unsigned int uAppId, KeyValueIteratorCallback_t AddEntryToKeyValueFunc, void* pvCKeyValue, TSteamError* pError) = 0;
};


#define STEAM_INTERFACE_VERSION_005 "Steam005"

#endif // ISTEAM005_H
