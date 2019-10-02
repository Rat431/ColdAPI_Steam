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

#ifndef ICLIENTBILLING_H
#define ICLIENTBILLING_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "BillingCommon.h"


enum EPackageStatus
{
};


abstract_class UNSAFE_INTERFACE IClientBilling
{
public:
	virtual bool PurchaseWithActivationCode( const char *pchActivationCode ) = 0;

	virtual bool CancelLicense( PackageId_t packageID, int32 nCancelReason ) = 0;

	virtual PackageId_t GetLicensePackageID( uint32 nLicenseIndex ) = 0;
	virtual RTime32 GetLicenseTimeCreated( uint32 nLicenseIndex ) = 0;
	virtual RTime32 GetLicenseTimeNextProcess( uint32 nLicenseIndex ) = 0;
	virtual int32 GetLicenseMinuteLimit( uint32 nLicenseIndex ) = 0;
	virtual int32 GetLicenseMinutesUsed( uint32 nLicenseIndex ) = 0;
	virtual EPaymentMethod GetLicensePaymentMethod( uint32 nLicenseIndex ) = 0;
	virtual ELicenseFlags GetLicenseFlags( uint32 nLicenseIndex ) = 0;
	virtual const char *GetLicensePurchaseCountryCode( uint32 nLicenseIndex ) = 0;
	virtual int32 GetLicenseTerritoryCode( uint32 nLicenseIndex ) = 0;
	virtual bool GetLicenseInfo( uint32 nLicenseIndex, RTime32* pRTime32Created, RTime32* pRTime32NextProcess, int32* pnMinuteLimit, int32 * pnMinutesUsed, EPaymentMethod* pePaymentMethod, uint32* punFlags, int32 * pnTerritoryCode, char * prgchPurchaseCountryCode /* Use a 3 bytes buffer */) = 0;

	virtual PackageId_t GetReceiptPackageID( uint32 nReceiptIndex ) = 0;
	virtual EPurchaseStatus GetReceiptStatus( uint32 nReceiptIndex ) = 0;
	virtual EPurchaseResultDetail GetReceiptResultDetail( uint32 nReceiptIndex ) = 0;
	virtual RTime32 GetReceiptTransTime( uint32 nReceiptIndex ) = 0;
	virtual uint64 GetReceiptTransID( uint32 nReceiptIndex ) = 0;
	virtual EPaymentMethod GetReceiptPaymentMethod( uint32 nReceiptIndex ) = 0;
	virtual uint32 GetReceiptBaseCost( uint32 nReceiptIndex ) = 0;
	virtual uint32 GetReceiptTotalDiscount( uint32 nReceiptIndex ) = 0;
	virtual uint32 GetReceiptTax( uint32 nReceiptIndex ) = 0;
	virtual uint32 GetReceiptShipping( uint32 nReceiptIndex ) = 0;
	virtual ECurrencyCode GetReceiptCurrencyCode( uint32 nReceiptIndex ) = 0;
	virtual const char *GetReceiptCountryCode( uint32 nReceiptIndex ) = 0;
	virtual const char *GetReceiptErrorHeadline( uint32 nReceiptIndex ) = 0;
	virtual const char *GetReceiptErrorString( uint32 nReceiptIndex ) = 0;
	virtual const char *GetReceiptErrorLinkText( uint32 nReceiptIndex ) = 0;
	virtual const char *GetReceiptErrorLinkURL( uint32 nReceiptIndex ) = 0;

	virtual AppId_t GetReceiptErrorAppID( uint32 nReceiptIndex ) = 0;

	virtual uint32 GetNumLicenses() = 0;
	virtual uint32 GetNumReceipts() = 0;

	virtual bool PurchaseWithMachineID( PackageId_t nPackageID, const char *pchCustomData ) = 0;

	virtual bool GetReceiptCardInfo( uint32 nReceiptIndex, ECreditCardType* eCreditCardType, char* pchCardLast4Digits, char* pchCardHolderFirstName, char* pchCardHolderLastName, char* pchCardExpYear, char* pchCardExpMonth ) = 0;

	virtual bool GetReceiptBillingAddress( uint32 nReceiptIndex, char* pchFirstName, char* pchLastName, char* pchAddress1, char* pchAddress2, char* pchCity, char* pchPostcode, char* pchState, char* pchCountry, char* pchPhone ) = 0;

	virtual uint32 GetReceiptLineItemCount( uint32 nReceiptIndex ) = 0;
	virtual bool GetReceiptLineItemInfo( uint32 nReceiptIndex, uint32 nLineItemIndex, PackageId_t *nPackageID, uint32 *nBaseCost, uint32 *nDiscount, uint32 *nTax, uint32 *nShipping, ECurrencyCode *eCurrencyCode, AppId_t *punAppId, char *pchDescription, char *pchCouponInfoURL ) = 0;

	virtual void EnableTestLicense( PackageId_t unPackageID ) = 0;
	virtual void DisableTestLicense( PackageId_t unPackageID ) = 0;

	virtual bool ActivateOEMTicket( const char *pchOEMLicenseFile ) = 0;

	virtual uint32 GetPackageName( PackageId_t unPackageID, char *pchName, int32 cubName ) = 0;
	virtual bool GetPackageInfo( PackageId_t unPackageID, uint32 * puNumAppIds, uint32 * puNumDepotIDs, EBillingType * peBillingType, ELicenseType * peLicenseType, EPackageStatus * pePackageStatus, int32 * piCodeClass, int32 * piGameCode, int32 * piTerritoryCode, bool *pbRequiresShipping, bool *pbIsPreorder ) = 0;
	virtual uint32 GetAppsInPackage( PackageId_t unPackageID, AppId_t puIds[], uint32 uMaxIds, bool bExcludeDepots, bool bExcludeApps ) = 0;
	virtual uint32 GetPackageExtendedInfo( PackageId_t unPackageID, uint8 *pubData, int32 cubData, bool bSharedKVSymbols ) = 0;

	virtual SteamAPICall_t RequestFreeLicenseForApp( AppId_t unAppId ) = 0;
};

#endif // ICLIENTBILLING_H
