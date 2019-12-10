#pragma once
#include "../public SDK/ISteamRemoteStorage005.h"
#include "../Bridge.h"
#include "../ColdManager.h"

class SteamRemoteStorageIn005 : public ISteamRemoteStorage005
{
public:
	bool	FileWrite(const char* pchFile, const void* pvData, int32 cubData)
	{
		if (!Steam_Config::RemoteStorage)
			return true;
		if (cubData < NULL)
			return false;
		if (pvData <= NULL)
			return false;

		PublicSafe.lock();

		char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(pchFile);

		// Let's use std as more faster.
		std::FILE* File = std::fopen(ConnectedDir, "wb");
		if (File)
		{
			std::fwrite(pvData, cubData, 1, File);
			std::fclose(File);
			ColdAPI_Storage::CloseMem(ConnectedDir);
			PublicSafe.unlock();
			return true;
		}
		ColdAPI_Storage::CloseMem(ConnectedDir);
		PublicSafe.unlock();
		return false;
	}
	int32	FileRead(const char* pchFile, void* pvData, int32 cubDataToRead)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		if (cubDataToRead < NULL)
			return NULL;
		if (pvData <= NULL)
			return NULL;

		PublicSafe.lock();

		char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(pchFile);

		// Let's use std as more faster.
		std::FILE* File = std::fopen(ConnectedDir, "rb");
		if (File)
		{
			std::fseek(File, 0, SEEK_END);
			long FileSize = std::ftell(File);
			std::fseek(File, 0, SEEK_SET);

			// Let's check always if the read size is not bigger than the FileSize. We'll do it with min.
			int32_t Min = min(cubDataToRead, FileSize);
			std::fread(pvData, Min, 1, File);
			std::fclose(File);
			ColdAPI_Storage::CloseMem(ConnectedDir);
			PublicSafe.unlock();
			return Min;
		}
		ColdAPI_Storage::CloseMem(ConnectedDir);
		PublicSafe.unlock();
		return NULL;
	}
	bool	FileForget(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return true;
	}
	bool	FileDelete(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;

		PublicSafe.lock();

		char* myfile = (char*)ColdAPI_Storage::ConnectDirectoryToFile(pchFile);
		if (GetFileAttributesA(myfile) == INVALID_FILE_ATTRIBUTES) {
			ColdAPI_Storage::CloseMem(myfile);
			PublicSafe.unlock();
			return false;
		}
		bool Deleted = DeleteFileA(myfile) == TRUE;
		ColdAPI_Storage::CloseMem(myfile);
		PublicSafe.unlock();
		return Deleted;
	}
	SteamAPICall_t FileShare(const char* pchFile)
	{
		return NULL;
	}
	bool	SetSyncPlatforms(const char* pchFile, ERemoteStoragePlatform eRemoteStoragePlatform)
	{
		return true;
	}

	bool	FileExists(const char* pchFile)
	{
		PublicSafe.lock();

		// Variables 
		bool Exists;
		char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(pchFile);

		if (!Steam_Config::RemoteStorage) {
			ColdAPI_Storage::CloseMem(ConnectedDir);
			PublicSafe.unlock();
			return false;
		}

		Exists = GetFileAttributesA(ColdAPI_Storage::ConnectDirectoryToFile(pchFile)) != INVALID_FILE_ATTRIBUTES;
		ColdAPI_Storage::CloseMem(ConnectedDir);
		PublicSafe.unlock();
		return Exists;
	}
	bool	FilePersisted(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return true;
	}
	int32	GetFileSize(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;

		PublicSafe.lock();

		char* myfile = (char*)ColdAPI_Storage::ConnectDirectoryToFile(pchFile);
		// Let's use std as more faster.
		std::FILE* File = std::fopen(myfile, "rb");
		if (File)
		{
			std::fseek(File, 0, SEEK_END);
			long FileSize = std::ftell(File);
			std::fseek(File, 0, SEEK_SET);
			std::fclose(File);
			ColdAPI_Storage::CloseMem(myfile);
			PublicSafe.unlock();
			return FileSize;
		}
		ColdAPI_Storage::CloseMem(myfile);
		PublicSafe.unlock();
		return NULL;
	}
	int64	GetFileTimestamp(const char* pchFile)
	{
		return time(NULL) - 3000;
	}
	ERemoteStoragePlatform GetSyncPlatforms(const char* pchFile)
	{
		return k_ERemoteStoragePlatformAll;
	}

	int32 GetFileCount()
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());
		PublicSafe.unlock();
		return FilesMatrix.size(); // Return the vector size
	}
	const char* GetFileNameAndSize(int iFile, int32* pnFileSizeInBytes)
	{
		if (!Steam_Config::RemoteStorage)
			return "";
		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());

		if (iFile <= FilesMatrix.size())
		{
			std::string FileName = FilesMatrix.at(iFile);

			char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(FileName.c_str());

			// Let's use std as more faster.
			std::FILE* File = std::fopen(ConnectedDir, "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);
				if (pnFileSizeInBytes != NULL && pnFileSizeInBytes > NULL)
					*pnFileSizeInBytes = FileSize;
				ColdAPI_Storage::CloseMem(ConnectedDir);
				PublicSafe.unlock();
				return FileName.c_str();
			}
			ColdAPI_Storage::CloseMem(ConnectedDir);
		}
		PublicSafe.unlock();
		return "";
	}

	bool GetQuota(int32* pnTotalBytes, int32* puAvailableBytes)
	{
		if (pnTotalBytes <= NULL)
			return false;
		if (puAvailableBytes <= NULL)
			return false;
		*pnTotalBytes = NULL;
		*puAvailableBytes = INT_MAX;
		return true;
	}
	bool IsCloudEnabledForAccount()
	{
		return true;
	}
	bool IsCloudEnabledForApp()
	{
		return true;
	}
	void SetCloudEnabledForApp(bool bEnabled)
	{
		return;
	}

	SteamAPICall_t UGCDownload(UGCHandle_t hContent)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;

		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetUGCDirectory());

		if (FilesMatrix.size() >= hContent)
		{
			// Read the UGC File.
			std::string FileName = FilesMatrix.at(hContent);

			char* UGCConnectedDir = (char*)ColdAPI_Storage::ConnectUGCDirectoryToFile(FileName.c_str());

			std::FILE* File = std::fopen(UGCConnectedDir, "rb");
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
				ColdAPI_Storage::CloseMem(UGCConnectedDir);
				PublicSafe.unlock();
				return RequestID;
			}
			ColdAPI_Storage::CloseMem(UGCConnectedDir);
		}
		PublicSafe.unlock();
		return NULL;
	}
	bool	GetUGCDetails(UGCHandle_t hContent, AppId_t* pnAppID, char** ppchName, int32* pnFileSizeInBytes, CSteamID* pSteamIDOwner)
	{
		if (!Steam_Config::RemoteStorage)
			return false;

		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetUGCDirectory());

		if (FilesMatrix.size() >= hContent)
		{
			// Read the UGC File.
			std::string FileName = FilesMatrix.at(hContent);

			char* UGCConnectedDir = (char*)ColdAPI_Storage::ConnectUGCDirectoryToFile(FileName.c_str());

			std::FILE* File = std::fopen(UGCConnectedDir, "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);
				if (pnAppID != NULL && pnAppID > NULL)
					*pnAppID = Steam_Config::AppId;
				if (ppchName != NULL && ppchName > NULL) {
					*ppchName = (char*)std::malloc(std::strlen(FileName.c_str()) + 10);
					std::strcpy(*ppchName, FileName.c_str());
				}
				if (pnFileSizeInBytes != NULL && pnFileSizeInBytes > NULL)
					*pnFileSizeInBytes = FileSize;
				if (pSteamIDOwner != NULL && pSteamIDOwner > NULL)
					*pSteamIDOwner = Steam_Config::UserID;
				ColdAPI_Storage::CloseMem(UGCConnectedDir);
				PublicSafe.unlock();
				return true;
			}
			ColdAPI_Storage::CloseMem(UGCConnectedDir);
		}
		PublicSafe.unlock();
		return false;
	}
	int32	UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		if (cubDataToRead < NULL)
			return NULL;
		if (pvData <= NULL)
			return NULL;

		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetUGCDirectory());

		if (FilesMatrix.size() >= hContent)
		{
			// Read the UGC File.
			std::string FileName = FilesMatrix.at(hContent);

			char* UGCConnectedDir = (char*)ColdAPI_Storage::ConnectUGCDirectoryToFile(FileName.c_str());

			std::FILE* File = std::fopen(UGCConnectedDir, "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);

				// Let's check always if the read size is not bigger than the FileSize. We'll do it with min.
				int32_t Min = min(cubDataToRead, FileSize);
				std::fread(pvData, Min, 1, File);
				std::fclose(File);
				ColdAPI_Storage::CloseMem(UGCConnectedDir);
				PublicSafe.unlock();
				return Min;
			}
			ColdAPI_Storage::CloseMem(UGCConnectedDir);
		}
		PublicSafe.unlock();
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

	SteamAPICall_t	PublishFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags)
	{
		return NULL;
	}
	SteamAPICall_t	PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, SteamParamStringArray_t* pTags)
	{
		return NULL;
	}
	SteamAPICall_t	UpdatePublishedFile(RemoteStorageUpdatePublishedFileRequest_t updatePublishedFileRequest)
	{
		return NULL;
	}
	SteamAPICall_t	GetPublishedFileDetails(PublishedFileId_t unPublishedFileId)
	{
		return NULL;
	}
	SteamAPICall_t	DeletePublishedFile(PublishedFileId_t unPublishedFileId)
	{
		return NULL;
	}
	SteamAPICall_t	EnumerateUserPublishedFiles(uint32 unStartIndex)
	{
		return NULL;
	}
	SteamAPICall_t	SubscribePublishedFile(PublishedFileId_t unPublishedFileId)
	{
		return NULL;
	}
	SteamAPICall_t	EnumerateUserSubscribedFiles(uint32 unStartIndex)
	{
		return NULL;
	}
	SteamAPICall_t	UnsubscribePublishedFile(PublishedFileId_t unPublishedFileId)
	{
		return NULL;
	}
};

