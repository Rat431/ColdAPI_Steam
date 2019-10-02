#pragma once
#include "../public SDK/ISteamBilling001.h"

class SteamBillingIn001 : public ISteamBilling001
{
public:
	bool SetBillingAddress(const char* pchName, const char* pchAddress1, const char* pchAddress2, const char* pchCity, const char* pchPostcode, const char* pchState, const char* pchCountry, const char* pchPhone)
	{
		return false;
	}
	bool GetBillingAddress(char* pchName, char* pchAddress1, char* pchAddress2, char* pchCity, char* pchPostcode, char* pchState, char* pchCountry, char* pchPhone)
	{
		return false;
	}
	bool SetShippingAddress(const char* pchName, const char* pchAddress1, const char* pchAddress2, const char* pchCity, const char* pchPostcode, const char* pchState, const char* pchCountry, const char* pchPhone)
	{
		return false;
	}
	bool GetShippingAddress(char* pchName, char* pchAddress1, char* pchAddress2, char* pchCity, char* pchPostcode, char* pchState, char* pchCountry, char* pchPhone)
	{
		return false;
	}
	bool GetFinalPrice(int32 nPackageID)
	{
		return false;
	}

	bool SetCardInfo(ECreditCardType eCreditCardType, const char* pchCardNumber, const char* pchCardHolderName, const char* pchCardExpYear, const char* pchCardExpMonth, const char* pchCardCVV2)
	{
		return false;
	}
	bool GetCardInfo(ECreditCardType* eCreditCardType, char* pchCardNumber, char* pchCardHolderName, char* pchCardExpYear, char* pchCardExpMonth, char* pchCardCVV2)
	{
		return false;
	}

	bool Purchase(int32 nPackageID, int32 nExpectedCostCents, uint64 gidCardID, bool bStoreCardInfo)
	{
		return false;
	}
};