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

		PublicSafe.lock();

		char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(filename);
		
		// Let's use std as more faster.
		std::FILE* File = std::fopen(ConnectedDir, "wb");
		if (File)
		{
			std::fwrite(data, sizebytestowrite, 1, File);
			std::fclose(File);
			ColdAPI_Storage::CloseMem(ConnectedDir);
			PublicSafe.unlock();
			return true;
		}
		ColdAPI_Storage::CloseMem(ConnectedDir);
		PublicSafe.unlock();
		return false;
	}

	uint32 GetFileSize(const char* filename)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;

		PublicSafe.lock();

		char* myfile = (char*)ColdAPI_Storage::ConnectDirectoryToFile(filename);
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

	bool FileRead(const char* filename, void* buffer, int size)
	{
		if (!Steam_Config::RemoteStorage)
			return false;
		if(buffer <= NULL)
			return false;
		if(size < NULL)
			return false;

		PublicSafe.lock();

		char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(filename);

		// Let's use std as more faster.
		std::FILE* File = std::fopen(ConnectedDir, "rb");
		if (File)
		{
			std::fseek(File, 0, SEEK_END);
			long FileSize = std::ftell(File);
			std::fseek(File, 0, SEEK_SET);

			// Let's check always if the read size is not bigger than the FileSize. We'll do it with min.
			std::fread(buffer, min(size, FileSize), 1, File);
			std::fclose(File);
			ColdAPI_Storage::CloseMem(ConnectedDir);
			PublicSafe.unlock();
			return true;
		}
		ColdAPI_Storage::CloseMem(ConnectedDir);
		PublicSafe.unlock();
		return false;
	}

	bool FileExists(const char* filename)
	{
		PublicSafe.lock();

		// Variables 
		bool Exists;
		char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(filename);

		if (!Steam_Config::RemoteStorage) {
			ColdAPI_Storage::CloseMem(ConnectedDir);
			PublicSafe.unlock();
			return false;
		}
			
		Exists = GetFileAttributesA(ColdAPI_Storage::ConnectDirectoryToFile(filename)) != INVALID_FILE_ATTRIBUTES;
		ColdAPI_Storage::CloseMem(ConnectedDir);
		PublicSafe.unlock();
		return Exists;
	}
	OBSOLETE_FUNCTION bool FileDelete(const char* filename)
	{
		if (!Steam_Config::RemoteStorage)
			return false;

		PublicSafe.lock();
		char* myfile = (char*)ColdAPI_Storage::ConnectDirectoryToFile(filename);
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

	uint32 GetFileCount()
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;
		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());
		PublicSafe.unlock();
		return FilesMatrix.size(); // Return the vector size
	}

	const char* GetFileNameAndSize(int index, int* size)
	{
		if (!Steam_Config::RemoteStorage)
			return "";
		PublicSafe.lock();
		FilesMatrix.clear();
		ColdAPI_Storage::FillFileStructure(ColdAPI_Storage::GetStorageDirectory());

		if (index <= FilesMatrix.size())
		{
			std::string FileName = FilesMatrix.at(index);

			char* ConnectedDir = (char*)ColdAPI_Storage::ConnectDirectoryToFile(FileName.c_str());

			// Let's use std as more faster.
			std::FILE* File = std::fopen(ConnectedDir, "rb");
			if (File)
			{
				std::fseek(File, 0, SEEK_END);
				long FileSize = std::ftell(File);
				std::fseek(File, 0, SEEK_SET);
				std::fclose(File);
				if(size != NULL && size > NULL)
					*size = FileSize;
				ColdAPI_Storage::CloseMem(ConnectedDir);
				PublicSafe.unlock();
				return FileName.c_str();
			}
			ColdAPI_Storage::CloseMem(ConnectedDir);
		}
		PublicSafe.unlock();
		return "";
	}

	bool GetQuota(int* current, int* maximum)
	{
		if (current <= NULL)
			return false;
		if (maximum <= NULL)
			return false;
		*current = NULL;
		*maximum = INT_MAX;
		return true;
	}
};