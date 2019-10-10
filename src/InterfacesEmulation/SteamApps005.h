#pragma once
#include "../public SDK/ISteamApps005.h"
#include "../Bridge.h"

class SteamAppsIn005 : public ISteamApps005
{
public:
	bool BIsSubscribed()
	{
		return true;
	}
	bool BIsLowViolence()
	{
		return Steam_Config::LowViolence;
	}
	bool BIsCybercafe()
	{
		return false;
	}
	bool BIsVACBanned()
	{
		return false;
	}
	const char* GetCurrentGameLanguage()
	{
		return Steam_Config::Language;
	}
	const char* GetAvailableGameLanguages()
	{
		return Steam_Config::Language;
	}

	bool BIsSubscribedApp(AppId_t nAppID)
	{
		return ColdAPI_DLC::IsDLCAvailable(nAppID);
	}

	bool BIsDlcInstalled(AppId_t nAppID)
	{
		return ColdAPI_DLC::IsDLCAvailable(nAppID);
	}

	uint32 GetEarliestPurchaseUnixTime(AppId_t nAppID)
	{
		return (uint32)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 700;
	}

	bool BIsSubscribedFromFreeWeekend()
	{
		return false;
	}
	int GetDLCCount()
	{
		return ColdAPI_DLC::GetDlCCount();
	}

	bool BGetDLCDataByIndex(int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize)
	{
		return ColdAPI_DLC::GetDLCByIndex(iDLC, pAppID, pbAvailable, pchName, cchNameBufferSize);
	}

	void InstallDLC(AppId_t nAppID)
	{
		return;
	}
	void UninstallDLC(AppId_t nAppID)
	{
		return;
	}

	void RequestAppProofOfPurchaseKey(AppId_t nAppID)
	{
		return;
	}

	bool GetCurrentBetaName(char* pchName, int cchNameBufferSize)
	{
		return false;
	}
	bool MarkContentCorrupt(bool bMissingFilesOnly)
	{
		return false;
	}
	uint32 GetInstalledDepots(DepotId_t* pvecDepots, uint32 cMaxDepots)
	{
		return NULL;
	}

	uint32 GetAppInstallDir(AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize)
	{
		if (pchFolder != NULL && pchFolder > NULL && cchFolderBufferSize >= NULL) {
			GetCurrentDirectoryA(cchFolderBufferSize, pchFolder);
			return cchFolderBufferSize;
		}
		return NULL;
	}
	bool BIsAppInstalled(AppId_t appID)
	{
		return true;
	}
};
