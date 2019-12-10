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
#include "ColdManager.h"
#include "CSteamCallbacks.h"
#include <mutex>
#include <map>
#include <stdio.h>
#include <wchar.h>

#define EXPORTMYFUNC extern "C" __declspec(dllexport)			// Define structures and interface names : )

#define STEAMAPPID "steam_appid.txt"
#define EMPTY "Nothing"
#define STEAM_NOTINSTALLED "NoSteam"
#define INI "ColdAPI.ini"
#ifdef _WIN64
#define STEAMOVERLAY "gameoverlayrenderer64.dll"
#define STEAMCLIENT "steamclient64.dll"
#define STEAMCLIENTREG "SteamClientDll64"
#define STEAMAPI "steam_api64"
#define Steamregistry "Software\\Wow6432Node\\Valve\\Steam"
#define ORGAPI "steam_api64.org"
#else
#define STEAMOVERLAY "gameoverlayrenderer.dll"
#define STEAMCLIENT "steamclient.dll"
#define STEAMCLIENTREG "SteamClientDll"
#define STEAMAPI "steam_api"
#define Steamregistry "Software\\Valve\\Steam"
#define ORGAPI "steam_api.org"
#endif
#define INTERFACE_NOT_FOUND 10
#define SUCCES_LOADED 1


enum CSteamInterface
{
	STEAM_APPLIST,
	STEAM_APPS,
	STEAM_APPTICKET,
	STEAM_CLIENT,
	STEAM_CONTENTSERVER,
	STEAM_CONTROLLER,
	STEAM_FRIENDS,
	STEAM_PARENTALSETTINGS,
	STEAM_GAMECOORDINATOR,
	STEAM_GAMESERVER,
	STEAM_GAMESERVERSTATS,
	STEAM_MATCHMAKING,
	STEAM_MATCHMAKINGSERVERS,
	STEAM_MUSIC,
	STEAM_NETWORKING,
	STEAM_REMOTESTORAGE,
	STEAM_USER,
	STEAM_USERSTATS,
	STEAM_UTILS,
	STEAM_BILLING,
	STEAM_GAMESERVERHTTP,
	STEAM_GAMESERVERINVENTORY,
	STEAM_GAMESERVERNETWORKING,
	STEAM_GAMESERVERUGC,
	STEAM_GAMESERVERUTILS,
	STEAM_HTMLSURFACE,
	STEAM_HTTP,
	STEAM_INVENTORY,
	STEAM_MUSICREMOTE,
	STEAM_SCREENSHOTS,
	STEAM_UNIFIEDMESSAGES,
	STEAM_UGC,
	STEAM_VIDEO,
	STEAM_MASTERSERVERUPDATER,
	STEAM_GAMESEARCH,
	STEAM_INPUT,
	STEAM_PARTIES,
	STEAM_REMOTEPLAY
};




namespace Steam_Config // Steam configuration
{
	extern char Username[40];    
	extern uint32_t AppId;
	extern uint32_t AppBuildId;
	extern uint64_t UserID;

	extern char SaveDirectory[0x400];
	extern char UGCDirectotry[0x400];
	extern char Language[40];

	extern bool OnlineMod;
	extern bool UnlockAllDLCS;
	extern bool LowViolence;
	extern bool RemoteStorage;
	extern bool LoadOverLay;
	extern bool StubBypass;
	extern bool InterfaceNFound;

	extern bool ClientEmulation;
	extern bool HookForInjection;
}
struct InterfaceInfo
{
	CSteamInterface SteamType;
	int Version;
};
struct InterfaceData
{
	CSteamInterface SteamType;
	std::string key;
	std::string name;
	bool isstarted;
	int Version;
	InterfaceData(void* p = NULL, bool t = false) : datapointer(p), isstarted(t) {}
	void* datapointer;

};
struct SteamContext
{
	FARPROC InitContext;
	ULONG_PTR Flag;
	ULONG_PTR Out;
};
struct MyFileStream
{
	void* Buffer;
	size_t lastbuffersize;
	char* FileNameS;
};

// public vars
extern std::vector<std::string> FilesMatrix;
extern std::mutex PublicSafe;
extern HMODULE SteamApimod;
extern char Steamapipath[MAX_PATH];
extern char SteamModule[MAX_PATH];
extern unsigned char TicketData[128];
// Crazy? ;P Change it if you don't like. :)