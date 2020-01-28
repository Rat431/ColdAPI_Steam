#include "ColdManager.h"
#include "InterfacesEmulation/PublicConnector.h"

namespace ColdDLC_Config
{
	std::vector<std::string> DLCsNames;
	std::vector<uint32_t> DLCsAPPID;
	int DLCsCount = 0;
}
HMODULE OverLayModule = 0;
std::vector<std::string> FilesMatrix;
std::vector<std::string> Dirs;
std::mutex PublicSafe;

std::vector<InterfaceData> PublicInterfaces;
std::vector<InterfaceInfo> PublicInterfacesInfo;

std::vector<std::string> IgnoredWInterfacesS;
std::multimap<int, int> IgnoredWInterfacesT;

typedef HMODULE(WINAPI* _LoadLibraryA)(LPCSTR);
typedef HMODULE(WINAPI* _LoadLibraryW)(LPCWSTR);
typedef HMODULE(WINAPI* _LoadLibraryExA)(LPCSTR, HANDLE, DWORD);
typedef HMODULE(WINAPI* _LoadLibraryExW)(LPCWSTR, HANDLE, DWORD);

namespace Hooks_Infos
{
	Hook_Info InfoLoadLibraryA;
	int32_t HookIDLoadLibraryA;
	_LoadLibraryA LibA;

	Hook_Info InfoLoadLibraryW;
	int32_t HookIDLoadLibraryW;
	_LoadLibraryW LibW;

	Hook_Info InfoLoadLibraryExA;
	int32_t HookIDLoadLibraryExA;
	_LoadLibraryExA LibExA;

	Hook_Info InfoLoadLibraryExW;
	int32_t HookIDLoadLibraryExW;
	_LoadLibraryExW LibExW;
}

namespace Steam_Config // Steam configuration
{
	// User Attempt
	char Username[40] = { "ColdAPI" };
	uint32_t AppId = 0;
	uint32_t AppBuildId = 0;
	uint64_t UserID = 0x03100004771F810C;

	// Directories and language attempt
	char SaveDirectory[0x400] = { 0 };
	char UGCDirectotry[0x400] = { 0 };
	char Language[40] = { "english" };


	// Custom variables attempt
	bool OnlineMod = true;
	bool UnlockAllDLCS = true;
	bool LowViolence = false;
	bool RemoteStorage = true;
	bool StubBypass = false;
	bool InterfaceNFound = false;

