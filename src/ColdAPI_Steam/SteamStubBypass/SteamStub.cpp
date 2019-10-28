#include "SteamStub.h"
ULONG_PTR BindStrt = 0;
ULONG_PTR BindEndt = 0;

BYTE int3bp[2] = { 0xCC, 0x90 };
BYTE orgdata[2] = { 0 };
BYTE orgdata2[2] = { 0 };
#ifdef _WIN64
BYTE VirtualAllocOrgData[12] = { 0 };
BYTE KIUEDOrgData[12] = { 0 };
#else
BYTE VirtualAllocOrgData[6] = { 0 };
BYTE KIUEDOrgData[6] = { 0 };
#endif 

// Declare patterns arrays variables.
BYTE StubPattern1[2] = { 0x3C, 0x30 };
BYTE StubPatternPatch1[2] = { 0x38, 0xC0 };
BYTE StubPattern2[5] = { 0x3D, 0x10, 0x27, 0x00, 0x00 };
BYTE StubPatternPatch2[5] = { 0x39, 0xC0, 0x90, 0x90, 0x90 };
BYTE StubPattern3[4] = { 0xF6, 0x47, 0xA8, 0x04 };
BYTE operators[4] = { 0x0F, 0x74, 0x76, 0x75 };

// Declare functions pointers for hooking.
FARPROC IsDebuggerPresentAPI = 0;
FARPROC _GetFileSize = 0;
FARPROC GetTickCountAPI = 0;
FARPROC KIUEDApi = 0;
FARPROC CtxR = 0;
FARPROC VirtualAllocAPI = 0;
HMODULE hKernelBase = 0;
DWORD OldProtect = 0;

HMODULE hNtdll = 0;
HMODULE hKernel = 0;
int found = 0;

LPVOID StubBuf[10000] = { 0 };
SIZE_T StubBufSize[10000] = { 0 };
long long data = 0;


bool SStepFlag = false;
ULONG_PTR PrecAddress = 0;


typedef NTSTATUS(WINAPI* _NtAllocateVirtualMemory)(_In_ HANDLE, _Inout_ PVOID*, _In_  ULONG_PTR, _Inout_ PSIZE_T, _In_ ULONG, _In_  ULONG);
_NtAllocateVirtualMemory __NtAllocateVirtualMemory;

extern "C" void CallDispatcherData(void* Dispatcher);
bool checked = false;

extern "C" _declspec(dllexport) LPVOID WINAPI WVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtect)
{
	NTSTATUS status = __NtAllocateVirtualMemory((HANDLE)-1, &lpAddress, NULL, &dwSize, flAllocationType, flProtect);
	if (status == NULL)
	{
		if (lpAddress)
		{
			if (data <= sizeof(StubBuf))
			{
				// Save page informations (base address, size) for later.
				StubBuf[data] = lpAddress;
				StubBufSize[data] = dwSize;
				data++;
			}
			return lpAddress;
		}
	}
	return NULL;
}

