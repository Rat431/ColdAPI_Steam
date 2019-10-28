#pragma once
#include "../public SDK/ISteamAppTicket001.h"
#include "../Bridge.h"

class SteamAppTicketIn001 : public ISteamAppTicket001
{
public:
	uint32 GetAppOwnershipTicketData(AppId_t nAppId, void* pvSignedTicket, uint32 cbSignedTicket, uint32* piAppId, uint32* piSteamId, uint32* piSignature, uint32* pcbSignature)
	{
		if (nAppId == Steam_Config::AppId)
		{
			// Use small string signature
			const char* Signature = "Fake";
			int SLength = std::strlen(Signature) + 1;
			uint32_t FSize = sizeof(uint32_t) + sizeof(uint64_t) + SLength;

			// I would assume that the target/game would give enough buffer size for at least the AppId and UserID, so we decrease the Signature string length size. 
			while (FSize > cbSignedTicket) {
				SLength--;
				FSize = sizeof(uint32_t) + sizeof(uint64_t) + SLength;
			}
			if (pvSignedTicket != NULL && pvSignedTicket > NULL)
			{
				std::memcpy(pvSignedTicket, &Steam_Config::AppId, sizeof(uint32_t));
				std::memcpy((void*)((ULONG_PTR)pvSignedTicket + sizeof(uint32_t)), &Steam_Config::UserID, sizeof(uint64_t));
				std::memcpy((void*)((ULONG_PTR)pvSignedTicket + sizeof(uint32_t) + sizeof(uint64_t)), Signature, SLength);
			}
			if(piAppId != NULL && piAppId > NULL)
				*piAppId = 0;
			if(piSteamId != NULL && piSteamId > NULL)
				*piSteamId = sizeof(uint32_t);
			if(piSignature != NULL && piSignature > NULL)
				*piSignature = sizeof(uint32_t) + sizeof(uint64_t);
			if(pcbSignature != NULL && pcbSignature > NULL)
				*pcbSignature = SLength;
			return FSize;
		}
		return NULL;
	}
};