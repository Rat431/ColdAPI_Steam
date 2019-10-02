// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include "Bridge.h"
#include "Steam_data.h"
unsigned char TicketData[128] = { 0 };
char Steamapipath[MAX_PATH] = { 0 };
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
				RtlFillMemory(&myfile[i + 1], size - i + 1, NULL);
				break;

			}
		}
		lstrcpyA(Steamapipath, myfile);
		SteamAPI_Init();
	}

	return TRUE;
}

