// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include "Bridge.h"
#include "Steam_data.h"
unsigned char TicketData[128] = { 0 };
char Steamapipath[MAX_PATH] = { 0 };
char SteamModule[MAX_PATH] = { 0 };
HMODULE SteamApimod = 0;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		SteamApimod = hModule;
		char myfile[MAX_PATH] = { 0 };
		GetModuleFileNameA(hModule, myfile, MAX_PATH);
		int size = lstrlenA(myfile);
		for (int i = size; i > 0; i--) {
			if (myfile[i] == '\\') {
				lstrcpyA(SteamModule, &myfile[i + 1]);
				RtlFillMemory(&myfile[i + 1], size - i + 1, NULL);
				break;

			}
		}
		// Check if the steam_appid file or INI might be in the main module directory one
		char FileoNe[MAX_PATH] = { 0 };
		lstrcpyA(FileoNe, myfile);
		lstrcatA(FileoNe, "ColdAPI.ini");
		if (GetFileAttributesA(FileoNe) == INVALID_FILE_ATTRIBUTES) {
			lstrcpyA(FileoNe, myfile);
			lstrcatA(FileoNe, STEAMAPPID);
			if (GetFileAttributesA(FileoNe) == INVALID_FILE_ATTRIBUTES) {
				ZeroMemory(myfile, MAX_PATH);
				GetCurrentDirectoryA(MAX_PATH, myfile);
				lstrcatA(myfile, "\\");
			}
		}
		lstrcpyA(Steamapipath, myfile);
		ColdAPI_InitAndShutDown::ColdClientInitializzation();
	}
	return TRUE;
}