	bool ClientEmulation = false;
	bool HookForInjection = false;
}
namespace ColdHookEmu
{
#ifdef _WIN64
	CHAR ClientDir[MAX_PATH] = { "myclienthooked64.dll" };
	WCHAR WClientDir[MAX_PATH] = { L"myclienthooked64.dll" };
#else
	CHAR ClientDir[MAX_PATH] = { "myclienthooked.dll" };
	WCHAR WClientDir[MAX_PATH] = { L"myclienthooked.dll" };
#endif

	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryA(
		LPCSTR lpLibFileName
	)
	{
		if (lpLibFileName > NULL && std::strcmp(lpLibFileName, ClientDir) == 0)
			return SteamApimod;
		return Hooks_Infos::LibA(lpLibFileName);
	}
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryW(
		LPCWSTR lpLibFileName
	)
	{
		if (lpLibFileName > NULL && std::wcscmp(lpLibFileName, WClientDir) == 0)
			return SteamApimod;
		return Hooks_Infos::LibW(lpLibFileName);
	}
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryExA(
		LPCSTR lpLibFileName,
		HANDLE hFile,
		DWORD  dwFlags
	)
	{
		if (lpLibFileName > NULL && std::strcmp(lpLibFileName, ClientDir) == 0)
			return SteamApimod;
		return Hooks_Infos::LibExA(lpLibFileName, hFile, dwFlags);
	}
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryExW(
		LPCWSTR lpLibFileName,
		HANDLE  hFile,
		DWORD   dwFlags
	)
	{
		if (lpLibFileName > NULL && std::wcscmp(lpLibFileName, WClientDir) == 0)
			return SteamApimod;
		return Hooks_Infos::LibExW(lpLibFileName, hFile, dwFlags);
	}
}
namespace ColdClientHookManager
{
	void ColdClientHookInit()
	{
		if (ColdHook_Service::ServiceGlobalInit(NULL))
		{
			Hooks_Infos::HookIDLoadLibraryA = ColdHook_Service::InitFunctionHookByName(&Hooks_Infos::InfoLoadLibraryA, true, true, "kernel32.dll", "LoadLibraryA", ColdHookEmu::CLoadLibraryA, NULL);
			Hooks_Infos::HookIDLoadLibraryW = ColdHook_Service::InitFunctionHookByName(&Hooks_Infos::InfoLoadLibraryW, true, true, "kernel32.dll", "LoadLibraryW", ColdHookEmu::CLoadLibraryW, NULL);
			Hooks_Infos::HookIDLoadLibraryExA = ColdHook_Service::InitFunctionHookByName(&Hooks_Infos::InfoLoadLibraryExA, true, true, "kernel32.dll", "LoadLibraryExA", ColdHookEmu::CLoadLibraryExA, NULL);
			Hooks_Infos::HookIDLoadLibraryExW = ColdHook_Service::InitFunctionHookByName(&Hooks_Infos::InfoLoadLibraryExW, true, true, "kernel32.dll", "LoadLibraryExW", ColdHookEmu::CLoadLibraryExW, NULL);
			if (Hooks_Infos::HookIDLoadLibraryA != NULL && Hooks_Infos::HookIDLoadLibraryW != NULL && Hooks_Infos::HookIDLoadLibraryExA != NULL && Hooks_Infos::HookIDLoadLibraryExW != NULL)
			{
				bool Reg1 = ColdHook_Service::ServiceRegisterHookInformation(&Hooks_Infos::InfoLoadLibraryA, Hooks_Infos::HookIDLoadLibraryA, NULL);
				if (!Reg1) {
					MessageBoxA(NULL, "Falied to inject the steamclient(64) module with HookInjectionMode. Error: Couldn't get the requested function pointer.",
						"Error", MB_ICONERROR);
					ExitProcess(NULL);
				}
				bool Reg2 = ColdHook_Service::ServiceRegisterHookInformation(&Hooks_Infos::InfoLoadLibraryW, Hooks_Infos::HookIDLoadLibraryW, NULL);
				if (!Reg2) {
					MessageBoxA(NULL, "Falied to inject the steamclient(64) module with HookInjectionMode. Error: Couldn't get the requested function pointer.",
						"Error", MB_ICONERROR);
					ExitProcess(NULL);
				}
				bool Reg3 = ColdHook_Service::ServiceRegisterHookInformation(&Hooks_Infos::InfoLoadLibraryExA, Hooks_Infos::HookIDLoadLibraryExA, NULL);
				if (!Reg3) {
					MessageBoxA(NULL, "Falied to inject the steamclient(64) module with HookInjectionMode. Error: Couldn't get the requested function pointer.",
						"Error", MB_ICONERROR);
					ExitProcess(NULL);
				}
				bool Reg4 = ColdHook_Service::ServiceRegisterHookInformation(&Hooks_Infos::InfoLoadLibraryExW, Hooks_Infos::HookIDLoadLibraryExW, NULL);
				if (!Reg4) {
					MessageBoxA(NULL, "Falied to inject the steamclient(64) module with HookInjectionMode. Error: Couldn't get the requested function pointer.",
						"Error", MB_ICONERROR);
					ExitProcess(NULL);
				}
				Hooks_Infos::LibA = (_LoadLibraryA)Hooks_Infos::InfoLoadLibraryA.OriginalF;
				Hooks_Infos::LibW = (_LoadLibraryW)Hooks_Infos::InfoLoadLibraryW.OriginalF;
				Hooks_Infos::LibExA = (_LoadLibraryExA)Hooks_Infos::InfoLoadLibraryExA.OriginalF;
				Hooks_Infos::LibExW = (_LoadLibraryExW)Hooks_Infos::InfoLoadLibraryExW.OriginalF;
			}
			else {
				MessageBoxA(NULL, "Falied to inject the steamclient(64) module with HookInjectionMode. Error: Couldn't get the requested function pointer.",
					"Error", MB_ICONERROR);
				ExitProcess(NULL);
			}
		}
	}
}
namespace ColdAPI_DLC
{
	bool GetDLCByIndex(int iDLC, unsigned int* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize)
	{
		if (iDLC < ColdDLC_Config::DLCsCount && !Steam_Config::UnlockAllDLCS && ColdDLC_Config::DLCsCount > 0)
		{
			if (pAppID != NULL && pAppID > NULL)
				* pAppID = ColdDLC_Config::DLCsAPPID.at(iDLC);
			if (pbAvailable != NULL && pbAvailable > NULL)
				* pbAvailable = true;
			std::string Name = ColdDLC_Config::DLCsNames.at(iDLC);
			if (pchName != NULL && pchName > NULL && cchNameBufferSize >= NULL)
				std::memcpy(pchName, Name.c_str(), cchNameBufferSize);
			return true;
		}
		return false;
	}
	bool IsDLCAvailable(uint32_t Appid)
	{
		// Check if the requested AppId is not 0 or the same as the game setted one.

		if (Appid != 0 && Appid != Steam_Config::AppId)
		{
			if (!Steam_Config::UnlockAllDLCS)
			{
				uint32_t CurrentAppID = 0;

				if (ColdDLC_Config::DLCsCount > 0)
				{
					// Search if the asked DLC was requested by the user.
					auto IterStart = ColdDLC_Config::DLCsAPPID.begin();

					while (IterStart != ColdDLC_Config::DLCsAPPID.end())
					{
						CurrentAppID = *IterStart;
						if (CurrentAppID == Appid)
							return true;
						++IterStart;
					}
				}
				return false;
			}
		}
		return true;
	}
	int GetDlCCount()
	{
		return ColdDLC_Config::DLCsCount;
	}
}
namespace ColdAPI_Storage
{
	char* ConnectDirectoryToFile(const char* FileName)
	{
		// Variables 
		char* tempbuffer = nullptr;
		char* FileAndDir = nullptr;
		int ConstantDirLength = std::strlen(Steam_Config::SaveDirectory);
		int ProvidedStringLength = std::strlen(FileName);
		int CalcSize = ConstantDirLength + ProvidedStringLength;

		FileAndDir = (char*)VirtualAlloc(nullptr, CalcSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (FileAndDir)
		{
			tempbuffer = (char*)VirtualAlloc(nullptr, CalcSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			if (tempbuffer)
			{
				std::strcpy(FileAndDir, Steam_Config::SaveDirectory);
				std::strcpy(&FileAndDir[ConstantDirLength], FileName);

				for (int i = 0; i < ProvidedStringLength; i++, ConstantDirLength++)
				{
					if (FileAndDir[ConstantDirLength] == '\\' || FileAndDir[ConstantDirLength] == '/')
					{
						std::memcpy(tempbuffer, FileAndDir, ConstantDirLength);
						DWORD ftyp = GetFileAttributesA(tempbuffer);
						if (ftyp == INVALID_FILE_ATTRIBUTES) {
							CreateDirectoryA(tempbuffer, NULL);
						}
					}
				}
				VirtualFree(tempbuffer, NULL, MEM_RELEASE);
				return FileAndDir;
			}
			VirtualFree(FileAndDir, NULL, MEM_RELEASE);
		}
		return nullptr;
	}
	char* ConnectUGCDirectoryToFile(const char* FileName)
	{
		// Variables 
		char* tempbuffer = nullptr;
		char* FileAndDir = nullptr;
		int ConstantDirLength = std::strlen(Steam_Config::UGCDirectotry);
		int ProvidedStringLength = std::strlen(FileName);
		int CalcSize = ConstantDirLength + ProvidedStringLength;

		FileAndDir = (char*)VirtualAlloc(nullptr, CalcSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (FileAndDir)
		{
			tempbuffer = (char*)VirtualAlloc(nullptr, CalcSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			if (tempbuffer)
			{
				std::strcpy(FileAndDir, Steam_Config::UGCDirectotry);
				std::strcpy(&FileAndDir[ConstantDirLength], FileName);

				for (int i = 0; i < ProvidedStringLength; i++, ConstantDirLength++)
				{
					if (FileAndDir[ConstantDirLength] == '\\' || FileAndDir[ConstantDirLength] == '/')
					{
						std::memcpy(tempbuffer, FileAndDir, ConstantDirLength);
						DWORD ftyp = GetFileAttributesA(tempbuffer);
						if (ftyp == INVALID_FILE_ATTRIBUTES) {
							CreateDirectoryA(tempbuffer, NULL);
						}
					}
				}
				VirtualFree(tempbuffer, NULL, MEM_RELEASE);
				return FileAndDir;
			}
			VirtualFree(FileAndDir, NULL, MEM_RELEASE);
		}
		return nullptr;
	}
	static bool Ready = false;
	const char* GetStorageDirectory()
	{
		if (!Ready)
		{
			if (std::strcmp(Steam_Config::SaveDirectory, "Auto") == 0)
			{
				std::memset(Steam_Config::SaveDirectory, 0, 0x400);
				std::strcpy(Steam_Config::SaveDirectory, Steamapipath);
				std::strcat(Steam_Config::SaveDirectory, "ColdStorage\\");
				std::strcat(Steam_Config::SaveDirectory, Steam_Config::Username);
				std::strcat(Steam_Config::SaveDirectory, "\\");
				std::strcat(Steam_Config::SaveDirectory, ColdAPI_General::FormatTheString("%lu", EMPTY, Steam_Config::AppId));
				std::strcat(Steam_Config::SaveDirectory, "\\");
				std::strcat(Steam_Config::SaveDirectory, "LocalSaves\\");
			}
			else
			{ 
				int c = 0;

				// Search if the last byte was a "/".
				for (;;)
				{
					if (Steam_Config::SaveDirectory[c] == NULL)
					{
						if (Steam_Config::SaveDirectory[c - 1] != '\\' || Steam_Config::SaveDirectory[c - 1] != '/')
							std::strcpy(&Steam_Config::SaveDirectory[c], "\\");
						break;
					}
					c++;
				}
				std::strcat(Steam_Config::SaveDirectory, "ColdStorage\\");
				std::strcat(Steam_Config::SaveDirectory, Steam_Config::Username);
				std::strcat(Steam_Config::SaveDirectory, "\\");
				std::strcat(Steam_Config::SaveDirectory, ColdAPI_General::FormatTheString("%lu", EMPTY, Steam_Config::AppId));
				std::strcat(Steam_Config::SaveDirectory, "\\");
				std::strcat(Steam_Config::SaveDirectory, "LocalSaves\\");
			}
			Ready = true;
		}
		return Steam_Config::SaveDirectory;
	}
	void FillFileStructure(const char* Directory)
	{
		// List files
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		char path[MAX_PATH + 0x200] = { 0 };
		char tmp[MAX_PATH + 0x200] = { 0 };
		int SaveDirL = std::strlen(Steam_Config::SaveDirectory);
		int UGCSaveDirL = std::strlen(Steam_Config::UGCDirectotry);
		std::string Path = Directory;

		Path.append("*");

		hFind = FindFirstFileA(Path.c_str(), &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if ((std::strncmp(".", (char*)FindFileData.cFileName, 1) != 0) && (std::strncmp("..", (char*)FindFileData.cFileName, 2) != 0))
				{
					if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						if (std::strncmp(Directory, Steam_Config::SaveDirectory, SaveDirL) == 0) {
							std::memset(tmp, 0, sizeof(tmp));
							std::memcpy(tmp, &Directory[SaveDirL], (std::strlen(Directory) - SaveDirL));
							std::strcat(tmp, (char*)FindFileData.cFileName);
							FilesMatrix.push_back(tmp);
						}
						else if (std::strncmp(Directory, Steam_Config::UGCDirectotry, UGCSaveDirL) == 0) {
							std::memset(tmp, 0, sizeof(tmp));
							std::memcpy(tmp, &Directory[UGCSaveDirL], (std::strlen(Directory) - UGCSaveDirL));
							std::strcat(tmp, (char*)FindFileData.cFileName);
							FilesMatrix.push_back(tmp);
						}
						else {
							FilesMatrix.push_back((char*)FindFileData.cFileName);
						}
					}
					else {
						// Loop
						std::sprintf(path, "%s%s/", Directory, (char*)FindFileData.cFileName);
						FillFileStructure(path);
					}
				}
			} while (FindNextFileA(hFind, &FindFileData) == TRUE);
			FindClose(hFind);
		}
	}
	void Storage_Initializzation()
	{
		std::strcpy(Steam_Config::UGCDirectotry, Steam_Config::SaveDirectory);
		ColdAPI_Storage::GetUGCDirectory();
		ColdAPI_Storage::GetStorageDirectory();

		// Check if the directory exist
		int Arr = 0;
		char TempDir[0x400] = { 0 };

		for (;;)
		{
			if (Steam_Config::SaveDirectory[Arr] == NULL)
				break;
			std::memcpy(&TempDir[Arr], &Steam_Config::SaveDirectory[Arr], 1);
			if (Steam_Config::SaveDirectory[Arr] == '\\') {
				DWORD ftyp = GetFileAttributesA(TempDir);
				if (ftyp != INVALID_FILE_ATTRIBUTES && ftyp & FILE_ATTRIBUTE_DIRECTORY) {
					Arr++;
					continue;
				}
				CreateDirectoryA(TempDir, NULL);
			}
			Arr++;
		}
		Arr = 0;
		std::memset(TempDir, 0, 0x400);
		for (;;)
		{
			if (Steam_Config::UGCDirectotry[Arr] == NULL)
				break;
			std::memcpy(&TempDir[Arr], &Steam_Config::UGCDirectotry[Arr], 1);
			if (Steam_Config::UGCDirectotry[Arr] == '\\') {
				DWORD ftyp = GetFileAttributesA(TempDir);
				if (ftyp != INVALID_FILE_ATTRIBUTES && ftyp & FILE_ATTRIBUTE_DIRECTORY) {
					Arr++;
					continue;
				}
				CreateDirectoryA(TempDir, NULL);
			}
			Arr++;
		}
	}
	static bool UReady = false;
	const char* GetUGCDirectory()
	{
		if (!UReady)
		{
			if (std::strcmp(Steam_Config::UGCDirectotry, "Auto") == 0)
			{
				std::memset(Steam_Config::UGCDirectotry, 0, 0x400);
				std::strcpy(Steam_Config::UGCDirectotry, Steamapipath);
				std::strcat(Steam_Config::UGCDirectotry, "ColdStorage\\");
				std::strcat(Steam_Config::UGCDirectotry, Steam_Config::Username);
				std::strcat(Steam_Config::UGCDirectotry, "\\");
				std::strcat(Steam_Config::UGCDirectotry, ColdAPI_General::FormatTheString("%lu", EMPTY, Steam_Config::AppId));
				std::strcat(Steam_Config::UGCDirectotry, "\\");
				std::strcat(Steam_Config::UGCDirectotry, "LocalUGC\\");
			}
			else
			{
				int c = 0;

				// Search if the last byte was a "/".
				for (;;)
				{
					if (Steam_Config::UGCDirectotry[c] == NULL)
					{
						if (Steam_Config::UGCDirectotry[c - 1] != '\\' || Steam_Config::UGCDirectotry[c - 1] != '/')
							std::strcpy(&Steam_Config::UGCDirectotry[c], "\\");
						break;
					}
					c++;
				}
				std::strcat(Steam_Config::UGCDirectotry, "ColdStorage\\");
				std::strcat(Steam_Config::UGCDirectotry, Steam_Config::Username);
				std::strcat(Steam_Config::UGCDirectotry, "\\");
				std::strcat(Steam_Config::UGCDirectotry, ColdAPI_General::FormatTheString("%lu", EMPTY, Steam_Config::AppId));
				std::strcat(Steam_Config::UGCDirectotry, "\\");
				std::strcat(Steam_Config::UGCDirectotry, "LocalUGC\\");
			}
			UReady = true;
		}
		return Steam_Config::UGCDirectotry;
	}

	std::multimap<uint64_t, MyFileStream> Streams;
	uint64_t GlobalStream = 0;
	uint64_t ShareFile(const char* FileName)
	{
		return NULL;
	}
	uint64_t CFileWriteStreamOpen(const char* FileName)
	{
		if (!Steam_Config::RemoteStorage)
			return NULL;

		// Variables 
		char* FStreamName = nullptr;
		int SLength = std::strlen(FileName);
		MyFileStream stream;

		++GlobalStream;
		FStreamName = (char*)VirtualAlloc(nullptr, SLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (!FStreamName) {
			return NULL;
		}

		std::strcpy(FStreamName, FileName);
		stream.Buffer = nullptr;
		stream.FileNameS = FStreamName;
		stream.lastbuffersize = 0;

		Streams.insert(std::make_pair(GlobalStream, stream));
		return GlobalStream;
	}
	int32_t CFileWriteStreamWriteChunk(uint64_t hStream, const void* pvData, int32_t cubData)
	{
		if (!Steam_Config::RemoteStorage)
			return 1;
		if (!hStream)
			return 2;
		if (!pvData)
			return 2;
		if (!cubData)
			return 2;
		if (cubData > (100 * 1024 * 1024))
			return 2;

		auto StreamRequested = Streams.find(hStream);
		if (StreamRequested == Streams.end()) {
			return 2;
		}

		// Write our data 
		if (StreamRequested->second.Buffer == nullptr) {
			StreamRequested->second.Buffer = (char*)VirtualAlloc(nullptr, cubData, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if (!StreamRequested->second.Buffer) {
				return 2;
			}
			StreamRequested->second.lastbuffersize = cubData;
		}
		else {
			if (cubData > StreamRequested->second.lastbuffersize) {
				VirtualFree(StreamRequested->second.Buffer, NULL, MEM_RELEASE);
				StreamRequested->second.Buffer = (char*)VirtualAlloc(nullptr, cubData, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if (!StreamRequested->second.Buffer) {
					return 2;
				}
				StreamRequested->second.lastbuffersize = cubData;
			}
		}
		std::memcpy(StreamRequested->second.Buffer, pvData, cubData);
		return 1;
	}
	int32_t CFileWriteStreamClose(uint64_t hStream)
	{
		if (!Steam_Config::RemoteStorage)
			return 1;

		if (!hStream)
			return 2;

		auto StreamRequested = Streams.find(hStream);
		if (StreamRequested == Streams.end()) {
			return 2;
		}
		if (!StreamRequested->second.Buffer) {
			return 2;
		}
		if (!StreamRequested->second.FileNameS) {
			return 2;
		}

		// Save to our file
		std::FILE* FileStream = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(StreamRequested->second.FileNameS), "wb");
		if (FileStream)
		{
			std::fwrite(StreamRequested->second.Buffer, StreamRequested->second.lastbuffersize, 1, FileStream);
			std::fclose(FileStream);
		}
		
		if (StreamRequested->second.Buffer)
			VirtualFree(StreamRequested->second.Buffer, NULL, MEM_RELEASE);
		if(StreamRequested->second.FileNameS)
			VirtualFree(StreamRequested->second.FileNameS, NULL, MEM_RELEASE);
		Streams.erase(StreamRequested);
		return 1;
	}
	int32_t CFileWriteStreamCancel(uint64_t hStream)
	{
		if (!Steam_Config::RemoteStorage)
			return 1;

		if (!hStream)
			return 2;

		auto StreamRequested = Streams.find(hStream);
		if (StreamRequested == Streams.end()) {
			return 2;
		}
		if (StreamRequested->second.Buffer)
			VirtualFree(StreamRequested->second.Buffer, NULL, MEM_RELEASE);
		if (StreamRequested->second.FileNameS)
			VirtualFree(StreamRequested->second.FileNameS, NULL, MEM_RELEASE);
		Streams.erase(StreamRequested);
		return 1;
	}
	bool bCFileWriteStreamWriteChunk(uint64_t hStream, const void* pvData, int32_t cubData)
	{
		if (!Steam_Config::RemoteStorage)
			return true;

		if (!hStream)
			return false;
		if (!pvData)
			return false;
		if (!cubData)
			return false;
		if (cubData > (100 * 1024 * 1024))
			return false;

		auto StreamRequested = Streams.find(hStream);
		if (StreamRequested == Streams.end()) {
			return false;
		}

		// Write our data 
		if (StreamRequested->second.Buffer == nullptr) {
			StreamRequested->second.Buffer = (char*)VirtualAlloc(nullptr, cubData, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if (!StreamRequested->second.Buffer) {
				return false;
			}
			StreamRequested->second.lastbuffersize = cubData;
		}
		else {
			if (cubData > StreamRequested->second.lastbuffersize) {
				VirtualFree(StreamRequested->second.Buffer, NULL, MEM_RELEASE);
				StreamRequested->second.Buffer = (char*)VirtualAlloc(nullptr, cubData, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if (!StreamRequested->second.Buffer) {
					return false;
				}
				StreamRequested->second.lastbuffersize = cubData;
			}
		}
		std::memcpy(StreamRequested->second.Buffer, pvData, cubData);
		return true;
	}
	bool bCFileWriteStreamClose(uint64_t hStream)
	{
		if (!Steam_Config::RemoteStorage)
			return true;

		if (!hStream)
			return false;

		auto StreamRequested = Streams.find(hStream);
		if (StreamRequested == Streams.end()) {
			return false;
		}
		if (!StreamRequested->second.Buffer) {
			return false;
		}
		if (!StreamRequested->second.FileNameS) {
			return false;
		}

		// Save to our file
		std::FILE* FileStream = std::fopen(ColdAPI_Storage::ConnectDirectoryToFile(StreamRequested->second.FileNameS), "wb");
		if (FileStream)
		{
			std::fwrite(StreamRequested->second.Buffer, StreamRequested->second.lastbuffersize, 1, FileStream);
			std::fclose(FileStream);
		}

		if (StreamRequested->second.Buffer)
			VirtualFree(StreamRequested->second.Buffer, NULL, MEM_RELEASE);
		if (StreamRequested->second.FileNameS)
			VirtualFree(StreamRequested->second.FileNameS, NULL, MEM_RELEASE);
		Streams.erase(StreamRequested);
		return true;
	}
	bool bCFileWriteStreamCancel(uint64_t hStream)
	{
		if (!Steam_Config::RemoteStorage)
			return true;

		if (!hStream)
			return false;

		auto StreamRequested = Streams.find(hStream);
		if (StreamRequested == Streams.end()) {
			return false;
		}
		if (StreamRequested->second.Buffer)
			VirtualFree(StreamRequested->second.Buffer, NULL, MEM_RELEASE);
		if (StreamRequested->second.FileNameS)
			VirtualFree(StreamRequested->second.FileNameS, NULL, MEM_RELEASE);
		Streams.erase(StreamRequested);
		return true;
	}

	void CloseMem(void* Buffer)
	{
		if(Buffer)
			VirtualFree(Buffer, NULL, MEM_RELEASE);
	}
}
namespace ColdAPI_General
{
	const char* GetCountryFromLanguage(const char* Language)
	{
		if (std::strcmp(Language, "english") <= 0)
			return "UK England";
		if (std::strcmp(Language, "french") <= 0)
			return "French";
		if (std::strcmp(Language, "spanish") <= 0)
			return "Spain";
		if (std::strcmp(Language, "japanese") <= 0)
			return "Japan";
		if (std::strcmp(Language, "finnish") <= 0)
			return "Finland";
		if (std::strcmp(Language, "romanian") <= 0)
			return "Romania";
		if (std::strcmp(Language, "german") <= 0)
			return "Germany";
		if (std::strcmp(Language, "schinese") <= 0)
			return "China";
		if (std::strcmp(Language, "portuguese") <= 0)
			return "Portugal";
		if (std::strcmp(Language, "norwegian") <= 0)
			return "Norway";
		if (std::strcmp(Language, "turkish") <= 0)
			return "Turkey";
		if (std::strcmp(Language, "tchinese") <= 0)
			return "China";
		if (std::strcmp(Language, "polish") <= 0)
			return "Poland";
		if (std::strcmp(Language, "swedish") <= 0)
			return "Sweden";
		if (std::strcmp(Language, "italian") <= 0)
			return "Italy";
		if (std::strcmp(Language, "russian") <= 0)
			return "Russia";
		if (std::strcmp(Language, "danish") <= 0)
			return "Denmark";
		if (std::strcmp(Language, "hungarian") <= 0)
			return "Hungary";
		if (std::strcmp(Language, "koreana") <= 0)
			return "Korean";
		if (std::strcmp(Language, "thai") <= 0)
			return "Thailand";
		if (std::strcmp(Language, "dutch") <= 0)
			return "Netherlands";
		if (std::strcmp(Language, "czech") <= 0)
			return "Czech Republic";
		return "";
	}
	static char SteamDir[MAX_PATH] = { 0 };
	static char CurrentDirectory[MAX_PATH] = { 0 };
	const char* ColdAPI_GetSteamInstallPath()
	{
		if (std::strcmp(SteamDir, STEAM_NOTINSTALLED) == 0)
			return CurrentDirectory;
		if (std::strlen(SteamDir) == NULL)
		{
			HKEY Registrykey;
			if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, Steamregistry, 0, KEY_QUERY_VALUE, &Registrykey) == ERROR_SUCCESS)
			{
				DWORD Size = MAX_PATH;
				RegQueryValueExA(Registrykey, "InstallPath", NULL, NULL, (BYTE*)SteamDir, &Size);
				RegCloseKey(Registrykey);
			}
			else
			{
				std::strcpy(SteamDir, STEAM_NOTINSTALLED);
				GetCurrentDirectoryA(MAX_PATH, CurrentDirectory);
				return CurrentDirectory;
			}
		}
		return SteamDir;
	}
	void SetOverlayNotification(int Value)
	{
		FARPROC SetNotificationPositionExt = GetProcAddress(OverLayModule, "SetNotificationPosition");		// Load SetNotificationPosition from STEAMOVERLAY module
		if (SetNotificationPositionExt)
			((void(*)(int32_t))SetNotificationPositionExt)(Value);		// Call the virtual loaded function, most of people uses typedef method but in this way more fast
		else
			return;
	}
	bool IsOverlayNeededOrEnabled()
	{
		FARPROC OverLayEn = GetProcAddress(OverLayModule, "IsOverlayEnabled");		// Load IsOverlayEnabled from STEAMOVERLAY module
		if (OverLayEn)
			return ((bool(*)())OverLayEn)(); // Call the virtual loaded function, most of people uses typedef method but in this way more fast
		return false;
	}
	bool OverlayNeedsPresent()
	{
		FARPROC OverLayEn = GetProcAddress(OverLayModule, "BOverlayNeedsPresent");		// Load BOverlayNeedsPresent from STEAMOVERLAY module
		if (OverLayEn)
			return ((bool(*)())OverLayEn)(); // Call the virtual loaded function, most of people uses typedef method but in this way more fast
		return false;
	}
	int InitInterfaces()
	{
		InterfaceData StructureData = { 0 };

		// Load Interfaces
		std::string InterfaceName = "";
		void* SteamInterfaceAccessor = new SteamAppListIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPLIST_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_APPLIST;
		StructureData.Version = 1;
		InterfaceName = "SteamAppList";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 1;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 2;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 3;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 4;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 5;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 6;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 7;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppsIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPS_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_APPS;
		StructureData.Version = 8;
		InterfaceName = "SteamApps";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamAppTicketIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMAPPTICKET_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_APPTICKET;
		StructureData.Version = 1;
		InterfaceName = "SteamAppTicket";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamBillingIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMBILLING_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_BILLING;
		StructureData.Version = 1;
		InterfaceName = "SteamBilling";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamBillingIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMBILLING_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_BILLING;
		StructureData.Version = 2;
		InterfaceName = "SteamBilling";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 6;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 7;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 8;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 9;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_010;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 10;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn011();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_011;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 11;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn012();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_012;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 12;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn013();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_013;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 13;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn014();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_014;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 14;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn015();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_015;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 15;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn016();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_016;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 16;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn017();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_017;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 17;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn018();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_018;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 18;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamClientIn019();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCLIENT_INTERFACE_VERSION_019;
		StructureData.SteamType = CSteamInterface::STEAM_CLIENT;
		StructureData.Version = 19;
		InterfaceName = "SteamClient";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamContentServerIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTENTSERVER_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_CONTENTSERVER;
		StructureData.Version = 1;
		InterfaceName = "SteamContentServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamContentServerIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTENTSERVER_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_CONTENTSERVER;
		StructureData.Version = 2;
		InterfaceName = "SteamContentServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 1;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION002;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 2;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION003;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 3;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION004;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 4;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION005;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 5;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION006;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 6;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamControllerIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMCONTROLLER_INTERFACE_VERSION007;
		StructureData.SteamType = CSteamInterface::STEAM_CONTROLLER;
		StructureData.Version = 7;
		InterfaceName = "SteamController";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 1;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 2;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 3;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 4;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 5;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 6;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 7;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 8;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 9;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_010;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 10;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn011();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_011;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 11;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn012();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_012;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 12;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn013();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_013;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 13;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn014();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_014;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 14;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn015();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_015;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 15;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn016();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_016;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 16;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamFriendsIn017();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMFRIENDS_INTERFACE_VERSION_017;
		StructureData.SteamType = CSteamInterface::STEAM_FRIENDS;
		StructureData.Version = 17;
		InterfaceName = "SteamFriends";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameCoordinatorIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMECOORDINATOR_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_GAMECOORDINATOR;
		StructureData.Version = 1;
		InterfaceName = "SteamGameCoordinator";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameSearchIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESEARCH_INTERFACE_VERSION001;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESEARCH;
		StructureData.Version = 1;
		InterfaceName = "SteamGameSearch";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 2;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 3;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 4;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 5;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 6;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 7;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 8;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 9;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_010;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 10;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn011();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_011;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 11;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerIn012();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVER_INTERFACE_VERSION_012;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVER;
		StructureData.Version = 12;
		InterfaceName = "SteamGameServer";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamGameServerStatsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMGAMESERVERSTATS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_GAMESERVERSTATS;
		StructureData.Version = 1;
		InterfaceName = "SteamGameServerStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTMLSurfaceIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTMLSURFACE_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_HTMLSURFACE;
		StructureData.Version = 2;
		InterfaceName = "SteamHTMLSurface";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTMLSurfaceIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTMLSURFACE_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_HTMLSURFACE;
		StructureData.Version = 3;
		InterfaceName = "SteamHTMLSurface";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTMLSurfaceIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTMLSURFACE_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_HTMLSURFACE;
		StructureData.Version = 4;
		InterfaceName = "SteamHTMLSurface";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTMLSurfaceIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTMLSURFACE_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_HTMLSURFACE;
		StructureData.Version = 5;
		InterfaceName = "SteamHTMLSurface";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTTPIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTTP_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_HTTP;
		StructureData.Version = 1;
		InterfaceName = "SteamHTTP";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTTPIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTTP_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_HTTP;
		StructureData.Version = 2;
		InterfaceName = "SteamHTTP";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamHTTPIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMHTTP_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_HTTP;
		StructureData.Version = 3;
		InterfaceName = "SteamHTTP";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamInputIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMINPUT_INTERFACE_VERSION001;
		StructureData.SteamType = CSteamInterface::STEAM_INPUT;
		StructureData.Version = 1;
		InterfaceName = "SteamInput";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamInventoryIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMINVENTORY_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_INVENTORY;
		StructureData.Version = 1;
		InterfaceName = "SteamInventory";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamInventoryIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMINVENTORY_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_INVENTORY;
		StructureData.Version = 2;
		InterfaceName = "SteamInventory";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamInventoryIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMINVENTORY_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_INVENTORY;
		StructureData.Version = 3;
		InterfaceName = "SteamInventory";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 1;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 2;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 3;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 4;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 5;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 6;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 7;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 8;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKING_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKING;
		StructureData.Version = 9;
		InterfaceName = "SteamMatchmaking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingServersIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKINGSERVERS;
		StructureData.Version = 1;
		InterfaceName = "SteamMatchmakingServers";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMatchmakingServersIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_MATCHMAKINGSERVERS;
		StructureData.Version = 2;
		InterfaceName = "SteamMatchmakingServers";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMusicIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMUSIC_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_MUSIC;
		StructureData.Version = 1;
		InterfaceName = "SteamMusic";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamMusicRemoteIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMMUSICREMOTE_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_MUSICREMOTE;
		StructureData.Version = 1;
		InterfaceName = "SteamMusicRemote";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamNetworkingIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMNETWORKING_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_NETWORKING;
		StructureData.Version = 1;
		InterfaceName = "SteamNetworking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamNetworkingIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMNETWORKING_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_NETWORKING;
		StructureData.Version = 2;
		InterfaceName = "SteamNetworking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamNetworkingIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMNETWORKING_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_NETWORKING;
		StructureData.Version = 3;
		InterfaceName = "SteamNetworking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamNetworkingIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMNETWORKING_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_NETWORKING;
		StructureData.Version = 4;
		InterfaceName = "SteamNetworking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamNetworkingIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMNETWORKING_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_NETWORKING;
		StructureData.Version = 5;
		InterfaceName = "SteamNetworking";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamParentalSettingsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = "STEAMPARENTALSETTINGS_INTERFACE_VERSION001";
		StructureData.SteamType = CSteamInterface::STEAM_PARENTALSETTINGS;
		StructureData.Version = 1;
		InterfaceName = "SteamParentalSettings";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamPartiesIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMPARTIES_INTERFACE_VERSION002;
		StructureData.SteamType = CSteamInterface::STEAM_PARTIES;
		StructureData.Version = 2;
		InterfaceName = "SteamParties";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemotePlayIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTEPLAY_INTERFACE_VERSION001;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTEPLAY;
		StructureData.Version = 1;
		InterfaceName = "SteamRemotePlay";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 1;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 2;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 3;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 4;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 5;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 6;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 7;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 8;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 9;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_010;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 10;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn011();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_011;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 11;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn012();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_012;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 12;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn013();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_013;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 13;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamRemoteStorageIn014();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMREMOTESTORAGE_INTERFACE_VERSION_014;
		StructureData.SteamType = CSteamInterface::STEAM_REMOTESTORAGE;
		StructureData.Version = 14;
		InterfaceName = "SteamRemoteStorage";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamScreenshotsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMSCREENSHOTS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_SCREENSHOTS;
		StructureData.Version = 1;
		InterfaceName = "SteamScreenshots";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamScreenshotsIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMSCREENSHOTS_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_SCREENSHOTS;
		StructureData.Version = 2;
		InterfaceName = "SteamScreenshots";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamScreenshotsIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMSCREENSHOTS_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_SCREENSHOTS;
		StructureData.Version = 3;
		InterfaceName = "SteamScreenshots";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION001;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 1;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION002;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 2;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION003;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 3;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION004;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 4;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION005;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 5;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION007;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 7;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION008;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 8;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION009;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 9;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION010;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 10;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn012();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION012;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 12;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUGCIn013();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUGC_INTERFACE_VERSION013;
		StructureData.SteamType = CSteamInterface::STEAM_UGC;
		StructureData.Version = 13;
		InterfaceName = "SteamUGC";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUnifiedMessagesIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUNIFIEDMESSAGES_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_UNIFIEDMESSAGES;
		StructureData.Version = 1;
		InterfaceName = "SteamUnifiedMessages";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 4;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 5;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 6;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 7;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 8;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 9;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_010;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 10;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn011();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_011;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 11;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn012();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_012;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 12;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn013();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_013;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 13;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn014();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_014;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 14;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn015();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_015;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 15;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn016();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_016;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 16;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn017();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_017;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 17;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn018();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_018;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 18;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn019();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_019;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 19;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserIn020();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSER_INTERFACE_VERSION_020;
		StructureData.SteamType = CSteamInterface::STEAM_USER;
		StructureData.Version = 20;
		InterfaceName = "SteamUser";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 1;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 2;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 3;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 4;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 5;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 6;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 7;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 8;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 9;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn010();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_010;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 10;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUserStatsIn011();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUSERSTATS_INTERFACE_VERSION_011;
		StructureData.SteamType = CSteamInterface::STEAM_USERSTATS;
		StructureData.Version = 11;
		InterfaceName = "SteamUserStats";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 1;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 2;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn003();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_003;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 3;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn004();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_004;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 4;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn005();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_005;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 5;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn006();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_006;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 6;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn007();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_007;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 7;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn008();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_008;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 8;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamUtilsIn009();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMUTILS_INTERFACE_VERSION_009;
		StructureData.SteamType = CSteamInterface::STEAM_UTILS;
		StructureData.Version = 9;
		InterfaceName = "SteamUtils";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamVideoIn001();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMVIDEO_INTERFACE_VERSION_001;
		StructureData.SteamType = CSteamInterface::STEAM_VIDEO;
		StructureData.Version = 1;
		InterfaceName = "SteamVideo";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);
		SteamInterfaceAccessor = nullptr;
		SteamInterfaceAccessor = new SteamVideoIn002();
		StructureData.datapointer = SteamInterfaceAccessor;
		StructureData.isstarted = true;
		StructureData.key = STEAMVIDEO_INTERFACE_VERSION_002;
		StructureData.SteamType = CSteamInterface::STEAM_VIDEO;
		StructureData.Version = 2;
		InterfaceName = "SteamVideo";
		StructureData.name = InterfaceName;
		PublicInterfaces.push_back(StructureData);

		return 1;
	}
	char FormattedMessage[0x9000] = { 0 };
	void* ProvideInterface(int type, const char* Version, bool ScanForName)
	{
		if (ScanForName)
		{
			// Search interface by name 
			for (std::vector<InterfaceData>::size_type i = 0; i < PublicInterfaces.size(); i++)
				if (std::strcmp(PublicInterfaces[i].key.c_str(), Version) == 0)
					return PublicInterfaces[i].datapointer;

			// Looks like the interface is not available, warn if the user want it.
			if (Steam_Config::InterfaceNFound)
			{
				// Check if the user choosen to ignore the current interface.
				bool Ignore = false;
				for (auto iter = IgnoredWInterfacesS.begin(); iter != IgnoredWInterfacesS.end(); ++iter)
				{
					std::string CInterface = *iter;
					if (std::strcmp(CInterface.c_str(), Version) == 0)
					{
						Ignore = true;
						break;
					}
				}
				if (!Ignore) {
					std::memset(FormattedMessage, 0, sizeof(FormattedMessage));
					std::sprintf(FormattedMessage, "The interface %s couldn't be loaded or it is not available. Do you want to ignore the current interface and try to continue the execution? (Game might crash)", Version);

					// Print the message 
					if (MessageBoxA(NULL, FormattedMessage, "Interface error", MB_ICONWARNING | MB_YESNOCANCEL) == IDYES) {
						IgnoredWInterfacesS.push_back(Version);
					}
					else {
						ExitProcess(NULL);
					}
				}
			}
			return nullptr;
		}
		else
		{
			// Search interface by the enum type 
			int InVersion = 0;

			for (std::vector<InterfaceInfo>::size_type i = 0; i < PublicInterfacesInfo.size(); i++) {
				if (PublicInterfacesInfo[i].SteamType == type) {
					InVersion = PublicInterfacesInfo[i].Version;
					break;
				}
			}
			if (InVersion != 0) {
				for (std::vector<InterfaceData>::size_type i = 0; i < PublicInterfaces.size(); i++) {

					if (PublicInterfaces[i].SteamType == type && PublicInterfaces[i].Version == InVersion) {
						return PublicInterfaces[i].datapointer;
					}
				}
			}

			// Looks like the interface is not available, warn if the user want it.
			if (Steam_Config::InterfaceNFound)
			{
				// Check if the user choosen to ignore the current interface.
				bool Ignore = false;
				for (auto iter = IgnoredWInterfacesT.begin(); iter != IgnoredWInterfacesT.end(); ++iter)
				{
					if (iter->first == type && iter->second == InVersion)
					{
						Ignore = true;
						break;
					}
				}
				if (!Ignore) {
					std::memset(FormattedMessage, 0, sizeof(FormattedMessage));
					std::sprintf(FormattedMessage, "The interface id %d with version %d couldn't be loaded or it is not available. Do you want to ignore the current interface and try to continue the execution? (Game might crash)", type, InVersion);

					// Print the message 
					if (MessageBoxA(NULL, FormattedMessage, "Interface error", MB_ICONWARNING | MB_YESNOCANCEL) == IDYES) {
						IgnoredWInterfacesT.insert(std::make_pair(type, InVersion));
					}
					else {
						ExitProcess(NULL);
					}
				}
			}
			return nullptr;
		}
	}
	void* ContextInitializzation(void* Input)
	{
		int32_t hUser = SteamAPI_GetHSteamUser();
		SteamContext* Sctx = (SteamContext*)Input;
		if (Sctx->Flag != hUser)	// Check if the context isn't already initialized
		{
			Sctx->Flag = hUser;
			((void(*)(void*))Sctx->InitContext)(&Sctx->Out);
		}
		return (void*)&Sctx->Out;
	}
	bool ReadIni()
	{
		char SteamORG[MAX_PATH] = { 0 };
		std::strcpy(SteamORG, Steamapipath);
		std::strcat(SteamORG, ORGAPI);
		char SteamINI[MAX_PATH] = { 0 };
		std::strcpy(SteamINI, Steamapipath);
		std::strcat(SteamINI, INI);

		// Read from INI
		Steam_Config::AppId = GetPrivateProfileIntA("SteamData", "AppID", NULL, SteamINI);
		Steam_Config::AppBuildId = GetPrivateProfileIntA("SteamData", "AppBuildId", NULL, SteamINI);
		Steam_Config::OnlineMod = GetPrivateProfileIntA("SteamData", "OnlineMode", NULL, SteamINI) != FALSE;
		Steam_Config::UnlockAllDLCS = GetPrivateProfileIntA("SteamData", "UnlockAllDLCs", true, SteamINI) != FALSE;
		Steam_Config::LowViolence = GetPrivateProfileIntA("SteamProfile", "LowViolence", NULL, SteamINI) != FALSE;
		Steam_Config::RemoteStorage = GetPrivateProfileIntA("SteamData", "SteamFileSave", true, SteamINI) != FALSE;
		Steam_Config::StubBypass = GetPrivateProfileIntA("SteamAdditional", "PatchSteamStub", NULL, SteamINI) != FALSE;
		Steam_Config::ClientEmulation = GetPrivateProfileIntA("SteamAdditional", "ClientEmulation", NULL, SteamINI) != FALSE;
		Steam_Config::HookForInjection = GetPrivateProfileIntA("SteamClient", "HookInjectionMode", NULL, SteamINI) != FALSE;
		Steam_Config::InterfaceNFound = GetPrivateProfileIntA("SteamAdditional", "WarnInterfaceNFound", NULL, SteamINI) != FALSE;

		GetPrivateProfileStringA("SteamProfile", "Username", "ColdAPI", Steam_Config::Username, sizeof(Steam_Config::Username), SteamINI);
		GetPrivateProfileStringA("SteamProfile", "Language", "english", Steam_Config::Language, sizeof(Steam_Config::Language), SteamINI);
		GetPrivateProfileStringA("SteamData", "SavePath", "Auto", Steam_Config::SaveDirectory, sizeof(Steam_Config::SaveDirectory), SteamINI);

		// DLC attempt:
		if (!Steam_Config::UnlockAllDLCS)
		{
			bool NullByte = false;
			size_t OffSet = 0;
			char String[500] = { 0 };
			char Section[0x900] = { 0 };
			GetPrivateProfileSectionA("DLC", Section, sizeof(Section), SteamINI);
			uint32_t DAppid = 0;

			// GetDLCs
			while (std::memcmp(&Section[OffSet], &NullByte, 1) != 0)
			{
				// Scan the string.
				std::sscanf(&Section[OffSet], "%u=%[^\n]", &DAppid, String);

				ColdDLC_Config::DLCsAPPID.push_back(DAppid);
				ColdDLC_Config::DLCsNames.push_back(String);
				ColdDLC_Config::DLCsCount++;
				
				// Prepare for next DLC String Info
				std::memset(String, 0, sizeof(String));
				DAppid = 0;

				// Calculate the offset for the next string, just get the string length and add 1 byte.
				size_t SSize = std::strlen(&Section[OffSet]) + 1;
				OffSet += SSize;
			}
		}
		// Check if we should read interfaces from the original steam_api.
		if (GetPrivateProfileIntA("SteamAdditional", "InterfaceChecker", NULL, SteamINI) == TRUE)
		{
			HANDLE hOrg = CreateFileA(SteamORG, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hOrg == INVALID_HANDLE_VALUE) {
				MessageBoxA(NULL, "Couldn't load steam_api(64).org for scanning interfaces.", "ColdAPI", MB_ICONERROR);
				ExitProcess(NULL);
			}
			HANDLE hMap = CreateFileMapping(hOrg, 0, PAGE_READONLY, 0, 0, 0);
			if (hMap == NULL) {
				CloseHandle(hOrg);
				MessageBoxA(NULL, "Couldn't map in memory steam_api(64).org for scanning interfaces.", "ColdAPI", MB_ICONERROR);
				ExitProcess(NULL);
			}
			LPVOID bytesorg = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
			if(bytesorg == nullptr) {
				CloseHandle(hMap);
				CloseHandle(hOrg);
				MessageBoxA(NULL, "Couldn't map in memory steam_api(64).org for scanning interfaces.", "ColdAPI", MB_ICONERROR);
				ExitProcess(NULL);
			}

			auto DosP = (IMAGE_DOS_HEADER*)bytesorg;
			auto NtP = (IMAGE_NT_HEADERS*)((ULONG_PTR)bytesorg + DosP->e_lfanew);
			auto SecP = IMAGE_FIRST_SECTION(NtP);

			// Scan sectiion for names.
			bool ExpectedSFound = false;
			for (int i = 0; i < NtP->FileHeader.NumberOfSections; i++) {
				if (std::strcmp((char*)SecP->Name, ".rdata") == 0) {
					ExpectedSFound = true;
					break;
				}
				SecP++;
			}
			
			if (ExpectedSFound)
			{
				// We have now the original steam_api section base address. Let's search the string into it.
				auto Buff = (LPSTR)((ULONG_PTR)bytesorg + SecP->PointerToRawData);

				// Iter on our initialized interfaces
				auto CInterfaceIter = PublicInterfaces.begin();
				bool FoundSomething = false;

				while (CInterfaceIter != PublicInterfaces.end())
				{
					InterfaceData InterfaceC = *CInterfaceIter;

					// Loop to the sectiion 
					for (unsigned int i = 0; i < SecP->SizeOfRawData; i++)
					{
						unsigned int RemainingBytes = SecP->SizeOfRawData - i;
						int Length = std::strlen(InterfaceC.key.c_str());

						if (RemainingBytes >= Length)
						{
							if (std::memcmp(&Buff[i], InterfaceC.key.c_str(), Length) == 0)
							{
								InterfaceInfo PublicInfo = { InterfaceC.SteamType, InterfaceC.Version };
								PublicInterfacesInfo.push_back(PublicInfo);
								WritePrivateProfileStringA("SteamInterfaces", InterfaceC.name.c_str(), ColdAPI_General::FormatTheString("%d", EMPTY, InterfaceC.Version),
									SteamINI);
								if (!FoundSomething)
									FoundSomething = true;
								break;
							}
						}
					}
					++CInterfaceIter;
				}

				WritePrivateProfileStringA("SteamAdditional", "InterfaceChecker", "0", SteamINI);	// Disable interface checker
				UnmapViewOfFile(bytesorg);
				CloseHandle(hMap);
				CloseHandle(hOrg);
				return true;
			}
		}
		else 
		{
			// Iter on our initialized interfaces
			int LVersion = 0;
			CSteamInterface b;
			bool Dones[38] = { 0 };
			for (auto CInterfaceIter = PublicInterfaces.begin(); CInterfaceIter != PublicInterfaces.end(); ++CInterfaceIter)
			{
				InterfaceData InterfaceC = *CInterfaceIter;

				// Check and read interface types.
				if (!Dones[InterfaceC.SteamType])
				{
					// To be safe we search the latest interface version as it'll be used if it was not specified from the ini.
					auto LCInterfaceIter = CInterfaceIter;
					for (;;) {
						if (LCInterfaceIter == PublicInterfaces.end()) {
							// Should be the latest.
							--LCInterfaceIter;
							InterfaceData LInterfaceC = *LCInterfaceIter;
							LVersion = LInterfaceC.Version;
							break;
						}
						InterfaceData LInterfaceC = *LCInterfaceIter;
						if (InterfaceC.SteamType != LInterfaceC.SteamType) {
							// Should be the latest.
							--LCInterfaceIter;
							LInterfaceC = *LCInterfaceIter;
							LVersion = LInterfaceC.Version;
							break;
						}
						++LCInterfaceIter;
					}

					int RVersion = GetPrivateProfileIntA("SteamInterfaces", InterfaceC.name.c_str(), LVersion, SteamINI);
					InterfaceInfo PublicInfo = { InterfaceC.SteamType, RVersion };
					PublicInterfacesInfo.push_back(PublicInfo);

					// Mark interface type as read
					Dones[InterfaceC.SteamType] = true;
				}
			}
		}
		return true;
	}
	const char* FormatTheString(const char* Format, const char* ValueS, uint64_t ValueU)
	{
		char TheString[300] = { 0 };
		if (std::strcmp(ValueS, EMPTY) == 0) {
			std::sprintf(TheString, Format, ValueU);
			return TheString;
		}
		std::sprintf(TheString, Format, ValueS);
		return TheString;
	}
}
namespace ColdAPI_InitAndShutDown
{
	static bool IsInitialized = false;
	bool ColdClientInitializzation()
	{
		if (!IsInitialized)
		{
			// Init Interfaces.
			ColdAPI_General::InitInterfaces();

			// Configuration attempt.
			ColdAPI_General::ReadIni();

			if (Steam_Config::AppId == NULL)
			{
				char SteamAPPID[MAX_PATH] = { 0 };
				std::strcpy(SteamAPPID, Steamapipath);
				std::strcat(SteamAPPID, STEAMAPPID);

				// Read from steam_appid.txt file if the APPID wasn't provided from the INI.
				std::FILE* hSteamAPPID = std::fopen(SteamAPPID, "r");
				if (hSteamAPPID) 
				{
					std::fscanf(hSteamAPPID, "%u", &Steam_Config::AppId);
					std::fclose(hSteamAPPID);
				}
			}
			if (Steam_Config::AppId == NULL)
			{
				MessageBoxA(NULL, "Please set an AppID and try again.", "ColdAPI", MB_ICONERROR);
				ExitProcess(NULL);
			}

			// Check if we're not emulating steamclient as Registry is mainly used to get the steamclient directory to load it and for process checks.
			if (!Steam_Config::ClientEmulation)
			{
				SetEnvironmentVariableA("SteamAppId", ColdAPI_General::FormatTheString("%lu", EMPTY, Steam_Config::AppId));
				SetEnvironmentVariableA("SteamGameId", ColdAPI_General::FormatTheString("%llu", EMPTY, Steam_Config::AppId & 0xFFFFFF));

				// Overlay
				std::string OverLay64 = "GameOverlayRenderer64.dll";
				std::string OverLay32 = "GameOverlayRenderer.dll";

				std::string OverLay = "";
#ifdef _WIN64
				OverLay = OverLay64;
#else
				OverLay = OverLay32;
#endif 
				OverLayModule = GetModuleHandleA(OverLay.c_str());
			}
			
			// Check if we should hook LoadLibraries functions 
			if (Steam_Config::ClientEmulation)
			{
				if (Steam_Config::HookForInjection)
				{
					ColdClientHookManager::ColdClientHookInit();
				}
			}

			if (Steam_Config::RemoteStorage)
			{
				ColdAPI_Storage::Storage_Initializzation();
			}
			if (Steam_Config::StubBypass)
			{
				SteamStubBypass::Patch();
			}
			IsInitialized = true;
		}
		return IsInitialized;
	}
	void ColdClientShutDown()
	{
		// Add something if needed but usually this is useless.
		return;
	}
}