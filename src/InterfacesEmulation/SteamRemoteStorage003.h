#pragma once
#include "../public SDK/ISteamRemoteStorage003.h"
#include "../Bridge.h"
#include "../ColdManager.h"

class SteamRemoteStorageIn003 : public ISteamRemoteStorage003
{
public:
	bool FileWrite(const char* pchFile, const void* pvData, int32 cubData)
	{
		if (!Steam_Config::RemoteStorage)
			return true;
		if (cubData < NULL)
			return false;
		if (pvData == NULL)
			return false;

		// Let's use std as more faster.
		std::FILE* File = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(pchFile), "wb");
		if (File)
		{
			std::fwrite(pvData, cubData, 1, File);
			std::fclose(File);
			return true;
		}
		return false;
	}
	int32 FileRead(const char* pchFile, void* pvData, int32 cubDataToRead)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		// Let's use std as more faster.
		std::FILE* File = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(pchFile), "rb");
		if (File)
		{
			std::fseek(File, 0, SEEK_END);
			long FileSize = std::ftell(File);
			std::fseek(File, 0, SEEK_SET);

			// Let's check always if the read size is not bigger than the FileSize. We'll do it with min.
			int32_t Min = min(cubDataToRead, FileSize);
			std::fread(pvData, Min, 1, File);
			std::fclose(File);
			return Min;
		}
		return NULL;
	}

	bool FileForget(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return true;
	}
	bool FileDelete(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		const char* myfile = ColdAPI_Storage::ConnectDirectoryToFile(pchFile);
		if (GetFileAttributesA(myfile) == INVALID_FILE_ATTRIBUTES)
			return false;
		return (DeleteFileA(myfile) == TRUE);
	}
	SteamAPICall_t FileShare(const char* pchFile)
	{
		return NULL;
	}

	bool FileExists(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return (GetFileAttributesA(ColdAPI_Storage::ConnectDirectoryToFile(pchFile)) != INVALID_FILE_ATTRIBUTES);
	}
	bool FilePersisted(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return true;
	}
	int32 GetFileSize(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		const char* myfile = ColdAPI_Storage::ConnectDirectoryToFile(pchFile);
		// Let's use std as more faster.
		std::FILE* File = std::fopen(myfile, "rb");
		if (File)
		{
			std::fseek(File, 0, SEEK_END);
			long FileSize = std::ftell(File);
			std::fseek(File, 0, SEEK_SET);
			std::fclose(File);
			return FileSize;
		}
		return NULL;
	}
	int64 GetFileTimestamp(const char* pchFile)
	{
		return time(NULL) - 3000;
	}

	int32 GetFileCount()
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());
		return FilesMatrix.size(); // Return the vector size
	}
	const char* GetFileNameAndSize(int iFile, int32* pnFileSizeInBytes)
	{
		if (!Steam_Config::RemoteStorage)
			return "";
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());
		if (iFile <= FilesMatrix.size())
		{
			std::string FileName = FilesMatrix.at(iFile);

			// Let's use std as more faster.
			std::FILE* File = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(FileName.c_str()), "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);
				*pnFileSizeInBytes = FileSize;
				return FileName.c_str();
			}
		}
		return "";

	}

	bool GetQuota(int32* pnTotalBytes, int32* puAvailableBytes)
	{
		*pnTotalBytes = NULL;
		*puAvailableBytes = INT_MAX;
		return true;
	}
	bool IsCloudEnabledForAccount()
	{
		return true;
	}
	bool IsCloudEnabledThisApp()
	{
		return true;
	}
	bool SetCloudEnabledThisApp(bool bEnable)
	{
		return true;
	}

	SteamAPICall_t UGCDownload(UGCHandle_t hContent)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;

		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetUGCDirectory());

		if (FilesMatrix.size() >= hContent)
		{
			// Read the UGC File.
			std::string FileName = FilesMatrix.at(hContent);
			std::FILE* File = std::fopen(ColdAPI_Storage::ConnectUGCDirectoryToFile(FileName.c_str()), "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);

				auto Response = new RemoteStorageDownloadUGCResult_t();
				auto RequestID = SteamCallback::RegisterCall(true);
				Response->m_eResult = k_EResultOK;
				Response->m_hFile = hContent;
				Response->m_nAppID = Steam_Config::AppId;
				Response->m_nSizeInBytes = FileSize;
				std::memcpy(Response->m_pchFileName, FileName.c_str(), MAX_PATH);
				Response->m_ulSteamIDOwner = Steam_Config::UserID;
				SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
				return RequestID;
			}
		}
		return NULL;
	}
	bool GetUGCDetails(UGCHandle_t hContent, AppId_t* pnAppID, char** ppchName, int32* pnFileSizeInBytes, CSteamID* pSteamIDOwner)
	{
		if (!Steam_Config::RemoteStorage)
			return false;

		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetUGCDirectory());

		if (FilesMatrix.size() >= hContent)
		{
			// Read the UGC File.
			std::string FileName = FilesMatrix.at(hContent);
			std::FILE* File = std::fopen(ColdAPI_Storage::ConnectUGCDirectoryToFile(FileName.c_str()), "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);
				*pnAppID = Steam_Config::AppId;
				*ppchName = (char*)std::malloc(std::strlen(FileName.c_str()) + 10);
				std::strcpy(*ppchName, FileName.c_str());
				*pnFileSizeInBytes = FileSize;
				*pSteamIDOwner = Steam_Config::UserID;
				return true;
			}
		}
		return false;
	}
	int32 UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;

		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetUGCDirectory());

		if (FilesMatrix.size() >= hContent)
		{
			// Read the UGC File.
			std::string FileName = FilesMatrix.at(hContent);
			std::FILE* File = std::fopen(ColdAPI_Storage::ConnectUGCDirectoryToFile(FileName.c_str()), "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);

				// Let's check always if the read size is not bigger than the FileSize. We'll do it with min.
				int32_t Min = min(cubDataToRead, FileSize);
				std::fread(pvData, Min, 1, File);
				std::fclose(File);
				return Min;
			}
		}
		return NULL;
	}

	int32	GetCachedUGCCount()
	{
		return NULL;
	}
	UGCHandle_t GetCachedUGCHandle(int32 iCachedContent)
	{
		return NULL;
	}
};
