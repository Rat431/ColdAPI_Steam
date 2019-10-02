#include "SteamStub.h"
ULONG_PTR BindStrt = 0;
ULONG_PTR BindEndt = 0;

BYTE int3bp[2] = { 0xCC, 0x90 };
BYTE orgdata[2] = { 0 };
BYTE orgdata2[2] = { 0 };
#ifdef _WIN64
BYTE VirtualAllocOrgData[12] = { 0 };
#else
BYTE VirtualAllocOrgData[6] = { 0 };
#endif 

BYTE StubPattern1[2] = { 0x3C, 0x30 };
BYTE StubPatternPatch1[2] = { 0x38, 0xC0 };
BYTE StubPattern2[5] = { 0x3D, 0x10, 0x27, 0x00, 0x00 };
BYTE StubPatternPatch2[5] = { 0x39, 0xC0, 0x90, 0x90, 0x90 };
BYTE operators[3] = { 0x0F, 0x74, 0x76 };
FARPROC IsDebuggerPresentAPI = 0;
FARPROC _GetFileSize = 0;
FARPROC GetTickCountAPI = 0;
FARPROC VirtualAllocAPI = 0;
HMODULE hKernelBase = 0;
HMODULE hNtdll = 0;
HMODULE hKernel = 0;
int found = 0;
DWORD OldProtect = 0;
void* fakeGetTickCount = nullptr;
LPVOID StubBuf[10000] = { 0 };
SIZE_T StubBufSize[10000] = { 0 };
long long data = 0;

typedef NTSTATUS(WINAPI* _NtAllocateVirtualMemory)(_In_ HANDLE, _Inout_ PVOID*, _In_  ULONG_PTR, _Inout_ PSIZE_T, _In_ ULONG, _In_  ULONG);
_NtAllocateVirtualMemory __NtAllocateVirtualMemory;

bool checked = false;

extern "C" _declspec(dllexport) LPVOID WVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtect)
{
	NTSTATUS status = __NtAllocateVirtualMemory(GetCurrentProcess(), &lpAddress, NULL, &dwSize, flAllocationType, flProtect);
	if (!status)
	{
		if (lpAddress)
		{
			StubBuf[data] = lpAddress;
			StubBufSize[data] = dwSize;
			data++;
			return lpAddress;
		}
	}

	return NULL;
}


