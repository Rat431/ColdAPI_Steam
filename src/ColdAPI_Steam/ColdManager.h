#pragma once
#include "Bridge.h"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <Dbghelp.h>
#include "Hook_utils/ColdHook.h"
#include "SteamStubBypass/SteamStub.h"

namespace ColdHookEmu
{
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryA(
		LPCSTR lpLibFileName
	);
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryW(
		LPCWSTR lpLibFileName
	);
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryExA(
		LPCSTR lpLibFileName,
		HANDLE hFile,
		DWORD  dwFlags
	);
	extern "C" _declspec(dllexport) HMODULE WINAPI CLoadLibraryExW(
		LPCWSTR lpLibFileName,
		HANDLE  hFile,
		DWORD   dwFlags
	);
}
namespace ColdClientHookManager
{
	void ColdClientHookInit();
}
namespace ColdAPI_General
{
	const char* GetCountryFromLanguage(const char* Language);
	const char* ColdAPI_GetSteamInstallPath();
	void SetOverlayNotification(int Value);
	bool IsOverlayNeededOrEnabled();
	bool OverlayNeedsPresent();
	int InitInterfaces();
	void* ProvideInterface(int type, const char* Version, bool ScanForName);
	void* ContextInitializzation(void* Input);
	bool ReadIni();
	const char* FormatTheString(const char* Format, const char* ValueS, uint64_t ValueU);
}
namespace ColdAPI_DLC
{
	bool GetDLCByIndex(int iDLC, unsigned int* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize);
	bool IsDLCAvailable(uint32_t Appid);
	int GetDlCCount();
}
namespace ColdAPI_Storage
{
	char* ConnectDirectoryToFile(const char* FileName);
	char* ConnectUGCDirectoryToFile(const char* FileName);
	const char* GetStorageDirectory();
	const char* GetUGCDirectory();
	void FillFileStructure(const char* Directory);
	void Storage_Initializzation();

	uint64_t ShareFile(const char* FileName);

	uint64_t CFileWriteStreamOpen(const char* FileName);
	int32_t CFileWriteStreamWriteChunk(uint64_t hStream, const void* pvData, int32_t cubData);
	int32_t CFileWriteStreamClose(uint64_t hStream);
	int32_t CFileWriteStreamCancel(uint64_t hStream);
	bool bCFileWriteStreamWriteChunk(uint64_t hStream, const void* pvData, int32_t cubData);
	bool bCFileWriteStreamClose(uint64_t hStream);
	bool bCFileWriteStreamCancel(uint64_t hStream);

	void CloseMem(void* Buffer);
}
namespace ColdAPI_InitAndShutDown
{
	bool ColdClientInitializzation();
	void ColdClientShutDown();
}