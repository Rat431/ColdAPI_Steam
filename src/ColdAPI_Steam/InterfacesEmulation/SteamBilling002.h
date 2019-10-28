#pragma once
#include "../public SDK/ISteamBilling002.h"

class SteamBillingIn002 : public ISteamBilling002
{
public:
	bool InitCreditCardPurchase(PackageId_t nPackageID, uint32 nCardIndex, bool bStoreCardInfo)
	{
		return false;
	}
	bool InitPayPalPurchase(PackageId_t nPackageID)
	{
		return false;
	}

	bool GetActivationCodeInfo(const char* pchActivationCode)
	{
		return false;
	}
	bool PurchaseWithActivationCode(const char* pchActivationCode)
	{
		return false;
	}

	bool GetFinalPrice()
	{
		return false;
	}

	bool CancelPurchase()
	{
		return false;
	}
	bool CompletePurchase()
	{
		return false;
	}

	bool UpdateCardInfo(uint32 nCardIndex)
	{
		return false;
	}

	bool DeleteCard(uint32)
	{
		return false;
	}

	bool GetCardList()
	{
		return false;
	}

	bool Obsolete_GetLicenses()
	{
		return false;
	}

	bool CancelLicense(PackageId_t nPackageID, int32 nCancelReason)
	{
		return false;
	}

	bool GetPurchaseReceipts(bool bUnacknowledgedOnly)
	{
		return false;
	}

	bool SetBillingAddress(uint32 nCardIndex, const char* pchFirstName, const char* pchLastName, const char* pchAddress1, const char* pchAddress2, const char* pchCity, const char* pchPostcode, const char* pchState, const char* pchCountry, const char* pchPhone)
	{
		return false;
	}

	bool GetBillingAddress(uint32 nCardIndex, char* pchFirstName, char* pchLastName, char* pchAddress1, char* pchAddress2, char* pchCity, char* pchPostcode, char* pchState, char* pchCountry, char* pchPhone)
	{
		return false;
	}

	bool SetShippingAddress(const char* pchFirstName, const char* pchLastName, const char* pchAddress1, const char* pchAddress2, const char* pchCity, const char* pchPostcode, const char* pchState, const char* pchCountry, const char* pchPhone)
	{
		return false;
	}
	bool GetShippingAddress(char* pchFirstName, char* pchLastName, char* pchAddress1, char* pchAddress2, char* pchCity, char* pchPostcode, char* pchState, char* pchCountry, char* pchPhone)
	{
		return false;
	}

	bool SetCardInfo(uint32 nCardIndex, ECreditCardType eCreditCardType, const char* pchCardNumber, const char* pchCardHolderFirstName, const char* pchCardHolderLastName, const char* pchCardExpYear, const char* pchCardExpMonth, const char* pchCardCVV2)
	{
		return false;
	}
	bool GetCardInfo(uint32 nCardIndex, ECreditCardType* eCreditCardType, char* pchCardNumber, char* pchCardHolderFirstName, char* pchCardHolderLastName, char* pchCardExpYear, char* pchCardExpMonth, char* pchCardCVV2)
	{
		return false;
	}

	PackageId_t GetLicensePackageID(uint32 nLicenseIndex)
	{
		return NULL;
	}
	RTime32 GetLicenseTimeCreated(uint32 nLicenseIndex)
	{
		return k_EPaymentMethodNone;
	}
	RTime32 GetLicenseTimeNextProcess(uint32 nLicenseIndex)
	{
		return k_EPaymentMethodNone;
	}
	int32 GetLicenseMinuteLimit(uint32 nLicenseIndex)
	{
		return NULL;
	}
	int32 GetLicenseMinutesUsed(uint32 nLicenseIndex)
	{
		return NULL;
	}
	EPaymentMethod GetLicensePaymentMethod(uint32 nLicenseIndex)
	{
		return k_EPaymentMethodNone;
	}
	ELicenseFlags GetLicenseFlags(uint32 nLicenseIndex)
	{
		return k_ELicenseFlagNone;
	}
	const char* GetLicensePurchaseCountryCode(uint32 nLicenseIndex)
	{
		return "";
	}

	PackageId_t GetReceiptPackageID(uint32 nReceiptIndex)
	{
		return NULL;
	}
	EPurchaseStatus GetReceiptStatus(uint32 nReceiptIndex)
	{
		return k_EPurchasePending;
	}
	EPurchaseResultDetail GetReceiptResultDetail(uint32 nReceiptIndex)
	{
		return k_EPurchaseResultNoDetail;
	}
	RTime32 GetReceiptTransTime(uint32 nReceiptIndex)
	{
		return NULL;
	}
	uint64 GetReceiptTransID(uint32 nReceiptIndex)
	{
		return NULL;
	}
	EPaymentMethod GetReceiptPaymentMethod(uint32 nReceiptIndex)
	{
		return k_EPaymentMethodNone;
	}
	uint32 GetReceiptBaseCost(uint32 nReceiptIndex)
	{
		return NULL;
	}
	uint32 GetReceiptTotalDiscount(uint32 nReceiptIndex)
	{
		return NULL;
	}
	uint32 GetReceiptTax(uint32 nReceiptIndex)
	{
		return NULL;
	}
	uint32 GetReceiptShipping(uint32 nReceiptIndex)
	{
		return NULL;
	}
	const char* GetReceiptCountryCode(uint32 nReceiptIndex)
	{
		return "";
	}

	uint32 GetNumLicenses()
	{
		return NULL;
	}
	uint32 GetNumReceipts()
	{
		return NULL;
	}

	bool PurchaseWithMachineID(PackageId_t nPackageID, const char* pchCustomData)
	{
		return false;
	}

	bool InitClickAndBuyPurchase(PackageId_t nPackageID, int64 nAccountNum, const char* pchState, const char* pchCountryCode)
	{
		return false;
	}

	bool GetPreviousClickAndBuyAccount(int64* pnAccountNum, char* pchState, char* pchCountryCode)
	{
		return false;
	}
};