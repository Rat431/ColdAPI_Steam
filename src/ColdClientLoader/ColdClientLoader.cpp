// ColdClientLoader.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ColdClientLoader.h"

bool IsNotRelativePathOrRemoveFileName(CHAR* output, bool Remove)
{
	int LG = lstrlenA(output);
	for (int i = LG; i > 0; i--) {
		if (output[i] == '\\') {
			if(Remove)
				RtlFillMemory(&output[i], LG - i, NULL);
			return true;
		}
	}
	return false;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	CHAR CurrentDirectory[MAX_PATH] = { 0 };
	CHAR Client64Path[MAX_PATH] = { 0 };
	CHAR ClientPath[MAX_PATH] = { 0 };
	CHAR ExeFile[MAX_PATH] = { 0 };
	CHAR ExeCommandLine[300] = { 0 };
	bool InjectH = false;
	bool ClientInjection = false;

	STARTUPINFOA info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	int Length = GetModuleFileNameA(GetModuleHandleA(NULL), CurrentDirectory, sizeof(CurrentDirectory)) + 1;
	for (int i = Length; i > 0; i--) {
		if (CurrentDirectory[i] == '\\') {
			lstrcpyA(&CurrentDirectory[i + 1], "ColdAPI.ini");
			break;
		}
	}
	if (GetFileAttributesA(CurrentDirectory) == INVALID_FILE_ATTRIBUTES) {
		MessageBoxA(NULL, "Couldn't find the configuration file(ColdAPI.ini).", "ColdClientLoader", MB_ICONERROR);
		ExitProcess(NULL);
	}

	GetPrivateProfileStringA("SteamClient", "SteamClient64Dll", "", Client64Path, MAX_PATH, CurrentDirectory);
	GetPrivateProfileStringA("SteamClient", "SteamClientDll", "", ClientPath, MAX_PATH, CurrentDirectory);
	GetPrivateProfileStringA("SteamClient", "Exe", NULL, ExeFile, MAX_PATH, CurrentDirectory);
	GetPrivateProfileStringA("SteamClient", "ExeCommandLine", NULL, ExeCommandLine, 300, CurrentDirectory);

	CHAR TMP[MAX_PATH] = { 0 };
	if (!IsNotRelativePathOrRemoveFileName(Client64Path, false)) {
		ZeroMemory(TMP, sizeof(TMP));
		lstrcpyA(TMP, Client64Path);
		ZeroMemory(Client64Path, sizeof(Client64Path));
		GetFullPathNameA(TMP, MAX_PATH, Client64Path, NULL);
	}
	if (!IsNotRelativePathOrRemoveFileName(ClientPath, false)) {
		ZeroMemory(TMP, sizeof(TMP));
		lstrcpyA(TMP, ClientPath);
		ZeroMemory(ClientPath, sizeof(ClientPath));
		GetFullPathNameA(TMP, MAX_PATH, ClientPath, NULL);
	}
	if (!IsNotRelativePathOrRemoveFileName(ExeFile, false)) {
		ZeroMemory(TMP, sizeof(TMP));
		lstrcpyA(TMP, ExeFile);
		ZeroMemory(ExeFile, sizeof(ExeFile));
		GetFullPathNameA(TMP, MAX_PATH, ExeFile, NULL);
	}
#ifdef _WIN64
	if (GetFileAttributesA(Client64Path) == INVALID_FILE_ATTRIBUTES) {
		MessageBoxA(NULL, "Couldn't find the requested SteamClient64Dll.", "ColdClientLoader", MB_ICONERROR);
		ExitProcess(NULL);
	}
#else
	if (GetFileAttributesA(ClientPath) == INVALID_FILE_ATTRIBUTES) {
		MessageBoxA(NULL, "Couldn't find the requested SteamClientDll.", "ColdClientLoader", MB_ICONERROR);
		ExitProcess(NULL);
	}
#endif

	if (GetFileAttributesA(ExeFile) == INVALID_FILE_ATTRIBUTES) {
		MessageBoxA(NULL, "Couldn't find the requested Exe file.", "ColdClientLoader", MB_ICONERROR);
		ExitProcess(NULL);
	}

	if (GetPrivateProfileIntA("SteamAdditional", "ClientEmulation", FALSE, CurrentDirectory) == TRUE)
	{
		if (ExeFile[0] != NULL && CreateProcessA(ExeFile, ExeCommandLine, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &info, &processInfo))
		{
			if (GetPrivateProfileIntA("SteamClient", "InjectClient", TRUE, CurrentDirectory) == TRUE)
			{
				InjectH = GetPrivateProfileIntA("SteamClient", "HookInjectionMode", FALSE, CurrentDirectory) == TRUE;

				int LengthC = 0;
				CHAR* ClientString = 0;
				CHAR FileD[MAX_PATH] = { 0 };
				SIZE_T WRITTENB = 0;
				ClientInjection = true;
#ifdef _WIN64
				LengthC = lstrlenA(Client64Path);
				ClientString = Client64Path;
				lstrcpyA(FileD, Client64Path);
#else
				LengthC = lstrlenA(ClientPath);
				ClientString = ClientPath;
				lstrcpyA(FileD, ClientPath);
#endif
				LPVOID String = VirtualAllocEx(processInfo.hProcess, NULL, LengthC + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if (String != NULL)
				{
					// Set Dll search directory 
					HMODULE hKernel = GetModuleHandleA("kernel32.dll");
					if (hKernel)
					{
						FARPROC hDdllDir = GetProcAddress(hKernel, "SetDllDirectoryA");
						FARPROC hLoadLibrary = GetProcAddress(hKernel, "LoadLibraryA");
						if (hDdllDir && hLoadLibrary)
						{
							if (IsNotRelativePathOrRemoveFileName(FileD, true))
							{
								WriteProcessMemory(processInfo.hProcess, String, FileD, lstrlenA(FileD) + 1, &WRITTENB);
								HANDLE hThread1 = CreateRemoteThread(processInfo.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)hDdllDir, String, 0, NULL);
								WaitForSingleObject(hThread1, INFINITE);
							}
							WriteProcessMemory(processInfo.hProcess, String, ClientString, LengthC + 1, &WRITTENB);
							HANDLE hThread2 = CreateRemoteThread(processInfo.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)hLoadLibrary, String, 0, NULL);
							WaitForSingleObject(hThread2, INFINITE);
						}
						else
						{
							MessageBoxA(NULL, "Unable to get the kernel functions addresses for the injection.", "ColdClientLoader", MB_ICONERROR);
							TerminateProcess(processInfo.hProcess, NULL);
							ExitProcess(NULL);
						}
					}
					else
					{
						MessageBoxA(NULL, "Unable to get the kernel module for the injection.", "ColdClientLoader", MB_ICONERROR);
						TerminateProcess(processInfo.hProcess, NULL);
						ExitProcess(NULL);
					}
				}
				else
				{
					MessageBoxA(NULL, "Unable to allocate the injection buffer.", "ColdClientLoader", MB_ICONERROR);
					TerminateProcess(processInfo.hProcess, NULL);
					ExitProcess(NULL);
				}
			}
		}
		else
		{
			MessageBoxA(NULL, "Unable to load the requested EXE file.", "ColdClientLoader", MB_ICONERROR);
			ExitProcess(NULL);
		}
		HKEY Registrykey;
		// Declare some variables to be used for Steam registry.
		DWORD UserId = 0x03100004771F810C & 0xffffffff;
		DWORD ProcessID = GetCurrentProcessId();

		if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", 0, KEY_ALL_ACCESS, &Registrykey) != ERROR_SUCCESS)
		{
			if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", 0, 0, REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS, NULL, &Registrykey, NULL) != ERROR_SUCCESS)
			{
				MessageBoxA(NULL, "Unable to patch Steam process informations on the Windows registry.", "ColdClientLoader", MB_ICONERROR);
				TerminateProcess(processInfo.hProcess, NULL);
				ExitProcess(NULL);
			}
			else
			{

				// Set values to Windows registry.
				RegSetValueExA(Registrykey, "ActiveUser", NULL, REG_DWORD, (LPBYTE)& UserId, sizeof(DWORD));
				RegSetValueExA(Registrykey, "pid", NULL, REG_DWORD, (LPBYTE)& ProcessID, sizeof(DWORD));

				if (ClientInjection)
				{
					if (!InjectH)
					{
						// Before saving to the registry check again if the path was valid and if the file exist
						if (GetFileAttributesA(ClientPath) != INVALID_FILE_ATTRIBUTES) {
							RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)ClientPath, (DWORD)lstrlenA(ClientPath) + 1);
						}
						else {
							RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(ClientPath) + 1);
						}
						if (GetFileAttributesA(Client64Path) != INVALID_FILE_ATTRIBUTES) {
							RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)Client64Path, (DWORD)lstrlenA(Client64Path) + 1);
						}
						else {
							RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(Client64Path) + 1);
						}
					}
					else
					{
						// Identifiers for our LoadLibraries hooks from our client emulator.
						RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)"myclienthooked.dll", (DWORD)lstrlenA("myclienthooked.dll") + 1);
						RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)"myclienthooked64.dll", (DWORD)lstrlenA("myclienthooked64.dll") + 1);
					}
				}
				else
				{
					// Before saving to the registry check again if the path was valid and if the file exist
					if (GetFileAttributesA(ClientPath) != INVALID_FILE_ATTRIBUTES) {
						RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)ClientPath, (DWORD)lstrlenA(ClientPath) + 1);
					}
					else {
						RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(ClientPath) + 1);
					}
					if (GetFileAttributesA(Client64Path) != INVALID_FILE_ATTRIBUTES) {
						RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)Client64Path, (DWORD)lstrlenA(Client64Path) + 1);
					}
					else {
						RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(Client64Path) + 1);
					}
				}
				RegSetValueExA(Registrykey, "Universe", NULL, REG_SZ, (LPBYTE)"Public", (DWORD)lstrlenA("Public") + 1);

				// Close the HKEY Handle.
				RegCloseKey(Registrykey);

				ResumeThread(processInfo.hThread);
				WaitForSingleObject(processInfo.hThread, INFINITE);
				CloseHandle(processInfo.hProcess);
				CloseHandle(processInfo.hThread);
				ExitProcess(NULL);
			}
		}
		else
		{
			DWORD keyType = REG_SZ;
			CHAR OrgSteamCDir[MAX_PATH] = { 0 };
			CHAR OrgSteamCDir64[MAX_PATH] = { 0 };
			DWORD Size = MAX_PATH;

			// Get original values to restore later.
			RegQueryValueExA(Registrykey, "SteamClientDll", 0, &keyType, (LPBYTE)& OrgSteamCDir, &Size);
			RegQueryValueExA(Registrykey, "SteamClientDll64", 0, &keyType, (LPBYTE)& OrgSteamCDir64, &Size);

			// Set values to Windows registry.
			RegSetValueExA(Registrykey, "ActiveUser", NULL, REG_DWORD, (LPBYTE)& UserId, sizeof(DWORD));
			RegSetValueExA(Registrykey, "pid", NULL, REG_DWORD, (LPBYTE)& ProcessID, sizeof(DWORD));

			if (ClientInjection)
			{
				if (!InjectH)
				{
					// Before saving to the registry check again if the path was valid and if the file exist
					if (GetFileAttributesA(ClientPath) != INVALID_FILE_ATTRIBUTES) {
						RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)ClientPath, (DWORD)lstrlenA(ClientPath) + 1);
					}
					else {
						RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(ClientPath) + 1);
					}
					if (GetFileAttributesA(Client64Path) != INVALID_FILE_ATTRIBUTES) {
						RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)Client64Path, (DWORD)lstrlenA(Client64Path) + 1);
					}
					else {
						RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(Client64Path) + 1);
					}
				}
				else
				{
					// Identifiers for our LoadLibraries hooks from our client emulator.
					RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)"myclienthooked.dll", (DWORD)lstrlenA("myclienthooked.dll") + 1);
					RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)"myclienthooked64.dll", (DWORD)lstrlenA("myclienthooked64.dll") + 1);
				}
			}
			else
			{
				// Before saving to the registry check again if the path was valid and if the file exist
				if (GetFileAttributesA(ClientPath) != INVALID_FILE_ATTRIBUTES) {
					RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)ClientPath, (DWORD)lstrlenA(ClientPath) + 1);
				}
				else {
					RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(ClientPath) + 1);
				}
				if (GetFileAttributesA(Client64Path) != INVALID_FILE_ATTRIBUTES) {
					RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)Client64Path, (DWORD)lstrlenA(Client64Path) + 1);
				}
				else {
					RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)"", (DWORD)lstrlenA(Client64Path) + 1);
				}
			}
			RegSetValueExA(Registrykey, "Universe", NULL, REG_SZ, (LPBYTE)"Public", (DWORD)lstrlenA("Public") + 1);

			// Close the HKEY Handle.
			RegCloseKey(Registrykey);

			ResumeThread(processInfo.hThread);
			WaitForSingleObject(processInfo.hThread, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);

			if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", 0, KEY_ALL_ACCESS, &Registrykey) == ERROR_SUCCESS)
			{
				// Restore the values.
				RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)OrgSteamCDir, (DWORD)lstrlenA(OrgSteamCDir) + 1);
				RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)OrgSteamCDir64, (DWORD)lstrlenA(OrgSteamCDir64) + 1);

				// Close the HKEY Handle.
				RegCloseKey(Registrykey);
			}
			ExitProcess(NULL);
		}
	}
	else 
	{
		if (MessageBoxA(NULL, "ClientEmulation must be enabled to run this loader, do you want the loader enabling it for you?",
			"Configuration error", MB_ICONWARNING | MB_YESNOCANCEL) == IDYES) {
			if (WritePrivateProfileStringA("SteamAdditional", "ClientEmulation", "1", CurrentDirectory) == NULL) {
				MessageBoxA(NULL, "Falied to save the ClientEmulation mode configuration.", "Configuration error", MB_ICONERROR);
			}
		}
		ExitProcess(NULL);
	}
	return 1;
}
