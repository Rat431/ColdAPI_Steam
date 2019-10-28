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

#ifndef HTMLSURFACECOMMON_H
#define HTMLSURFACECOMMON_H
#ifdef _WIN32
#pragma once
#endif


#define STEAMHTMLSURFACE_INTERFACE_VERSION_002 "STEAMHTMLSURFACE_INTERFACE_VERSION_002"
#define STEAMHTMLSURFACE_INTERFACE_VERSION_003 "STEAMHTMLSURFACE_INTERFACE_VERSION_003"
#define STEAMHTMLSURFACE_INTERFACE_VERSION_004 "STEAMHTMLSURFACE_INTERFACE_VERSION_004"
#define STEAMHTMLSURFACE_INTERFACE_VERSION_005 "STEAMHTMLSURFACE_INTERFACE_VERSION_005"

typedef uint32 HHTMLBrowser;
const uint32 INVALID_HTMLBROWSER = 0;


enum EHTMLMouseButton
{
	eHTMLMouseButton_Left = 0,
	eHTMLMouseButton_Right = 1,
	eHTMLMouseButton_Middle = 2,
};

enum EMouseCursor
{
	dc_user = 0,
	dc_none,
	dc_arrow,
	dc_ibeam,
	dc_hourglass,
	dc_waitarrow,
	dc_crosshair,
	dc_up,
	dc_sizenw,
	dc_sizese,
	dc_sizene,
	dc_sizesw,
	dc_sizew,
	dc_sizee,
	dc_sizen,
	dc_sizes,
	dc_sizewe,
	dc_sizens,
	dc_sizeall,
	dc_no,
	dc_hand,
	dc_blank, // don't show any custom cursor, just use your default
	dc_middle_pan,
	dc_north_pan,
	dc_north_east_pan,
	dc_east_pan,
	dc_south_east_pan,
	dc_south_pan,
	dc_south_west_pan,
	dc_west_pan,
	dc_north_west_pan,
	dc_alias,
	dc_cell,
	dc_colresize,
	dc_copycur,
	dc_verticaltext,
	dc_rowresize,
	dc_zoomin,
	dc_zoomout,
	dc_help,
	dc_custom,

	dc_last, // custom cursors start from this value and up
};

enum EHTMLKeyModifiers
{
	k_eHTMLKeyModifier_None = 0,
	k_eHTMLKeyModifier_AltDown = 1 << 0,
	k_eHTMLKeyModifier_CrtlDown = 1 << 1,
	k_eHTMLKeyModifier_ShiftDown = 1 << 2,
};


// callbacks
#pragma pack( push, 8 )


//-----------------------------------------------------------------------------
// Purpose: The browser is ready for use
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_BrowserReady_t, k_iSteamHTMLSurfaceCallbacks + 1 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // this browser is now fully created and ready to navigate to pages
END_DEFINE_CALLBACK_1()


//-----------------------------------------------------------------------------
// Purpose: the browser has a pending paint
//-----------------------------------------------------------------------------
DEFINE_CALLBACK(HTML_NeedsPaint_t, k_iSteamHTMLSurfaceCallbacks + 2)
CALLBACK_MEMBER(0, HHTMLBrowser, unBrowserHandle) // the browser that needs the paint
CALLBACK_MEMBER(1, const char *, pBGRA ) // a pointer to the B8G8R8A8 data for this surface, valid until SteamAPI_RunCallbacks is next called
CALLBACK_MEMBER(2, uint32, unWide) // the total width of the pBGRA texture
CALLBACK_MEMBER(3, uint32, unTall) // the total height of the pBGRA texture
CALLBACK_MEMBER(4, uint32, unUpdateX) // the offset in X for the damage rect for this update
CALLBACK_MEMBER(5, uint32, unUpdateY) // the offset in Y for the damage rect for this update
CALLBACK_MEMBER(6, uint32, unUpdateWide) // the width of the damage rect for this update
CALLBACK_MEMBER(7, uint32, unUpdateTall) // the height of the damage rect for this update
CALLBACK_MEMBER(8, uint32, unScrollX) // the page scroll the browser was at when this texture was rendered
CALLBACK_MEMBER(9, uint32, unScrollY) // the page scroll the browser was at when this texture was rendered
CALLBACK_MEMBER(10, float, flPageScale) // the page scale factor on this page when rendered
CALLBACK_MEMBER(11, uint32, unPageSerial) // incremented on each new page load, you can use this to reject draws while navigating to new pages
END_DEFINE_CALLBACK_12()