void RestoreHooks()
{
	DWORD POLD = 0;
	if (!VirtualProtect((void*)KIUEDApi, sizeof(KIUEDOrgData), PAGE_EXECUTE_READWRITE, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}
	std::memcpy((void*)KIUEDApi, KIUEDOrgData, sizeof(KIUEDOrgData));
	if (!VirtualProtect((void*)KIUEDApi, sizeof(KIUEDOrgData), POLD, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}

	if (!VirtualProtect((void*)VirtualAllocAPI, sizeof(VirtualAllocOrgData), PAGE_EXECUTE_READWRITE, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}
	std::memcpy((void*)VirtualAllocAPI, VirtualAllocOrgData, sizeof(VirtualAllocOrgData));
	if (!VirtualProtect((void*)VirtualAllocAPI, sizeof(VirtualAllocOrgData), POLD, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}

	if (!VirtualProtect((void*)IsDebuggerPresentAPI, sizeof(orgdata), PAGE_EXECUTE_READWRITE, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}
	std::memcpy((void*)IsDebuggerPresentAPI, orgdata, sizeof(orgdata));
	if (!VirtualProtect((void*)IsDebuggerPresentAPI, sizeof(orgdata), POLD, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}

	if (!VirtualProtect((void*)GetTickCountAPI, sizeof(orgdata2), PAGE_EXECUTE_READWRITE, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}
	std::memcpy((void*)GetTickCountAPI, orgdata2, sizeof(orgdata2));
	if (!VirtualProtect((void*)GetTickCountAPI, sizeof(orgdata2), POLD, &POLD)) {
		MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
		ExitProcess(NULL);
	}
}

ULONG_PTR PatchAgain = 0;
void HookedD(PEXCEPTION_RECORD pExcptRec, PCONTEXT ContextRecord)
{
	// Declare some variables.
	DWORD ExcCode = 0;
	ULONG_PTR ipAddress = 0;
	DWORD OLDMP = 0;
	bool expectedAddress = false;
#ifdef _WIN64
	ipAddress = ContextRecord->Rip;
#else
	ipAddress = ContextRecord->Eip;
#endif

	if (pExcptRec->ExceptionCode == STATUS_BREAKPOINT)
	{
		// Check if our context instruction pointer is one address of those we hooked before. 
		if (ipAddress == (ULONG_PTR)IsDebuggerPresentAPI) {
			if (VirtualProtect((void*)ipAddress, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect)) {
				std::memcpy((void*)ipAddress, orgdata, sizeof(orgdata));
				expectedAddress = true;
			}
			else {
				MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
				ExitProcess(NULL);
			}
		}
		if (ipAddress == (ULONG_PTR)GetTickCountAPI) {
			if (VirtualProtect((void*)ipAddress, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect)) {
				std::memcpy((void*)ipAddress, orgdata2, sizeof(orgdata2));
				expectedAddress = true;
			}
			else {
				MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
				ExitProcess(NULL);
			}
		}
		if (!found && expectedAddress)
		{

			ULONG_PTR returnAddress = 0;
			ULONG_PTR returnAddress2 = 0;
			bool isstub = false;
#ifndef _WIN64
			std::memcpy(&returnAddress, (void*)ContextRecord->Esp, 4);
#else
			std::memcpy(&returnAddress, (void*)ContextRecord->Rsp, 8);
#endif 
			bool found = false;
			ULONG_PTR addrs = 0;
			SIZE_T RangeS = 0;

			/* Loop to check if the stack returning address is on the range of the allocated pages used by Steam stub, 
			that's why we hooked VirtualAlloc function before
			*/
			for (long long i = 0; i < data; i++) {
				addrs = (ULONG_PTR)StubBuf[i];
				for (SIZE_T b = 0; b < StubBufSize[i]; b++) {
					if (addrs == returnAddress) {
						found = true;
						RangeS = StubBufSize[i] - b;
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
				ULONG_PTR pattern1addr, pattern2addr, pattern3addr;
				DWORD POLD;
				SIZE_T i = 0;
				// Scan some patterns.
				for (;;)
				{
					if (i == RangeS)
						break;

					if (patternfound == 0)
					{
						SIZE_T b = RangeS - i;
						if (b >= sizeof(StubPattern1))
						{
							if (std::memcmp((void*)returnAddress, StubPattern1, sizeof(StubPattern1)) == 0)
							{
								SIZE_T bctp = RangeS - i + 2;
								if (bctp >= 1)
								{
									for (int b = 0; b < sizeof(operators); b++)
									{
										if (std::memcmp((void*)((ULONG_PTR)returnAddress + 2), &operators[b], 1) == 0)
										{
											patternfound = 1;
											pattern1addr = returnAddress;
											if (!VirtualProtect((void*)pattern1addr, sizeof(StubPatternPatch1), PAGE_EXECUTE_READWRITE, &POLD)) {
												MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
												ExitProcess(NULL);
											}
											std::memcpy((void*)pattern1addr, StubPatternPatch1, sizeof(StubPatternPatch1));
											if (!VirtualProtect((void*)pattern1addr, sizeof(StubPatternPatch1), POLD, &POLD)) {
												MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
												ExitProcess(NULL);
											}
											break;
										}
									}
								}
								else
									break;
							}
						}
						else
							break;
					}

					if (patternfound == 1)
					{
						SIZE_T b = RangeS - i;
						if (b >= 0x2)
						{
							if (std::memcmp((void*)returnAddress, StubPattern3, 0x2) == 0)
							{
								SIZE_T bc = RangeS - i + 3;
								if (bc >= 1)
								{
									if (std::memcmp((void*)((ULONG_PTR)returnAddress + 3), &StubPattern3[3], 1) == 0)
									{
										SIZE_T bct = RangeS - i + 4;
										if (bct >= 1)
										{
											for (int bt = 0; bt < sizeof(operators); bt++)
											{
												if (std::memcmp((void*)((ULONG_PTR)returnAddress + 4), &operators[bt], 1) == 0)
												{
													patternfound = 2;
													pattern3addr = returnAddress;
													if (!VirtualProtect((void*)pattern3addr, 0x4, PAGE_EXECUTE_READWRITE, &POLD)) {
														MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
														ExitProcess(NULL);
													}
													std::memset((void*)pattern3addr, 0x90, 0x4);
													if (!VirtualProtect((void*)pattern3addr, 0x4, POLD, &POLD)) {
														MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
														ExitProcess(NULL);
													}
													break;
												}
											}
										}
										else
											break;
									}
								}
								else
									break;
							}
							if (std::memcmp((void*)returnAddress, &StubPattern3[2], 0x2) == 0)
							{
								SIZE_T bctp = RangeS - i + 2;
								if (bctp >= 1)
								{
									for (int b = 0; b < sizeof(operators); b++)
									{
										if (std::memcmp((void*)((ULONG_PTR)returnAddress + 2), &operators[b], 1) == 0)
										{
											patternfound = 2;
											pattern3addr = returnAddress;
											if (!VirtualProtect((void*)pattern3addr, 0x2, PAGE_EXECUTE_READWRITE, &POLD)) {
												MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
												ExitProcess(NULL);
											}
											std::memset((void*)pattern3addr, 0x90, 0x2);
											if (!VirtualProtect((void*)pattern3addr, 0x2, POLD, &POLD)) {
												MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
												ExitProcess(NULL);
											}
											break;
										}
									}
								}
								else
									break;
							}
						}
						else
							break;
					}
					if (patternfound == 2)
					{
						SIZE_T bop = RangeS - i;
						if (bop >= sizeof(StubPattern2))
						{
							if (std::memcmp((void*)returnAddress, StubPattern2, sizeof(StubPattern2)) == 0)
							{
								SIZE_T bopt = RangeS - i + 5;
								if (bopt >= 1)
								{
									for (int b = 0; b < sizeof(operators); b++)
									{
										if (std::memcmp((void*)((ULONG_PTR)returnAddress + 5), &operators[b], 1) == 0)
										{
											patternfound = 3;
											pattern2addr = returnAddress;
											if (!VirtualProtect((void*)pattern2addr, sizeof(StubPatternPatch2), PAGE_EXECUTE_READWRITE, &POLD)) {
												MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
												ExitProcess(NULL);
											}
											std::memcpy((void*)pattern2addr, StubPatternPatch2, sizeof(StubPatternPatch2));
											if (!VirtualProtect((void*)pattern2addr, sizeof(StubPatternPatch2), POLD, &POLD)) {
												MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
												ExitProcess(NULL);
											}
											break;
										}
									}
								}
								else
									break;
							}
						}
						else
							break;
					}
					if (patternfound == 3)
						break;
					returnAddress++;
					i++;
				}
				if (patternfound == 3)
				{
					// Pattern were successfully patched, now restore the functions we hooked before.
					RestoreHooks();
					found++;
#ifdef _WIN64
					((VOID(*)(PCONTEXT, _EXCEPTION_RECORD*))CtxR)(ContextRecord, NULL);
#else
					((NTSTATUS(*)(PCONTEXT, BOOLEAN))CtxR)(ContextRecord, NULL);
#endif
				}
				else {
					RestoreHooks();
					Sleep(2000);
					MessageBoxA(NULL, "Unable to find the Steam stub variant expected patterns. Game will exit.", "Error", MB_ICONERROR);
					ExitProcess(NULL);
				}
			}
			ContextRecord->EFlags |= 0x100;
			SStepFlag = true;
		}
	}
	if (pExcptRec->ExceptionCode == STATUS_SINGLE_STEP)
	{
		if (SStepFlag)
		{
			SStepFlag = false;
			if (VirtualProtect((void*)PrecAddress, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect)) {
				std::memcpy((void*)PrecAddress, int3bp, sizeof(int3bp));
				PrecAddress = 0;
			}
			else {
				MessageBoxA(NULL, "Falied to patch SteamStub. Error: Falied to protect the requested memory range.", "Error", MB_ICONERROR);
				ExitProcess(NULL);
			}
		}
	}
	// Continue execution.
#ifdef _WIN64
	((VOID(*)(PCONTEXT, _EXCEPTION_RECORD*))CtxR)(ContextRecord, NULL);
#else
	((NTSTATUS(*)(PCONTEXT, BOOLEAN))CtxR)(ContextRecord, NULL);
#endif
}
extern "C" _declspec(dllexport) void handledExceptionFilter() //Handler
{
	CallDispatcherData(HookedD);
}
namespace SteamStubBypass
{
	bool PatchSteamStub(ULONG_PTR BindStart, ULONG_PTR BindEnd, ULONG_PTR entryexe)
	{
		// Get kernel and ntdll modules base addresses.
		hKernel = GetModuleHandleA("kernel32.dll"); // Hooks
		hNtdll = GetModuleHandleA("ntdll.dll");
		if (!hKernel)
			return false;
		if (!hNtdll)
			return false;

		// Get functions and wrappers pointers for redirections.
		IsDebuggerPresentAPI = GetProcAddress(hKernel, "IsDebuggerPresent");
		GetTickCountAPI = GetProcAddress(hKernel, "GetTickCount");
		KIUEDApi = GetProcAddress(hNtdll, "KiUserExceptionDispatcher");
#ifdef _WIN64
		CtxR = GetProcAddress(hNtdll, "RtlRestoreContext");
#else
		CtxR = GetProcAddress(hNtdll, "ZwContinue");
#endif

		__NtAllocateVirtualMemory = (_NtAllocateVirtualMemory)GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
		VirtualAllocAPI = GetProcAddress(hKernel, "VirtualAlloc");
		ULONG_PTR myWrapper = (ULONG_PTR)GetProcAddress(SteamApimod, "WVirtualAlloc");
		ULONG_PTR myWrapper2 = (ULONG_PTR)GetProcAddress(SteamApimod, "handledExceptionFilter");


		if (!IsDebuggerPresentAPI)
			return false;
		if (!GetTickCountAPI)
			return false;
		if (!__NtAllocateVirtualMemory)
			return false;
		if (!VirtualAllocAPI)
			return false;
		if(!KIUEDApi)
			return false;
		if (!CtxR)
			return false;

#ifdef _WIN64
		BYTE HookData[12] = { 0x48, 0xB8 };
		std::memcpy(&HookData[2], &myWrapper, 8);
		HookData[10] = 0xFF;
		HookData[11] = 0xE0;
#else
		BYTE HookData[6] = { 0x68 };
		std::memcpy(&HookData[1], &myWrapper, 4);
		HookData[5] = 0xC3;
#endif 
		// Start hooking procedure by changing memory protections at first.
		if (!VirtualProtect((void*)IsDebuggerPresentAPI, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;
		if (!VirtualProtect((void*)GetTickCountAPI, sizeof(int3bp), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;
		if (!VirtualProtect((void*)VirtualAllocAPI, sizeof(HookData), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;
		if (!VirtualProtect((void*)KIUEDApi, sizeof(HookData), PAGE_EXECUTE_READWRITE, &OldProtect))
			return false;

		// Save original bytes and hook, we are hooking IsDebuggerPresent and GetTickCount because are called closely in the range to where we need to patch to.
		std::memcpy(orgdata, (void*)IsDebuggerPresentAPI, sizeof(orgdata));
		std::memcpy((void*)IsDebuggerPresentAPI, int3bp, sizeof(int3bp));

		std::memcpy(orgdata2, (void*)GetTickCount, sizeof(orgdata2));
		std::memcpy((void*)GetTickCountAPI, int3bp, sizeof(int3bp));

		std::memcpy(VirtualAllocOrgData, (void*)VirtualAllocAPI, sizeof(VirtualAllocOrgData));
		std::memcpy((void*)VirtualAllocAPI, HookData, sizeof(HookData));

#ifdef _WIN64
		std::memcpy(&HookData[2], &myWrapper2, 8);
#else
		std::memcpy(&HookData[1], &myWrapper2, 4);
#endif
		std::memcpy(KIUEDOrgData, (void*)KIUEDApi, sizeof(KIUEDOrgData));
		std::memcpy((void*)KIUEDApi, HookData, sizeof(HookData));

		BindEndt = BindEnd;
		BindStrt = BindStart;
		return true;
	}
	void Patch()
	{
		// Get main module base address, assuming is our target.
		HMODULE hExe = GetModuleHandleA(NULL);

		// Get module header informations.
		auto DosHeader = (IMAGE_DOS_HEADER*)hExe;
		auto ntheader = (IMAGE_NT_HEADERS*)((ULONG_PTR)hExe + DosHeader->e_lfanew);
		auto psection = IMAGE_FIRST_SECTION(ntheader);

		// Check if .bind section is present as usually used by Steam stub.
		int stubdetected = 0;
		ULONG_PTR strt1, end1;
		for (int i = 0; i < ntheader->FileHeader.NumberOfSections; i++)
		{
			if (std::strcmp((char*)psection->Name, ".bind") == 0)
			{
				strt1 = (ULONG_PTR)hExe + psection->VirtualAddress;
				end1 = (ULONG_PTR)strt1 + psection->Misc.VirtualSize;
				stubdetected = 1;
				break;
			}
			psection++;
		}
		// Check if the main module entrypoint is into the .bind section range.
		ULONG_PTR entrypoint = (ULONG_PTR)hExe + ntheader->OptionalHeader.AddressOfEntryPoint;
		for (ULONG_PTR i = strt1; i < end1; i++) {
			if (entrypoint == i) {
				stubdetected = 2;
				break;
			}
		}
		if (stubdetected == 2) 
		{
#if (!_DEBUG)
			PatchSteamStub(strt1, end1, (ULONG_PTR)hExe + ntheader->OptionalHeader.AddressOfEntryPoint);
#else
			MessageBoxA(NULL, "Please compile this DLL in release mode to use SteamStub bypass feature. It might be unstable with debug mode!", "Error", MB_ICONWARNING);
			ExitProcess(NULL);
#endif
		}
	}
}