#pragma once
#include "../public SDK/ISteamRemoteStorage002.h"
#include "../Bridge.h"
#include "../ColdManager.h"

class SteamRemoteStorageIn002 : public ISteamRemoteStorage002
{
public:
	bool FileWrite(const char* pchFile, const void* pvData, int32 cubData)
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
	int32 GetFileSize(const char* pchFile)
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
	int32 FileRead(const char* pchFile, void* pvData, int32 cubDataToRead)
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
	bool FileExists(const char* pchFile)
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
};
