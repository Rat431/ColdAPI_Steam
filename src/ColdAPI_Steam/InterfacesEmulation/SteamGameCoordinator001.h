#pragma once
#include "../public SDK/ISteamGameCoordinator001.h"
#include "../Bridge.h"

class SteamGameCoordinatorIn001 : public ISteamGameCoordinator001
{
public:

	EGCResults SendMessage(uint32 unMsgType, const void* pubData, uint32 cubData)
	{
		return k_EGCResultOK;
	}

	bool IsMessageAvailable(uint32* pcubMsgSize)
	{
		return true;
	}

	EGCResults RetrieveMessage(uint32* punMsgType, void* pubDest, uint32 cubDest, uint32* pcubMsgSize)
	{
		return k_EGCResultOK;
	}

};