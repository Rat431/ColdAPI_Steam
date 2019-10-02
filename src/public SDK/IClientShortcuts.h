//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef ICLIENTSHORTCUTS_H
#define ICLIENTSHORTCUTS_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"

#define CLIENTSHORTCUTS_INTERFACE_VERSION "CLIENTSHORTCUTS_INTERFACE_VERSION001"

abstract_class UNSAFE_INTERFACE IClientShortcuts
{
public:
	virtual uint32 GetUniqueLocalAppId() = 0;
	virtual CGameID GetGameIDForAppID( AppId_t unAppID ) = 0;
	virtual uint32 GetAppIDForGameID( CGameID gameID ) = 0;
	virtual uint32 GetShortcutCount() = 0;
	virtual uint32 GetShortcutAppIDByIndex( uint32 uIndex ) = 0;
	virtual const char * GetShortcutAppNameByIndex( uint32 uIndex ) = 0;
	virtual const char * GetShortcutExeByIndex( uint32 uIndex ) = 0;
	virtual uint32 GetShortcutUserTagCountByIndex( uint32 uIndex ) = 0;
	virtual const char * GetShortcutUserTagByIndex( uint32 uIndex, uint32 ) = 0;
	virtual bool BIsShortcutRemoteByIndex( uint32 uIndex ) = 0;
	virtual const char * GetShortcutAppNameByAppID( AppId_t unAppID ) = 0;
	virtual const char * GetShortcutExeByAppID( AppId_t unAppID ) = 0;
	virtual const char * GetShortcutStartDirByAppID( AppId_t unAppID ) = 0;
	virtual const char * GetShortcutIconByAppID( AppId_t unAppID ) = 0;
	virtual uint32 GetShortcutUserTagCountByAppID( AppId_t unAppID ) = 0;
	virtual const char * GetShortcutUserTagByAppID( AppId_t unAppID, uint32 ) = 0;
	virtual bool BIsShortcutRemoteByAppID( AppId_t unAppID ) = 0;
	virtual uint32 AddShortcut( const char *, const char *, const char * ) = 0;
	virtual void SetShortcutFromFullpath( uint32, const char * ) = 0;
	virtual void SetShortcutAppName( uint32, const char * ) = 0;
	virtual void SetShortcutExe( uint32, const char * ) = 0;
	virtual void SetShortcutStartDir( uint32, const char * ) = 0;
	virtual void SetShortcutIcon( uint32, const char * ) = 0;
	virtual void ClearShortcutUserTags( uint32 ) = 0;
	virtual void AddShortcutUserTag( uint32, const char * ) = 0;
	virtual void RemoveShortcut( uint32 ) = 0;
	virtual bool LaunchShortcut( uint32 ) = 0;
};

#endif // ICLIENTSHORTCUTS_H
