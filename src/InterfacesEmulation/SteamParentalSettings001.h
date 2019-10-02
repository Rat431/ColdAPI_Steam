#pragma once
#include "../public SDK/isteamparentalsettings.h"


class SteamParentalSettingsIn001 : public ISteamParentalSettings001
{
public:
	bool BIsParentalLockEnabled()
	{
		return false;
	}
	bool BIsParentalLockLocked()
	{
		return false;
	}

	bool BIsAppBlocked(AppId_t nAppID)
	{
		return false;
	}
	bool BIsAppInBlockList(AppId_t nAppID)
	{
		return false;
	}

	bool BIsFeatureBlocked(EParentalFeature eFeature)
	{
		return false;
	}
	bool BIsFeatureInBlockList(EParentalFeature eFeature)
	{
		return false;
	}
};