#pragma once
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <cstdint>
#include <ctime>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <mutex>
#include <map>
#include <stdio.h>
#include <wchar.h>
#include "DistormDisassembler\include\distorm.h"

#define MAX_HOOKS 0x90000

// Errors
#define FALIED_NEEDS_INITIALIZATION 40
#define FALIED_ALREADY_INITIALIZED 60
#define FALIED_HOOK_EXISTS 50
#define FALIED_HOOK_NOT_EXISTS 80
#define FALIED_BUFFER_CREATION 33
#define FALIED_INVALID_PARAMETER 19
#define FALIED_ALREADY_EXISTS 66
#define FALIED_NOT_EXISTS 67
#define FALIED_FREE_MEMORY 68
#define FALIED_UNHOOK 69
#define FALIED_HOOK 79
#define FALIED_NOT_ALLOWED 89
#define FALIED_NOT_HOOKED 56
#define FALIED_ALLOCATION 22
#define FALIED_NO_ACCESS 23
#define FALIED_DISASSEMBLER 25
#define FALIED_MEM_PROTECTION 26
#define FALIED_MODULE_NOT_FOUND 27
#define FALIED_FUNCTION_NOT_FOUND 28
#define FALIED_OUT_RANGE 29

// Warnings
#define WARN_32_BIT 24

struct Hook_Info
{
	Hook_Info() : StatusHooked(false),
		Trampoline(false),
		OriginalF(NULL),
		HFunction(NULL),
		TrampolinePage(NULL),
		OrgData(NULL),
		HookData(NULL),
		HookSize(NULL),
		TrampolineSize(NULL),
		ModuleName(""),
		FunctionName("") {}

	bool StatusHooked;
	bool Trampoline;

	void* OriginalF;
	void* HFunction;
	void* TrampolinePage;

	void* OrgData;
	void* HookData;

	size_t HookSize;
	size_t TrampolineSize;
	
	// Optional members
	std::string ModuleName;
	std::string FunctionName;
};

namespace ColdHook_Service
{
	// Private functions:
	namespace
	{
		//  Disassembler call
		static unsigned int DisasmRange(SIZE_T* OutPutInstructionsSize, ULONG_PTR* OutNextInst, SIZE_T HookSize, _OffsetType BaseAddressFormat, int DVer, void* Buffer);

		// Generate base address
		static void* AllocateTrampoline(ULONG_PTR StartBaseAddress, SIZE_T PageS, int32_t* OutErrorCode, SIZE_T* ChangedHookSize);

		// Arch
		static bool Is64BitProcess();

		// Custom 
		static bool IsAddressRegisteredAsHook(void* Address);
	}

	// Function wrap hooks
	int32_t InitFunctionHookByName(Hook_Info* OutputInfo, bool WrapFunction, bool CheckKBase, const char* ModulName, const char* FName, void* HookedF, int32_t* OutErrorCode);
	int32_t InitFunctionHookByAddress(Hook_Info* OutputInfo, bool WrapFunction, void* Target, void* HookedF, int32_t* OutErrorCode);

	// Memory custom hook
	int32_t InitHookCustomData(Hook_Info* OutputInfo, void* Target, void* CustomData, size_t CSize, int32_t* OutErrorCode);

	// UnHook
	bool UnHookRegisteredData(int32_t HookID, int32_t* OutErrorCode);
	bool HookAgainRegisteredData(int32_t HookID, int32_t* OutErrorCode);

	// Init And shut down
	bool ServiceGlobalInit(int32_t* OutErrorCode);
	bool ServiceGlobalShutDown(int32_t* OutErrorCode);

	// Informations
	bool RetrieveHookInfoByID(Hook_Info* OutputInfo, int32_t HookID, int32_t* OutErrorCode);
	bool RetrieveHookIDByInfo(Hook_Info* InputInfo, int32_t* OutHookID, int32_t* OutErrorCode);

	bool ServiceRegisterHookInformation(Hook_Info* InputInfo, int32_t HookID, int32_t* OutErrorCode);
	bool ServiceUnRegisterHookInformation(int32_t HookID, int32_t* OutErrorCode);
}