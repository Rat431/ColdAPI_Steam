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

#if !defined(CCALLBACK_H) && !defined(_S4N_)
#define CCALLBACK_H
#ifdef _WIN32
#pragma once
#endif 

#include "SteamTypes.h"

// Declares a callback member function plus a helper member variable which
// registers the callback on object creation and unregisters on destruction.
// The optional fourth 'var' param exists only for backwards-compatibility
// and can be ignored.
#define STEAM_CALLBACK( thisclass, func, .../*callback_type, [deprecated] var*/ ) \
	_STEAM_CALLBACK_SELECT( ( __VA_ARGS__, 4, 3 ), ( /**/, thisclass, func, __VA_ARGS__ ) )

// Declares a callback function and a named CCallbackManual variable which
// has Register and Unregister functions instead of automatic registration.
#define STEAM_CALLBACK_MANUAL( thisclass, func, callback_type, var )	\
	CCallbackManual< thisclass, callback_type > var; void func( callback_type *pParam )

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
// These macros are similar to the STEAM_CALLBACK_* macros in steam_api.h, but only trigger for gameserver callbacks
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
#define STEAM_GAMESERVER_CALLBACK( thisclass, func, /*callback_type, [deprecated] var*/... ) \
	_STEAM_CALLBACK_SELECT( ( __VA_ARGS__, GS, 3 ), ( this->SetGameserverFlag();, thisclass, func, __VA_ARGS__ ) )

#define STEAM_GAMESERVER_CALLBACK_MANUAL( thisclass, func, callback_type, var ) \
	CCallbackManual< thisclass, callback_type, true > var; void func( callback_type *pParam )



#define _STEAM_CALLBACK_GS( _, thisclass, func, param, var ) \
	CCallback< thisclass, param, true > var; void func( param *pParam )

//-----------------------------------------------------------------------------
// Purpose: base for callbacks and call results - internal implementation detail
//-----------------------------------------------------------------------------
class CCallbackBase
{
public:
	CCallbackBase() { m_nCallbackFlags = 0; m_iCallback = 0; }
	// don't add a virtual destructor because we export this binary interface across dll's
	virtual void Run( void *pvParam ) = 0;
	virtual void Run( void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall ) = 0;
	int GetICallback() { return m_iCallback; }
	virtual int GetCallbackSizeBytes() = 0;

protected:
	enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
	uint8 m_nCallbackFlags;
	int m_iCallback;
	friend class CCallbackMgr;

private:
	CCallbackBase( const CCallbackBase& );
	CCallbackBase& operator=( const CCallbackBase& );
};

//-----------------------------------------------------------------------------
// Purpose: templated base for callbacks - internal implementation detail
//-----------------------------------------------------------------------------
template< int sizeof_P >
class CCallbackImpl : protected CCallbackBase
{
public:
	~CCallbackImpl() { if ( m_nCallbackFlags & k_ECallbackFlagsRegistered ) SteamAPI_UnregisterCallback( this ); }
	void SetGameserverFlag() { m_nCallbackFlags |= k_ECallbackFlagsGameServer; }

protected:
	virtual void Run( void *pvParam ) = 0;
	virtual void Run( void *pvParam, bool /*bIOFailure*/, SteamAPICall_t /*hSteamAPICall*/ ) { Run( pvParam ); }
	virtual int GetCallbackSizeBytes() { return sizeof_P; }
};

//-----------------------------------------------------------------------------
// Purpose: maps a steam async call result to a class member function
//			template params: T = local class, P = parameter struct
//-----------------------------------------------------------------------------
template< class T, class P >
class CCallResult : private CCallbackBase
{
public:
	typedef void (T::*func_t)( P*, bool );

	CCallResult()
	{
		m_hAPICall = k_uAPICallInvalid;
		m_pObj = NULL;
		m_Func = NULL;
		m_iCallback = P::k_iCallback;
	}

	void Set( SteamAPICall_t hAPICall, T *p, func_t func )
	{
		if ( m_hAPICall )
			SteamAPI_UnregisterCallResult( this, m_hAPICall );

		m_hAPICall = hAPICall;
		m_pObj = p;
		m_Func = func;

		if ( hAPICall )
			SteamAPI_RegisterCallResult( this, hAPICall );
	}

	bool IsActive() const
	{
		return ( m_hAPICall != k_uAPICallInvalid );
	}

	void Cancel()
	{
		if ( m_hAPICall != k_uAPICallInvalid )
		{
			SteamAPI_UnregisterCallResult( this, m_hAPICall );
			m_hAPICall = k_uAPICallInvalid;
		}

	}

