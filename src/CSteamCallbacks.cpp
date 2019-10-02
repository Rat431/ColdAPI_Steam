#include "CSteamCallbacks.h"


namespace SteamCallback
{
	std::unordered_map<uint64_t, bool> _Calls;			// variables
	std::unordered_map<uint64_t, CCallbackBase*> ResultHandlersBuffers;
	std::vector<CSteamAPIResult_t> ResultsBuffer;
	std::vector<CCallbackBase*> CallbacksBuffer;
	int _CallID;
	std::mutex Thread;

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
		handler->SetICallback(callbackID);
		// Store in the vector
		CallbacksBuffer.push_back(handler);
	}
	void RegisterCallResult(CCallbackBase* result, uint64_t call)
	{
		// Store the callresult from its ID.
		ResultHandlersBuffers[call] = result;
	}
	void UnregisterCallback(CCallbackBase* handler, int callback)
	{
		auto iter = CallbacksBuffer.begin();

		// Loop untill we find the asked callback to remove based on the ID.
		while (iter != CallbacksBuffer.end())
		{
			CCallbackBase* handleriter = *iter;
			if (handleriter && handleriter->GetICallback() == callback)
			{
				CallbacksBuffer.erase(iter);
				break;
			}
			++iter;
		}		
	}
	void UnregisterCallResult(CCallbackBase* result, uint64_t call)
	{
		// Remove the callresult handler based on the ID.
		ResultHandlersBuffers.erase(call);
	}
	uint64_t RegisterCall(bool MarkActive)
	{
		// Return a new callresult id and set the status.
		++_CallID;
		_Calls[_CallID] = MarkActive;
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
}