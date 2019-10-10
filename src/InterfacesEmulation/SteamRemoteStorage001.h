#pragma once
#include "../public SDK/ISteamRemoteStorage001.h"
#include "../Bridge.h"
#include "../ColdManager.h"

class SteamRemoteStorageIn001 : public ISteamRemoteStorage001
{
public:
	bool FileWrite(const char* filename, void  const* data, int sizebytestowrite)
	{
		if (!Steam_Config::RemoteStorage)
			return true;
		if (sizebytestowrite < NULL)
			return false;
		if(data <= NULL)
			return false;
		
		// Let's use std as more faster.
		std::FILE* File = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(filename), "wb");
		if (File)
		{
			std::fwrite(data, sizebytestowrite, 1, File);
			std::fclose(File);
			return true;
		}
		return false;
	}

	uint32 GetFileSize(const char* filename)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		const char* myfile = ColdAPI_Storage::ConnectDirectoryToFile(filename);
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

	bool FileRead(const char* filename, void* buffer, int size)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		if(buffer <= NULL)
			return false;
		if(size < NULL)
			return false;

		// Let's use std as more faster.
		std::FILE* File = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(filename), "rb");
		if (File)
		{
			std::fseek(File, 0, SEEK_END);
			long FileSize = std::ftell(File);
			std::fseek(File, 0, SEEK_SET);

			// Let's check always if the read size is not bigger than the FileSize. We'll do it with min.
			std::fread(buffer, min(size, FileSize), 1, File);
			std::fclose(File);
			return true;
		}
		return false;
	}

	bool FileExists(const char* filename)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		return (GetFileAttributesA(ColdAPI_Storage::ConnectDirectoryToFile(filename)) != INVALID_FILE_ATTRIBUTES);
	}
	OBSOLETE_FUNCTION bool FileDelete(const char* filename)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		const char* myfile = ColdAPI_Storage::ConnectDirectoryToFile(filename);
		if (GetFileAttributesA(myfile) == INVALID_FILE_ATTRIBUTES)
			return false;
		return (DeleteFileA(myfile) == TRUE);
	}

	uint32 GetFileCount()
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());
		return FilesMatrix.size(); // Return the vector size
	}

	const char* GetFileNameAndSize(int index, int* size)
	{
		if (!Steam_Config::RemoteStorage)
			return "";
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());

		if (index <= FilesMatrix.size())
		{
			std::string FileName = FilesMatrix.at(index);

			// Let's use std as more faster.
			std::FILE* File = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(FileName.c_str()), "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);
				if(size != NULL && size > NULL)
					*size = FileSize;
				return FileName.c_str();
			}
		}
		return "";
	}

	bool GetQuota(int* current, int* maximum)
	{
		if (current == NULL || current < NULL)
			return false;
		if (maximum == NULL || maximum < NULL)
			return false;
		*current = NULL;
		*maximum = INT_MAX;
		return true;
	}
};