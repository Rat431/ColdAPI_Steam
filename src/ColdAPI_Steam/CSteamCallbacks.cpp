#include "CSteamCallbacks.h"


namespace SteamCallback
{
	std::unordered_map<uint64_t, bool> _Calls;			// variables
	std::unordered_map<uint64_t, CCallbackBase*> ResultHandlersBuffers;
	std::vector<CSteamAPIResult_t> ResultsBuffer;
	std::vector<CCallbackBase*> CallbacksBuffer;
	int _CallID;
	std::mutex Thread;
	std::vector<CSteamAPIResult_t>::iterator CurrentCB;

	void RunCallbacks()
	{
		// Lock 
		Thread.lock();

		// Loop to our stored callresults.
		auto criter = ResultsBuffer.begin();
		while (criter != ResultsBuffer.end())
		{
			// Scan from the request callresult IDs and run its callback.
			auto ResultHws = ResultHandlersBuffers.find(criter->Call);
			if (ResultHws != ResultHandlersBuffers.end()) {
				// Run the callback if was marked active.
				if (_Calls[criter->Call] == true)
					ResultHandlersBuffers[criter->Call]->Run(criter->Data, false, criter->Call);
			}
			// Scan from the callback type.
			auto cbiter = CallbacksBuffer.begin();
			while (cbiter != CallbacksBuffer.end())
			{
				CCallbackBase* CallBack = *cbiter;
				if (CallBack && CallBack->GetICallback() == criter->Type)
					if (_Calls[criter->Call] == true)
						CallBack->Run(criter->Data);
				++cbiter;
			}
			++criter;
		}
		ResultsBuffer.clear();
		Thread.unlock();
	}
	void RegisterCallback(CCallbackBase* handler, int callbackID)
	{
		// Store the new callback ID.
		Thread.lock();
		handler->SetICallback(callbackID);
		// Store in the vector
		CallbacksBuffer.push_back(handler);
		Thread.unlock();
	}
	void RegisterCallResult(CCallbackBase* result, uint64_t call)
	{
		// Store the callresult from its ID.
		Thread.lock();
		ResultHandlersBuffers[call] = result;
		Thread.unlock();
	}
	void UnregisterCallback(CCallbackBase* handler, int callback)
	{
		Thread.lock();

		auto iter = CallbacksBuffer.begin();

		// Loop untill we find the asked callback to remove based on the callback itself.
		while (iter != CallbacksBuffer.end())
		{
			CCallbackBase* handleriter = *iter;
			if (handleriter && handleriter == handler)
			{
				CallbacksBuffer.erase(iter);
				break;
			}
			++iter;
		}		

		Thread.unlock();
	}
	void UnregisterCallResult(CCallbackBase* result, uint64_t call)
	{
		// Remove the callresult handler based on the ID.
		Thread.lock();
		ResultHandlersBuffers.erase(call);
		Thread.unlock();
	}
	uint64_t RegisterCall(bool MarkActive)
	{
		// Return a new callresult id and set the status.
		Thread.lock();
		++_CallID;
		_Calls[_CallID] = MarkActive;
		Thread.unlock();
		return _CallID;
	}
	void CreateNewRequest(void* data, int size, int type, uint64_t call)
	{
		Thread.lock();
		// Create a new Callresult request with its callback stored.
		CSteamAPIResult_t cres;
		cres.Call = call;
		cres.Type = type;
		cres.Size = size;
		cres.Data = data;

		// Save our filled "buffer" in our public vector
		ResultsBuffer.push_back(cres);
		Thread.unlock();
	}
	const char* GetCallbackName(int32_t ID)
	{
		// You can add the names of the callbacks for debugging, but I believe is a bit redundant.
		return "";
	}

	bool CCGetCallBack(void* pCallbackMsg)
	{
		// Assuming we want to Run only callresults as we're returning its callresult ID by the interfaces functions.
		Thread.lock();
		if (pCallbackMsg > NULL)
		{
			CurrentCB = ResultsBuffer.begin();

			if (CurrentCB != ResultsBuffer.end() && !ResultsBuffer.empty())
			{
				void* Buffer = nullptr;
				CCallbackMsg_t* CBM = (CCallbackMsg_t*)pCallbackMsg;
				if (Buffer == nullptr)
					Buffer = std::malloc(sizeof(CCSteamAPICallCompleted_t));
				// We return a random item from our callresult vector to run
				int randomCB = std::rand() % ResultsBuffer.size();
				std::advance(CurrentCB, randomCB);

				if (CurrentCB != ResultsBuffer.end() && randomCB <= ResultsBuffer.size())
				{
					CSteamAPIResult_t cresC = *CurrentCB;
					
					if (Buffer > nullptr) {
						CCSteamAPICallCompleted_t* cst = (CCSteamAPICallCompleted_t*)Buffer;
						cst->m_cubParam = cresC.Size;
						cst->m_hAsyncCall = cresC.Call;
						cst->m_iCallback = cresC.Type;
					}
					CBM->m_iCallback = 703;
					CBM->m_cubParam = cresC.Size;
					CBM->m_hSteamUser = 1;
					CBM->m_pubParam = (unsigned char*)Buffer;

					Thread.unlock();
					return true;
				}
			}
		}
		Thread.unlock();
		return false;
	}
	bool CCGetAPICallResult(uint64_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
	{
		Thread.lock();

		if (hSteamAPICall && pCallback > NULL)
		{
			// Loop to our stored callresults.
			auto criter = ResultsBuffer.begin();
			while (criter != ResultsBuffer.end())
			{
				CSteamAPIResult_t cresC = *criter;
				if (cresC.Call == hSteamAPICall && cresC.Type == iCallbackExpected && cresC.Size == cubCallback)
				{
					// Copy our callback data in the requested buffer
					std::memcpy(pCallback, cresC.Data, cresC.Size);
					if(pbFailed > NULL)
						*pbFailed = false;

					Thread.unlock();
					return true;
				}
				++criter;
			}
		}
		if (pbFailed > NULL)
			*pbFailed = true;

		Thread.unlock();
		return false;
	}
	void FreeCB()
	{
		Thread.lock();
		if(!ResultsBuffer.empty())
			ResultsBuffer.erase(CurrentCB);
		Thread.unlock();
	}
}