//-----------------------------------------------------------------------------
// Purpose: The browser wanted to navigate to a new page
//   NOTE - you MUST call AllowStartRequest in response to this callback
//-----------------------------------------------------------------------------
DEFINE_CALLBACK(HTML_StartRequest_t, k_iSteamHTMLSurfaceCallbacks + 3)
CALLBACK_MEMBER(0, HHTMLBrowser, unBrowserHandle) // the handle of the surface navigating
CALLBACK_MEMBER(1, const char *, pchURL) // the url they wish to navigate to 
CALLBACK_MEMBER(2, const char *, pchTarget) // the html link target type  (i.e _blank, _self, _parent, _top )
CALLBACK_MEMBER(3, const char *, pchPostData ) // any posted data for the request
CALLBACK_MEMBER(4, bool, bIsRedirect) // true if this was a http/html redirect from the last load request
END_DEFINE_CALLBACK_5()


//-----------------------------------------------------------------------------
// Purpose: The browser has been requested to close due to user interaction (usually from a javascript window.close() call)
//-----------------------------------------------------------------------------
DEFINE_CALLBACK(HTML_CloseBrowser_t, k_iSteamHTMLSurfaceCallbacks + 4)
CALLBACK_MEMBER(0, HHTMLBrowser, unBrowserHandle) // the handle of the surface 
END_DEFINE_CALLBACK_1()


//-----------------------------------------------------------------------------
// Purpose: the browser is navigating to a new url
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_URLChanged_t, k_iSteamHTMLSurfaceCallbacks + 5 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface navigating
CALLBACK_MEMBER( 1, const char *, pchURL ) // the url they wish to navigate to 
CALLBACK_MEMBER( 2, const char *, pchPostData ) // any posted data for the request
CALLBACK_MEMBER( 3, bool, bIsRedirect ) // true if this was a http/html redirect from the last load request
CALLBACK_MEMBER( 4, const char *, pchPageTitle ) // the title of the page
CALLBACK_MEMBER( 5, bool, bNewNavigation ) // true if this was from a fresh tab and not a click on an existing page
END_DEFINE_CALLBACK_6()


//-----------------------------------------------------------------------------
// Purpose: A page is finished loading
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_FinishedRequest_t, k_iSteamHTMLSurfaceCallbacks + 6 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchURL ) // 
CALLBACK_MEMBER( 2, const char *, pchPageTitle ) // 
END_DEFINE_CALLBACK_3()


//-----------------------------------------------------------------------------
// Purpose: a request to load this url in a new tab
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_OpenLinkInNewTab_t, k_iSteamHTMLSurfaceCallbacks + 7 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchURL ) // 
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: the page has a new title now
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_ChangedTitle_t, k_iSteamHTMLSurfaceCallbacks + 8 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchTitle ) // 
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: results from a search
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_SearchResults_t, k_iSteamHTMLSurfaceCallbacks + 9 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, uint32, unResults ) // 
CALLBACK_MEMBER( 2, uint32, unCurrentMatch ) // 
END_DEFINE_CALLBACK_3()


//-----------------------------------------------------------------------------
// Purpose: page history status changed on the ability to go backwards and forward
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_CanGoBackAndForward_t, k_iSteamHTMLSurfaceCallbacks + 10 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, bool, bCanGoBack ) // 
CALLBACK_MEMBER( 2, bool, bCanGoForward ) // 
END_DEFINE_CALLBACK_3()


//-----------------------------------------------------------------------------
// Purpose: details on the visibility and size of the horizontal scrollbar
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_HorizontalScroll_t, k_iSteamHTMLSurfaceCallbacks + 11 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, uint32, unScrollMax ) // 
CALLBACK_MEMBER( 2, uint32, unScrollCurrent ) // 
CALLBACK_MEMBER( 3, float, flPageScale ) // 
CALLBACK_MEMBER( 4, bool , bVisible ) // 
CALLBACK_MEMBER( 5, uint32, unPageSize ) // 
END_DEFINE_CALLBACK_6()


//-----------------------------------------------------------------------------
// Purpose: details on the visibility and size of the vertical scrollbar
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_VerticalScroll_t, k_iSteamHTMLSurfaceCallbacks + 12 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, uint32, unScrollMax ) // 
CALLBACK_MEMBER( 2, uint32, unScrollCurrent ) // 
CALLBACK_MEMBER( 3, float, flPageScale ) // 
CALLBACK_MEMBER( 4, bool, bVisible ) // 
CALLBACK_MEMBER( 5, uint32, unPageSize ) // 
END_DEFINE_CALLBACK_6()


//-----------------------------------------------------------------------------
// Purpose: response to GetLinkAtPosition call 
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_LinkAtPosition_t, k_iSteamHTMLSurfaceCallbacks + 13 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, uint32, x ) // NOTE - Not currently set
CALLBACK_MEMBER( 2, uint32, y ) // NOTE - Not currently set
CALLBACK_MEMBER( 3, const char *, pchURL ) // 
CALLBACK_MEMBER( 4, bool, bInput ) // 
CALLBACK_MEMBER( 5, bool, bLiveLink ) // 
END_DEFINE_CALLBACK_6()