	~CCallResult()
	{
		Cancel();
	}

private:
	virtual void Run( void *pvParam )
	{
		m_hAPICall = k_uAPICallInvalid; // caller unregisters for us
		(m_pObj->*m_Func)( (P *)pvParam, false );		
	}
	virtual void Run( void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall )
	{
		if ( hSteamAPICall == m_hAPICall )
		{
			m_hAPICall = k_uAPICallInvalid; // caller unregisters for us
			(m_pObj->*m_Func)( (P *)pvParam, bIOFailure );			
		}
	}
	virtual int GetCallbackSizeBytes()
	{
		return sizeof( P );
	}

	SteamAPICall_t m_hAPICall;
	T *m_pObj;
	func_t m_Func;
};



//-----------------------------------------------------------------------------
// Purpose: maps a steam callback to a class member function
//			template params: T = local class, P = parameter struct,
//			bGameserver = listen for gameserver callbacks instead of client callbacks
//-----------------------------------------------------------------------------
template< class T, class P, bool bGameserver = false >
class CCallback : public CCallbackImpl< sizeof( P ) >
{
public:
	typedef void (T::*func_t)(P*);

	// NOTE: If you can't provide the correct parameters at construction time, you should
	// use the CCallbackManual callback object (STEAM_CALLBACK_MANUAL macro) instead.
	CCallback( T *pObj, func_t func ) : m_pObj( NULL ), m_Func( NULL )
	{
		if ( bGameserver )
		{
			this->SetGameserverFlag();
		}
		Register( pObj, func );
	}

	// manual registration of the callback
	void Register( T *pObj, func_t func )
	{
		if ( !pObj || !func )
			return;

		if ( this->m_nCallbackFlags & CCallbackBase::k_ECallbackFlagsRegistered )
			Unregister();

		m_pObj = pObj;
		m_Func = func;
		// SteamAPI_RegisterCallback sets k_ECallbackFlagsRegistered
		SteamAPI_RegisterCallback( this, P::k_iCallback );
	}

	void Unregister()
	{
		// SteamAPI_UnregisterCallback removes k_ECallbackFlagsRegistered
		SteamAPI_UnregisterCallback( this );
	}

protected:
	virtual void Run( void *pvParam )
	{
		(m_pObj->*m_Func)( (P *)pvParam );
	}

	T *m_pObj;
	func_t m_Func;
};


//-----------------------------------------------------------------------------
// Purpose: subclass of CCallback which allows default-construction in
//			an unregistered state; you must call Register manually
//-----------------------------------------------------------------------------
template< class T, class P, bool bGameServer = false >
class CCallbackManual : public CCallback< T, P, bGameServer >
{
public:
	CCallbackManual() : CCallback< T, P, bGameServer >( NULL, NULL ) {}

	// Inherits public Register and Unregister functions from base class
};


//-----------------------------------------------------------------------------
// The following macros are implementation details, not intended for public use
//-----------------------------------------------------------------------------
#define _STEAM_CALLBACK_AUTO_HOOK( thisclass, func, param )
#define _STEAM_CALLBACK_HELPER( _1, _2, SELECTED, ... )		_STEAM_CALLBACK_##SELECTED
#define _STEAM_CALLBACK_SELECT( X, Y )						_STEAM_CALLBACK_HELPER X Y
#define _STEAM_CALLBACK_3( extra_code, thisclass, func, param ) \
struct CCallbackInternal_ ## func : private CCallbackImpl< sizeof( param ) > { \
	CCallbackInternal_ ## func () { extra_code SteamAPI_RegisterCallback( this, param::k_iCallback ); } \
	CCallbackInternal_ ## func ( const CCallbackInternal_ ## func & ) { extra_code SteamAPI_RegisterCallback( this, param::k_iCallback ); } \
	CCallbackInternal_ ## func & operator=( const CCallbackInternal_ ## func & ) { return *this; } \
private: virtual void Run( void *pvParam ) { _STEAM_CALLBACK_AUTO_HOOK( thisclass, func, param ) \
	thisclass *pOuter = reinterpret_cast<thisclass*>( reinterpret_cast<char*>(this) - offsetof( thisclass, m_steamcallback_ ## func ) ); \
	pOuter->func( reinterpret_cast<param*>( pvParam ) ); \
} \
} m_steamcallback_ ## func ; void func( param *pParam )
#define _STEAM_CALLBACK_4( _, thisclass, func, param, var ) \
	CCallback< thisclass, param > var; void func( param *pParam )



#ifdef _MSC_VER
	// disable this warning; this pattern need for steam callback registration
	#pragma warning( disable: 4355 )	// 'this' : used in base member initializer list
#endif



#endif // CCALLBACK_H
