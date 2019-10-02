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
	bool FileExists(const char* pchFile)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return (GetFileAttributesA(ColdAPI_Storage::ConnectDirectoryToFile(pchFile)) != INVALID_FILE_ATTRIBUTES);
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
};