//-----------------------------------------------------------------------------
// Purpose: show a Javascript alert dialog, call JSDialogResponse 
//   when the user dismisses this dialog (or right away to ignore it)
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_JSAlert_t, k_iSteamHTMLSurfaceCallbacks + 14 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchMessage ) // 
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: show a Javascript confirmation dialog, call JSDialogResponse 
//   when the user dismisses this dialog (or right away to ignore it)
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_JSConfirm_t, k_iSteamHTMLSurfaceCallbacks + 15 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchMessage ) // 
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: when received show a file open dialog
//   then call FileLoadDialogResponse with the file(s) the user selected.
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_FileOpenDialog_t, k_iSteamHTMLSurfaceCallbacks + 16 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchTitle ) // 
CALLBACK_MEMBER( 2, const char *, pchInitialFile ) // 
END_DEFINE_CALLBACK_3()


//-----------------------------------------------------------------------------
// Purpose: a popup item (i.e combo box) on the page needs rendering
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_ComboNeedsPaint_t, k_iSteamHTMLSurfaceCallbacks + 17 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pBGRA ) // a pointer to the B8G8R8A8 data for this surface, valid until SteamAPI_RunCallbacks is next called
CALLBACK_MEMBER( 2, uint32, unWide ) // the total width of the pBGRA texture
CALLBACK_MEMBER( 3, uint32, unTall ) // the total height of the pBGRA texture
END_DEFINE_CALLBACK_4()


//-----------------------------------------------------------------------------
// Purpose: a popup (i.e combo box) wants to display
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_ShowPopup_t, k_iSteamHTMLSurfaceCallbacks + 18 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
END_DEFINE_CALLBACK_1()


//-----------------------------------------------------------------------------
// Purpose: a popup (i.e combo box) wants to hide
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_HidePopup_t, k_iSteamHTMLSurfaceCallbacks + 19 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
END_DEFINE_CALLBACK_1()


//-----------------------------------------------------------------------------
// Purpose: a popup (i.e combo box) wants to hide
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_SizePopup_t, k_iSteamHTMLSurfaceCallbacks + 20 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, uint32, unX ) // the x pos into the page to display the popup
CALLBACK_MEMBER( 2, uint32, unY ) // the y pos into the page to display the popup
CALLBACK_MEMBER( 3, uint32, unWide ) // the total width of the pBGRA texture
CALLBACK_MEMBER( 4, uint32, unTall ) // the total height of the pBGRA texture
END_DEFINE_CALLBACK_5()


//-----------------------------------------------------------------------------
// Purpose: a new html window has been created 
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_NewWindow_t, k_iSteamHTMLSurfaceCallbacks + 21 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the current surface 
CALLBACK_MEMBER( 1, const char *, pchURL ) // the page to load
CALLBACK_MEMBER( 2, uint32, unX ) // the x pos into the page to display the popup
CALLBACK_MEMBER( 3, uint32, unY ) // the y pos into the page to display the popup
CALLBACK_MEMBER( 4, uint32, unWide ) // the total width of the pBGRA texture
CALLBACK_MEMBER( 5, uint32, unTall ) // the total height of the pBGRA texture
CALLBACK_MEMBER( 6, HHTMLBrowser, unNewWindow_BrowserHandle ) // the handle of the new window surface 
END_DEFINE_CALLBACK_7()


//-----------------------------------------------------------------------------
// Purpose: change the cursor to display
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_SetCursor_t, k_iSteamHTMLSurfaceCallbacks + 22 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, uint32, eMouseCursor ) // the EMouseCursor to display
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: informational message from the browser
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_StatusText_t, k_iSteamHTMLSurfaceCallbacks + 23 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchMsg ) // the EMouseCursor to display
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: show a tooltip
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_ShowToolTip_t, k_iSteamHTMLSurfaceCallbacks + 24 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchMsg ) // the EMouseCursor to display
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: update the text of an existing tooltip
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_UpdateToolTip_t, k_iSteamHTMLSurfaceCallbacks + 25 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
CALLBACK_MEMBER( 1, const char *, pchMsg ) // the EMouseCursor to display
END_DEFINE_CALLBACK_2()


//-----------------------------------------------------------------------------
// Purpose: hide the tooltip you are showing
//-----------------------------------------------------------------------------
DEFINE_CALLBACK( HTML_HideToolTip_t, k_iSteamHTMLSurfaceCallbacks + 26 )
CALLBACK_MEMBER( 0, HHTMLBrowser, unBrowserHandle ) // the handle of the surface 
END_DEFINE_CALLBACK_1()


#pragma pack( pop )

#endif // HTMLSURFACECOMMON_H