LONG WINAPI handledExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo) //Handler
{

	if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT)
	{
		if (found)
			return EXCEPTION_CONTINUE_SEARCH;

		ULONG_PTR returnAddress = 0;
		ULONG_PTR returnAddress2 = 0;
		bool isstub = false;
#ifndef _WIN64
		memcpy(&returnAddress, (void*)pExceptionInfo->ContextRecord->Esp, 4);
#else
		memcpy(&returnAddress, (void*)pExceptionInfo->ContextRecord->Rsp, 8);
#endif 
		bool found = false;
		ULONG_PTR addrs = 0;
		for (long long i = 0; i < data; i++) {
			addrs = (ULONG_PTR)StubBuf[i];
			for (SIZE_T b = 0; b < StubBufSize[i]; b++) {
				if (addrs == returnAddress) {
					found = true;
					break;
				}
				addrs++;
			}
			if (found)
				break;
		}
		isstub = found;
		ULONG_PTR oldaddr = returnAddress;
		if (isstub)
		{
			DWORD old = 0;
			int patternfound = 0;
			ULONG_PTR pattern1addr, pattern2addr;
			for (;;)
			{
				if (patternfound == 0)
				{
					if (memcmp((void*)returnAddress, StubPattern1, sizeof(StubPattern1)) == 0)
					{
						for (int b = 0; b < sizeof(operators); b++)
						{
							if (memcmp((void*)((ULONG_PTR)returnAddress + 2), &operators[b], 1) == 0)
							{
								patternfound = 1;
								pattern1addr = returnAddress;
								break;
							}
						}
					}
				}

				if (patternfound == 1)
				{
					if (memcmp((void*)returnAddress, StubPattern2, sizeof(StubPattern2)) == 0)
					{
						for (int b = 0; b < sizeof(operators); b++)
						{
							if (memcmp((void*)((ULONG_PTR)returnAddress + 5), &operators[b], 1) == 0)
							{
								patternfound = 2;
								pattern2addr = returnAddress;
								break;
							}
						}
					}
				}
				if (patternfound == 2)
					break;
				returnAddress++;
			}
			if (patternfound == 2)
			{
				DWORD POLD;
				VirtualProtect((void*)pattern1addr, sizeof(StubPatternPatch1), PAGE_EXECUTE_READWRITE, &POLD);
				memcpy((void*)pattern1addr, StubPatternPatch1, sizeof(StubPatternPatch1));
				VirtualProtect((void*)pattern1addr, sizeof(StubPatternPatch1), POLD, &POLD);
				VirtualProtect((void*)pattern2addr, sizeof(StubPatternPatch2), PAGE_EXECUTE_READWRITE, &POLD);
				memcpy((void*)pattern2addr, StubPatternPatch2, sizeof(StubPatternPatch2));
				VirtualProtect((void*)pattern2addr, sizeof(StubPatternPatch2), POLD, &POLD);
				memcpy((void*)IsDebuggerPresentAPI, orgdata, sizeof(orgdata));
				memcpy((void*)GetTickCountAPI, orgdata2, sizeof(orgdata2));
				memcpy((void*)VirtualAllocAPI, VirtualAllocOrgData, sizeof(VirtualAllocOrgData));
				found++;
			}


		}
#ifdef _WIN64
		if (pExceptionInfo->ContextRecord->Rip == (ULONG_PTR)GetTickCountAPI)
		{
			pExceptionInfo->ContextRecord->Rip = (ULONG_PTR)fakeGetTickCount;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		pExceptionInfo->ContextRecord->Rax = (ULONG_PTR)0;
		pExceptionInfo->ContextRecord->Rsp = pExceptionInfo->ContextRecord->Rsp + 8;
		pExceptionInfo->ContextRecord->Rip = oldaddr;
#else
		if (pExceptionInfo->ContextRecord->Eip == (ULONG_PTR)GetTickCountAPI)
		{
			pExceptionInfo->ContextRecord->Eip = (ULONG_PTR)fakeGetTickCount;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		pExceptionInfo->ContextRecord->Eax = (ULONG_PTR)0;
		pExceptionInfo->ContextRecord->Esp = pExceptionInfo->ContextRecord->Esp + 4;
		pExceptionInfo->ContextRecord->Eip = oldaddr;
#endif // _WIN64
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}
namespace SteamStubBypass
{
	bool PatchSteamStub(ULONG_PTR BindStart, ULONG_PTR BindEnd, ULONG_PTR entryexe)
	{
		hKernel = GetModuleHandleA("kernel32.dll"); // Hooks
		hNtdll = GetModuleHandleA("ntdll.dll");
		hKernelBase = GetModuleHandleA("kernelbase.dll");
		if (!hKernel)
			return false;
		if (!hNtdll)
			return false;
		if (!hKernelBase)
			return false;

		IsDebuggerPresentAPI = GetProcAddress(hKernel, "IsDebuggerPresent");
		GetTickCountAPI = GetProcAddress(hKernel, "GetTickCount");
		__NtAllocateVirtualMemory = (_NtAllocateVirtualMemory)GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
		VirtualAllocAPI = GetProcAddress(hKernelBase, "VirtualAlloc");
		ULONG_PTR myWrapper = (ULONG_PTR)GetProcAddress(SteamApimod, "WVirtualAlloc");


		if (!IsDebuggerPresentAPI)
			return false;
		if (!GetTickCountAPI)
			return false;
		if (!__NtAllocateVirtualMemory)
			return false;
		if (!VirtualAllocAPI)
			return false;

#ifdef _WIN64
		BYTE VirtualAllocHookData[12] = { 0x48, 0xB8 };
		memcpy(&VirtualAllocHookData[2], &myWrapper, 8);
		VirtualAllocHookData[10] = 0xFF;
		VirtualAllocHookData[11] = 0xE0;
#else
		BYTE VirtualAllocHookData[6] = { 0x68 };
		memcpy(&VirtualAllocHookData[1], &myWrapper, 4);
		VirtualAllocHookData[5] = 0xC3;
#endif 

		if (!VirtualProtect((void*)IsDebuggerPresentAPI, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;
		if (!VirtualProtect((void*)GetTickCountAPI, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;
		if (!VirtualProtect((void*)VirtualAllocAPI, sizeof(VirtualAllocHookData), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;

		memcpy(orgdata, (void*)IsDebuggerPresentAPI, sizeof(orgdata));
		memcpy((void*)IsDebuggerPresentAPI, int3bp, sizeof(int3bp));
		fakeGetTickCount = VirtualAlloc(NULL, 1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		long funcsize = 0;
		BYTE endfbyte[1] = { 0xC3 };
		ULONG_PTR func = (ULONG_PTR)GetTickCountAPI;
		while (memcmp((void*)func, endfbyte, 1) != 0)
		{
			func++;
			funcsize++;
		}
		funcsize++;
		memcpy(fakeGetTickCount, (void*)GetTickCountAPI, funcsize);
		memcpy(orgdata2, (void*)GetTickCountAPI, sizeof(orgdata2));
		memcpy((void*)GetTickCountAPI, int3bp, sizeof(int3bp));
		memcpy(VirtualAllocOrgData, (void*)VirtualAllocAPI, sizeof(VirtualAllocOrgData));
		memcpy((void*)VirtualAllocAPI, VirtualAllocHookData, sizeof(VirtualAllocHookData));
		AddVectoredExceptionHandler(true, handledExceptionFilter);

		BindEndt = BindEnd;
		BindStrt = BindStart;
		return true;
	}
	void Patch()
	{
		HMODULE hExe = GetModuleHandleA(NULL);
		auto DosHeader = (IMAGE_DOS_HEADER*)hExe;
		auto ntheader = (IMAGE_NT_HEADERS*)((ULONG_PTR)hExe + DosHeader->e_lfanew);
		auto psection = IMAGE_FIRST_SECTION(ntheader);
		int stubdetected = 0;
		ULONG_PTR strt1, end1;
		for (int i = 0; i < ntheader->FileHeader.NumberOfSections; i++)
		{
			if (strcmp((char*)psection->Name, ".bind") == 0)
			{
				strt1 = (ULONG_PTR)hExe + psection->VirtualAddress;
				end1 = (ULONG_PTR)strt1 + psection->Misc.VirtualSize;
				stubdetected = 1;
				break;
			}
			psection++;
		}
		ULONG_PTR entrypoint = (ULONG_PTR)hExe + ntheader->OptionalHeader.AddressOfEntryPoint;
		for (ULONG_PTR i = strt1; i < end1; i++) {
			if (entrypoint == i) {
				stubdetected = 2;
				break;
			}
		}
		if (stubdetected == 2)
			PatchSteamStub(strt1, end1, (ULONG_PTR)hExe + ntheader->OptionalHeader.AddressOfEntryPoint);
	}
}