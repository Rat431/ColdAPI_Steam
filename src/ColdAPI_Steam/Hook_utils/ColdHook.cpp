#include "ColdHook.h"

namespace ColdHook_Vars
{
	bool Inited = false;
	int32_t CurrentID = 0;
	std::multimap<int32_t, Hook_Info*> RegisteredHooks;
}

namespace ColdHook_Service
{
	// Private functions:
	namespace
	{
		//  Disassembler call
		static unsigned int DisasmRange(SIZE_T* OutPutInstructionsSize, ULONG_PTR* OutNextInst, SIZE_T HookSize, _OffsetType BaseAddressFormat, int DVer, void* Buffer)
		{
			if (OutPutInstructionsSize > NULL && OutNextInst > NULL && BaseAddressFormat && Buffer > NULL)
			{
				// Declare some function variables
				_DecodeResult res;
				_DecodedInst decodedInstructions[0x1000]; // 1000 should be enough.
				unsigned int decodedInstructionsCount = 0;

				// Instructions size
				SIZE_T LSize = 0;

				// We disassemble 0x100 bytes
				if (ColdHook_Service::Is64BitProcess()) {
					res = distorm_decode(BaseAddressFormat, (unsigned char*)Buffer, 0x100, Decode64Bits, decodedInstructions, 0x1000, &decodedInstructionsCount);
				}
				else {
					res = distorm_decode(BaseAddressFormat, (unsigned char*)Buffer, 0x100, Decode32Bits, decodedInstructions, 0x1000, &decodedInstructionsCount);
				}
				for (unsigned int i = 0; i < decodedInstructionsCount; i++) {
					if (LSize >= HookSize) {
						// Store the next instruction address.
						*OutNextInst = decodedInstructions[i].offset;
						break;
					}
					LSize += decodedInstructions[i].size;
				}
				*OutPutInstructionsSize = LSize;
				return decodedInstructionsCount;
			}
			return NULL;
		}

		// Generate base address
		static void* AllocateTrampoline(ULONG_PTR StartBaseAddress, SIZE_T PageS, int32_t* OutErrorCode, SIZE_T* ChangedHookSize)
		{
			// Declare some function variables
			ULONG_PTR* StartingBaseAddress = NULL;
			SIZE_T AddressBytesCounter = NULL;
			void* ReturnAddress = NULL;
			SIZE_T Distance = NULL;
			bool IsBack = false;

			if (StartBaseAddress > NULL)
			{
				if (ColdHook_Service::Is64BitProcess())
				{
					StartingBaseAddress = (ULONG_PTR*)VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);

					if (StartingBaseAddress > NULL)
					{
						*StartingBaseAddress = StartBaseAddress;

						// Loop untill we find a right address 
						for (;;)
						{
							// We give a range of 40MB
							if (Distance > 0x41943040) {
								if (IsBack) {
									if (OutErrorCode > NULL) {
										*OutErrorCode = FALIED_OUT_RANGE;
									}
									// In that case we'll use another method to jump.
									*ChangedHookSize = 0xE;
									ReturnAddress = VirtualAlloc(NULL, PageS, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
									return ReturnAddress;
								}
								// We try searching before the module address
								Distance = NULL;
								*StartingBaseAddress = StartBaseAddress;
								IsBack = true;
							}
							if ((ReturnAddress = VirtualAlloc((void*)*StartingBaseAddress, PageS, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) != NULL)
								break;
							if (!IsBack)
								*StartingBaseAddress += 0x1000;
							else
								*StartingBaseAddress -= 0x1000;
							Distance += 0x1000;
						}
						if (OutErrorCode > NULL) {
							*OutErrorCode = NULL;
						}
						VirtualFree((void*)StartingBaseAddress, 0x1000, MEM_DECOMMIT);
						return ReturnAddress;
					}
					else
					{
						if (OutErrorCode > NULL) {
							*OutErrorCode = FALIED_ALLOCATION;
						}
					}
					return NULL;
				}
				else
				{
					if (OutErrorCode > NULL) {
						*OutErrorCode = WARN_32_BIT;
					}
					ReturnAddress = VirtualAlloc(NULL, PageS, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
					return ReturnAddress;
				}
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_INVALID_PARAMETER;
				}
			}
			return NULL;
		}

		// Arch
		static bool Is64BitProcess()
		{
#ifdef _WIN64
			return true;
#else
			return false;
#endif
		}

		// Custom 
		static bool IsAddressRegisteredAsHook(void* Address)
		{
			auto IterS = ColdHook_Vars::RegisteredHooks.begin();
			while (IterS != ColdHook_Vars::RegisteredHooks.end())
			{
				if (IterS->second->HFunction == Address) {
					return true;
				}
				IterS++;
			}
			return false;
		}
	}
	// Function wrap hooks
	int32_t InitFunctionHookByName(Hook_Info* OutputInfo, bool WrapFunction, bool CheckKBase , const char* ModulName, const char* FName, void* HookedF, int32_t* OutErrorCode)
	{
		if (OutputInfo > NULL && FName > NULL && HookedF > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				FARPROC RequestedFAddress = NULL;
				HMODULE RequestedM = NULL;

				ULONG_PTR TNextInstruction = NULL;
				SIZE_T TrampolineISize = NULL;
				SIZE_T MaxHSize = 5;
				DWORD OldP = NULL;
				int32_t Code = NULL;

				BYTE HookDataB[0x100] = { 0 };
				bool BytesStored = false;

				void* Redirection = NULL;
				void* JumpTo = NULL;

				// Read module
				RequestedM = GetModuleHandleA(ModulName);
				
				if (RequestedM > NULL)
				{
					// Get function pointer 
					RequestedFAddress = GetProcAddress(RequestedM, FName);

					// Latest windows uses mostly the kernel32 dll as a "bridge" to jump to the reals functions in the kernelbase module.
					if (ModulName > NULL) {
						if (CheckKBase && ColdHook_Service::Is64BitProcess()) {
							HMODULE hKernelBase = GetModuleHandleA("kernelbase.dll");
							HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
							FARPROC RequestedKbaseF = GetProcAddress(hKernelBase, FName);
							if (RequestedM == hKernel32) {
								if (hKernelBase > NULL && RequestedKbaseF > NULL) {
									// if the first 8 bytes are same, we continue using the requested module name
									if (std::memcmp((void*)RequestedFAddress, (void*)RequestedKbaseF, 8) != 0) {
										RequestedM = hKernelBase;
										RequestedFAddress = RequestedKbaseF;
									}
								}
							}
						}
					}

					if (RequestedFAddress > NULL)
					{
						if (!ColdHook_Service::IsAddressRegisteredAsHook((void*)RequestedFAddress))
						{
							SIZE_T ChangedHookSize = NULL;

							Redirection = ColdHook_Service::AllocateTrampoline((ULONG_PTR)RequestedM, 0x1000, &Code, &ChangedHookSize);
							if (ChangedHookSize != NULL) {
								MaxHSize = ChangedHookSize;
							}
							if (WrapFunction)
							{
								unsigned int DecodedI = ColdHook_Service::DisasmRange(&TrampolineISize, &TNextInstruction, MaxHSize, (ULONG_PTR)RequestedFAddress,
									distorm_version(), (void*)RequestedFAddress);
								if (Redirection > NULL)
								{
									if (DecodedI != NULL)
									{
										if (Code == NULL) // If 64 bit hook
										{
											// Install jump to our hooked function.
											*(BYTE*)Redirection = 0xFF;
											*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE)) = 0x25;
											std::memset((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));

											*(void**)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = HookedF;

											// Copy instructions that would be overwritten
											std::memcpy((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*)), (void*)RequestedFAddress, TrampolineISize);

											// Apply the return back jump
											*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize) = 0xFF;
											*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize + sizeof(BYTE)) = 0x25;
											std::memset((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));
											*(void**)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = (void*)TNextInstruction;

											JumpTo = Redirection;
											Redirection = (void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*));
										}
										else if (Code == FALIED_OUT_RANGE)
										{
											std::memcpy((void*)Redirection, (void*)RequestedFAddress, TrampolineISize);
											*((BYTE*)(ULONG_PTR)Redirection + TrampolineISize) = 0xFF;
											*((BYTE*)(ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE)) = 0x25;
											std::memset((void*)((ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));

											*(void**)((ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = (void*)TNextInstruction;
											JumpTo = HookedF;

											// Hook bytes
											HookDataB[0] = 0xFF;
											HookDataB[1] = 0x25;
											std::memset(&HookDataB[2], NULL, sizeof(DWORD));
											std::memcpy(&HookDataB[6], &JumpTo, sizeof(void*));
											BytesStored = true;
										}
										else if (Code == WARN_32_BIT)	// 32 bit
										{
											// Copy instructions that would be overwritten
											std::memcpy(Redirection, (void*)RequestedFAddress, TrampolineISize);

											// Apply the return back jump
											*((BYTE*)(ULONG_PTR)Redirection + TrampolineISize) = 0xE9;
											ULONG_PTR TempVar = (ULONG_PTR)Redirection + TrampolineISize;
											SIZE_T Jumpoffset = (ULONG_PTR)TNextInstruction - TempVar  - MaxHSize;
											std::memcpy((void*)((ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE)), &Jumpoffset, sizeof(DWORD));

											JumpTo = HookedF;
										}
										else
										{
											if (OutErrorCode > NULL) {
												*OutErrorCode = FALIED_ALLOCATION;
											}
											return NULL;
										}
									}
									else
									{
										if (OutErrorCode > NULL) {
											*OutErrorCode = FALIED_DISASSEMBLER;
										}
										return NULL;
									}
								}
								else
								{
									if (OutErrorCode > NULL) {
										*OutErrorCode = FALIED_ALLOCATION;
									}
									return NULL;
								}
							}
							else
							{
								if (Redirection > NULL)
								{
									if (Code == NULL) // If 64 bit hook
									{
										// Install jump to our hooked function.
										*(BYTE*)Redirection = 0xFF;
										*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE)) = 0x25;
										std::memset((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));

										*(void**)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = HookedF;

										JumpTo = Redirection;
										Redirection = (void*)RequestedFAddress;
									}
									else if (Code == WARN_32_BIT)
									{
										VirtualFree(Redirection, NULL, MEM_RELEASE);
										JumpTo = HookedF;
										Redirection = (void*)RequestedFAddress;
									}
									else if (Code == FALIED_OUT_RANGE)
									{
										JumpTo = HookedF;
										Redirection = (void*)RequestedFAddress;

										// Hook bytes
										HookDataB[0] = 0xFF;
										HookDataB[1] = 0x25;
										std::memset(&HookDataB[2], NULL, sizeof(DWORD));
										std::memcpy(&HookDataB[6], &JumpTo, sizeof(void*));
										BytesStored = true;
									}
									else
									{
										if (OutErrorCode > NULL) {
											*OutErrorCode = FALIED_ALLOCATION;
										}
										return NULL;
									}
								}
								else
								{
									if (OutErrorCode > NULL) {
										*OutErrorCode = FALIED_ALLOCATION;
									}
									return NULL;
								}
							}
							// Setup our hook
							if (VirtualProtect((void*)RequestedFAddress, MaxHSize, PAGE_EXECUTE_READWRITE, &OldP))
							{
								// Original bytes 
								OutputInfo->OrgData = VirtualAlloc(NULL, MaxHSize + 1, MEM_COMMIT, PAGE_READWRITE);
								OutputInfo->HookData = VirtualAlloc(NULL, MaxHSize + 1, MEM_COMMIT, PAGE_READWRITE);

								if (OutputInfo->OrgData > NULL && OutputInfo->HookData > NULL)
								{
									if (!BytesStored) {
										// Set hook bytes
										HookDataB[0] = 0xE9;
										SIZE_T Jumpoffset = (ULONG_PTR)JumpTo - (ULONG_PTR)RequestedFAddress - MaxHSize;
										std::memcpy(&HookDataB[1], &Jumpoffset, sizeof(DWORD));
									}
									std::memcpy(OutputInfo->OrgData, (void*)RequestedFAddress, MaxHSize);
									std::memcpy((void*)RequestedFAddress, HookDataB, MaxHSize);
									std::memcpy(OutputInfo->HookData, HookDataB, MaxHSize);

									VirtualProtect((void*)RequestedFAddress, MaxHSize, OldP, &OldP);

									if (ModulName > NULL)
										OutputInfo->ModuleName = ModulName;
									else
										OutputInfo->ModuleName = "";

									OutputInfo->FunctionName = FName;

									OutputInfo->HFunction = (void*)RequestedFAddress;
									OutputInfo->HookSize = MaxHSize;

									OutputInfo->OriginalF = Redirection;
									OutputInfo->TrampolinePage = JumpTo;

									OutputInfo->TrampolineSize = 0x1000;

									if (Code == WARN_32_BIT && WrapFunction != true)
										OutputInfo->Trampoline = false;
									else
										OutputInfo->Trampoline = true;

									OutputInfo->StatusHooked = true;

									if (OutErrorCode > NULL) {
										*OutErrorCode = NULL;
									}

									ColdHook_Vars::CurrentID++;
									return ColdHook_Vars::CurrentID;
								}
								else
								{
									if (OutErrorCode > NULL) {
										*OutErrorCode = FALIED_ALLOCATION;
									}
								}
							}
							else
							{
								if (OutErrorCode > NULL) {
									*OutErrorCode = FALIED_MEM_PROTECTION;
								}
							}
						}
						else
						{
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_ALREADY_EXISTS;
							}
						}
					}
					else
					{
						if (OutErrorCode > NULL) {
							*OutErrorCode = FALIED_FUNCTION_NOT_FOUND;
						}
					}
				}
				else
				{
					if (OutErrorCode > NULL) {
						*OutErrorCode = FALIED_MODULE_NOT_FOUND;
					}
				}
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return NULL;
	}
	int32_t InitFunctionHookByAddress(Hook_Info* OutputInfo, bool WrapFunction, void* Target, void* HookedF, int32_t* OutErrorCode)
	{
		if (OutputInfo > NULL && Target > NULL && HookedF > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				ULONG_PTR TNextInstruction = NULL;
				SIZE_T TrampolineISize = NULL;
				SIZE_T MaxHSize = 5;
				DWORD OldP = NULL;
				int32_t Code = NULL;

				BYTE HookDataB[0x100] = { 0 };
				bool BytesStored = false;

				void* Redirection = NULL;
				void* JumpTo = NULL;

				if (!ColdHook_Service::IsAddressRegisteredAsHook(Target))
				{
					SIZE_T ChangedHookSize = NULL;

					Redirection = ColdHook_Service::AllocateTrampoline((ULONG_PTR)Target, 0x1000, &Code, &ChangedHookSize);
					if (ChangedHookSize != NULL) {
						MaxHSize = ChangedHookSize;
					}
					if (WrapFunction)
					{
						unsigned int DecodedI = ColdHook_Service::DisasmRange(&TrampolineISize, &TNextInstruction, MaxHSize, (ULONG_PTR)Target,
							distorm_version(), Target);
						if (Redirection > NULL)
						{
							if (DecodedI != NULL)
							{
								if (Code == NULL) // If 64 bit hook
								{
									// Install jump to our hooked function.
									*(BYTE*)Redirection = 0xFF;
									*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE)) = 0x25;
									std::memset((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));

									*(void**)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = HookedF;

									// Copy instructions that would be overwritten
									std::memcpy((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*)), Target, TrampolineISize);

									// Apply the return back jump
									*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize) = 0xFF;
									*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize + sizeof(BYTE)) = 0x25;
									std::memset((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));
									*(void**)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*) + TrampolineISize + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = (void*)TNextInstruction;

									JumpTo = Redirection;
									Redirection = (void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD) + sizeof(void*));
								}
								else if (Code == FALIED_OUT_RANGE)
								{
									std::memcpy((void*)Redirection, Target, TrampolineISize);
									*((BYTE*)(ULONG_PTR)Redirection + TrampolineISize) = 0xFF;
									*((BYTE*)(ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE)) = 0x25;
									std::memset((void*)((ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));

									*(void**)((ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = (void*)TNextInstruction;
									JumpTo = HookedF;

									// Hook bytes
									HookDataB[0] = 0xFF;
									HookDataB[1] = 0x25;
									std::memset(&HookDataB[2], NULL, sizeof(DWORD));
									std::memcpy(&HookDataB[6], &JumpTo, sizeof(void*));
									BytesStored = true;
								}
								else if (Code == WARN_32_BIT)	// 32 bit
								{
									// Copy instructions that would be overwritten
									std::memcpy(Redirection, Target, TrampolineISize);

									// Apply the return back jump
									*((BYTE*)(ULONG_PTR)Redirection + TrampolineISize) = 0xE9;
									ULONG_PTR TempVar = (ULONG_PTR)Redirection + TrampolineISize;
									SIZE_T Jumpoffset = (ULONG_PTR)TNextInstruction - TempVar - MaxHSize;
									std::memcpy((void*)((ULONG_PTR)Redirection + TrampolineISize + sizeof(BYTE)), &Jumpoffset, sizeof(DWORD));

									JumpTo = HookedF;
								}
								else
								{
									if (OutErrorCode > NULL) {
										*OutErrorCode = FALIED_ALLOCATION;
									}
									return NULL;
								}
							}
							else
							{
								if (OutErrorCode > NULL) {
									*OutErrorCode = FALIED_DISASSEMBLER;
								}
								return NULL;
							}
						}
						else
						{
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_ALLOCATION;
							}
							return NULL;
						}
					}
					else
					{
						if (Redirection > NULL)
						{
							if (Code == NULL) // If 64 bit hook
							{
								// Install jump to our hooked function.
								*(BYTE*)Redirection = 0xFF;
								*((BYTE*)(ULONG_PTR)Redirection + sizeof(BYTE)) = 0x25;
								std::memset((void*)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE)), NULL, sizeof(DWORD));

								*(void**)((ULONG_PTR)Redirection + sizeof(BYTE) + sizeof(BYTE) + sizeof(DWORD)) = HookedF;

								JumpTo = Redirection;
								Redirection = Target;
							}
							else if (Code == FALIED_OUT_RANGE)
							{
								JumpTo = HookedF;
								Redirection = Target;

								// Hook bytes
								HookDataB[0] = 0xFF;
								HookDataB[1] = 0x25;
								std::memset(&HookDataB[2], NULL, sizeof(DWORD));
								std::memcpy(&HookDataB[6], &JumpTo, sizeof(void*));
								BytesStored = true;
							}
							else if (Code == WARN_32_BIT) // 32 bit
							{
								VirtualFree(Redirection, NULL, MEM_RELEASE);
								JumpTo = HookedF;
								Redirection = Target;
							}
							else
							{
								if (OutErrorCode > NULL) {
									*OutErrorCode = FALIED_ALLOCATION;
								}
								return NULL;
							}
						}
						else
						{
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_ALLOCATION;
							}
							return NULL;
						}
					}
					// Setup our hook
					if (VirtualProtect(Target, MaxHSize, PAGE_EXECUTE_READWRITE, &OldP))
					{
						// Original bytes 
						OutputInfo->OrgData = VirtualAlloc(NULL, MaxHSize + 1, MEM_COMMIT, PAGE_READWRITE);
						OutputInfo->HookData = VirtualAlloc(NULL, MaxHSize + 1, MEM_COMMIT, PAGE_READWRITE);

						if (OutputInfo->OrgData > NULL && OutputInfo->HookData > NULL)
						{
							std::memcpy(OutputInfo->OrgData, Target, MaxHSize);

							if (!BytesStored) {
								// Set hook bytes
								HookDataB[0] = 0xE9;								
								SIZE_T Jumpoffset = (ULONG_PTR)JumpTo - (ULONG_PTR)Target - MaxHSize;
								std::memcpy(&HookDataB[1], &Jumpoffset, sizeof(DWORD));
							}
							std::memcpy(OutputInfo->OrgData, Target, MaxHSize);
							std::memcpy(Target, HookDataB, MaxHSize);
							std::memcpy(OutputInfo->HookData, HookDataB, MaxHSize);
							
							VirtualProtect(Target, MaxHSize, OldP, &OldP);

							OutputInfo->FunctionName = "";
							OutputInfo->ModuleName = "";

							OutputInfo->HFunction = Target;
							OutputInfo->HookSize = MaxHSize;

							OutputInfo->OriginalF = Redirection;
							OutputInfo->TrampolinePage = JumpTo;

							OutputInfo->TrampolineSize = 0x1000;

							if (Code == WARN_32_BIT && WrapFunction != true)
								OutputInfo->Trampoline = false;
							else
								OutputInfo->Trampoline = true;

							OutputInfo->StatusHooked = true;

							if (OutErrorCode > NULL) {
								*OutErrorCode = NULL;
							}

							ColdHook_Vars::CurrentID++;
							return ColdHook_Vars::CurrentID;
						}
						else
						{
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_ALLOCATION;
							}
						}
					}
					else
					{
						if (OutErrorCode > NULL) {
							*OutErrorCode = FALIED_MEM_PROTECTION;
						}
					}
				}
				else
				{
					if (OutErrorCode > NULL) {
						*OutErrorCode = FALIED_ALREADY_EXISTS;
					}
				}
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return NULL;
	}


	// Memory custom hook
	int32_t InitHookCustomData(Hook_Info* OutputInfo, void* Target, void* CustomData, size_t CSize, int32_t* OutErrorCode)
	{
		if (OutputInfo > NULL && Target > NULL && CustomData > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				if (!ColdHook_Service::IsAddressRegisteredAsHook(Target))
				{
					DWORD OldP = NULL;
					if (VirtualProtect(Target, CSize, PAGE_EXECUTE_READWRITE, &OldP))
					{
						OutputInfo->OrgData = VirtualAlloc(NULL, CSize + 1, MEM_COMMIT, PAGE_READWRITE);
						OutputInfo->HookData = VirtualAlloc(NULL, CSize + 1, MEM_COMMIT, PAGE_READWRITE);

						if (OutputInfo->OrgData > NULL && OutputInfo->HookData > NULL)
						{
							std::memcpy(OutputInfo->OrgData, Target, CSize);
							std::memcpy(OutputInfo->HookData, CustomData, CSize);

							std::memcpy(Target, CustomData, CSize);
							VirtualProtect(Target, CSize, OldP, &OldP);

							OutputInfo->FunctionName = "";
							OutputInfo->ModuleName = "";

							OutputInfo->HFunction = Target;
							OutputInfo->HookSize = CSize;

							OutputInfo->OriginalF = NULL;
							OutputInfo->TrampolinePage = NULL;
							OutputInfo->TrampolineSize = NULL;

							OutputInfo->Trampoline = false;
							OutputInfo->StatusHooked = true;

							if (OutErrorCode > NULL) {
								*OutErrorCode = NULL;
							}

							ColdHook_Vars::CurrentID++;
							return ColdHook_Vars::CurrentID;
						}
						else
						{
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_ALLOCATION;
							}
						}
					}
					else
					{
						if (OutErrorCode > NULL) {
							*OutErrorCode = FALIED_MEM_PROTECTION;
						}
					}
				}
				else 
				{
					if (OutErrorCode > NULL) {
						*OutErrorCode = FALIED_ALREADY_EXISTS;
					}
				}
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return NULL;
	}

	// UnHook
	bool UnHookRegisteredData(int32_t HookID, int32_t* OutErrorCode)
	{
		if (HookID > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				DWORD OldP = NULL;
				auto IterS = ColdHook_Vars::RegisteredHooks.begin();
				while (IterS != ColdHook_Vars::RegisteredHooks.end())
				{
					if (IterS->first == HookID) {
						if (IterS->second->StatusHooked) {
							if (VirtualProtect(IterS->second->HFunction, IterS->second->HookSize, PAGE_EXECUTE_READWRITE, &OldP)) {
								std::memcpy(IterS->second->HFunction, IterS->second->OrgData, IterS->second->HookSize);
								VirtualProtect(IterS->second->HFunction, IterS->second->HookSize, OldP, &OldP);
								IterS->second->StatusHooked = false;
								if (OutErrorCode > NULL) {
									*OutErrorCode = NULL;
								}
								return true;
							}
							else {
								if (OutErrorCode > NULL) {
									*OutErrorCode = FALIED_UNHOOK;
								}
								return false;
							}
						}
						else {
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_NOT_HOOKED;
							}
							return false;
						}
					}
					IterS++;
				}
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_HOOK_NOT_EXISTS;
				}
				return false;
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return false;
	}
	bool HookAgainRegisteredData(int32_t HookID, int32_t* OutErrorCode)
	{
		if (HookID > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				DWORD OldP = NULL;
				auto IterS = ColdHook_Vars::RegisteredHooks.begin();
				while (IterS != ColdHook_Vars::RegisteredHooks.end())
				{
					if (IterS->first == HookID) {
						if (!IterS->second->StatusHooked) {
							if (VirtualProtect(IterS->second->HFunction, IterS->second->HookSize, PAGE_EXECUTE_READWRITE, &OldP)) {
								std::memcpy(IterS->second->HFunction, IterS->second->HookData, IterS->second->HookSize);
								VirtualProtect(IterS->second->HFunction, IterS->second->HookSize, OldP, &OldP);
								IterS->second->StatusHooked = true;
								if (OutErrorCode > NULL) {
									*OutErrorCode = NULL;
								}
								return true;
							}
							else {
								if (OutErrorCode > NULL) {
									*OutErrorCode = FALIED_HOOK;
								}
								return false;
							}
						}
						else {
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_ALREADY_EXISTS;
							}
							return false;
						}
					}
					IterS++;
				}
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_HOOK_NOT_EXISTS;
				}
				return false;
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return false;
	}

	// Init And shut down
	bool ServiceGlobalInit(int32_t* OutErrorCode)
	{
		if (!ColdHook_Vars::Inited)
		{
			if (!ColdHook_Vars::RegisteredHooks.empty()) {
				ColdHook_Vars::RegisteredHooks.clear();
			}
			if (OutErrorCode > NULL) {
				*OutErrorCode = NULL;
			}
			ColdHook_Vars::Inited = true;
			ColdHook_Vars::CurrentID = NULL;
			return true;
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_ALREADY_INITIALIZED;
			}
		}
		return false;
	}
	bool ServiceGlobalShutDown(int32_t* OutErrorCode)
	{
		if (ColdHook_Vars::Inited)
		{
			DWORD OldP = NULL;
			int32_t ErrorC = NULL;
			auto IterS = ColdHook_Vars::RegisteredHooks.begin();
			while (IterS != ColdHook_Vars::RegisteredHooks.end())
			{
				if (IterS->second->StatusHooked)
				{
					if (VirtualProtect(IterS->second->HFunction, IterS->second->HookSize, PAGE_EXECUTE_READWRITE, &OldP))
					{
						std::memcpy(IterS->second->HFunction, IterS->second->OrgData, IterS->second->HookSize);
						VirtualProtect(IterS->second->HFunction, IterS->second->HookSize, OldP, &OldP);
						if (!VirtualFree(IterS->second->OrgData, IterS->second->HookSize + 1, MEM_DECOMMIT)) {
							ErrorC = FALIED_FREE_MEMORY;
							if (OutErrorCode > NULL) {
								*OutErrorCode = ErrorC;
							}
							return false;
						}
						if (!VirtualFree(IterS->second->HookData, IterS->second->HookSize + 1, MEM_DECOMMIT)) {
							ErrorC = FALIED_FREE_MEMORY;
							if (OutErrorCode > NULL) {
								*OutErrorCode = ErrorC;
							}
							return false;
						}

						if (IterS->second->Trampoline)
						{
							if (!VirtualFree(IterS->second->TrampolinePage, NULL, MEM_RELEASE)) {
								ErrorC = FALIED_FREE_MEMORY;
								if (OutErrorCode > NULL) {
									*OutErrorCode = ErrorC;
								}
								return false;
							}
						}
					}
					else {
						ErrorC = FALIED_UNHOOK;
						if (OutErrorCode > NULL) {
							*OutErrorCode = ErrorC;
						}
						return false;
					}
				}
				else 
				{
					if (IterS->second->Trampoline)
					{
						if (!VirtualFree(IterS->second->TrampolinePage, NULL, MEM_RELEASE)) {
							ErrorC = FALIED_FREE_MEMORY;
						}
					}
				}
				ColdHook_Vars::RegisteredHooks.erase(IterS);
				IterS++;
			}
			if (OutErrorCode > NULL) {
				*OutErrorCode = ErrorC;
			}
			ColdHook_Vars::Inited = false;
			ColdHook_Vars::CurrentID = NULL;
			return true;
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
			}
		}
		return false;
	}

	// Informations
	bool RetrieveHookInfoByID(Hook_Info* OutputInfo, int32_t HookID, int32_t* OutErrorCode)
	{
		if (OutputInfo > NULL && HookID > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				auto IterS = ColdHook_Vars::RegisteredHooks.begin();
				while (IterS != ColdHook_Vars::RegisteredHooks.end())
				{
					if (IterS->first == HookID) {
						std::memcpy(OutputInfo, IterS->second, sizeof(Hook_Info));
						if (OutErrorCode > NULL) {
							*OutErrorCode = NULL;
						}
						return true;
					}
					IterS++;
				}
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_HOOK_NOT_EXISTS;
				}
				return false;
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return false;
	}
	bool RetrieveHookIDByInfo(Hook_Info* InputInfo, int32_t* OutHookID, int32_t* OutErrorCode)
	{
		if (InputInfo > NULL && OutHookID > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				auto IterS = ColdHook_Vars::RegisteredHooks.begin();
				while (IterS != ColdHook_Vars::RegisteredHooks.end())
				{
					if (std::memcmp(InputInfo, IterS->second, sizeof(Hook_Info)) == 0) {
						*OutHookID = IterS->first;
						if (OutErrorCode > NULL) {
							*OutErrorCode = NULL;
						}
						return true;
					}
					IterS++;
				}
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_HOOK_NOT_EXISTS;
				}
				return false;
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return false;
	}

	bool ServiceRegisterHookInformation(Hook_Info* InputInfo, int32_t HookID, int32_t* OutErrorCode)
	{
		if (InputInfo > NULL && HookID > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				// Check if is already registered
				auto IterS = ColdHook_Vars::RegisteredHooks.begin();
				while (IterS != ColdHook_Vars::RegisteredHooks.end())
				{
					if (IterS->first == HookID) {
						if (OutErrorCode > NULL) {
							*OutErrorCode = FALIED_ALREADY_EXISTS;
						}
						return false;
					}
					if (std::memcmp(InputInfo, IterS->second, sizeof(Hook_Info)) == 0) {
						if (OutErrorCode > NULL) {
							*OutErrorCode = FALIED_ALREADY_EXISTS;
						}
						return false;
					}
					IterS++;
				}
				ColdHook_Vars::RegisteredHooks.insert(std::make_pair(HookID, InputInfo));
				if (OutErrorCode > NULL) {
					*OutErrorCode = NULL;
				}
				return true;
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return false;
	}
	bool ServiceUnRegisterHookInformation(int32_t HookID, int32_t* OutErrorCode)
	{
		if (HookID > NULL)
		{
			if (ColdHook_Vars::Inited)
			{
				// Check if is registered
				auto IterS = ColdHook_Vars::RegisteredHooks.begin();
				while (IterS != ColdHook_Vars::RegisteredHooks.end())
				{
					if (IterS->first == HookID) {
						if (!IterS->second->StatusHooked) {
							ColdHook_Vars::RegisteredHooks.erase(IterS);
							if (OutErrorCode > NULL) {
								*OutErrorCode = NULL;
							}
							return true;
						}
						else {
							if (OutErrorCode > NULL) {
								*OutErrorCode = FALIED_NOT_ALLOWED;
							}
							return false;
						}
					}
					IterS++;
				}
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NOT_EXISTS;
				}
				return false;
			}
			else
			{
				if (OutErrorCode > NULL) {
					*OutErrorCode = FALIED_NEEDS_INITIALIZATION;
				}
			}
		}
		else
		{
			if (OutErrorCode > NULL) {
				*OutErrorCode = FALIED_INVALID_PARAMETER;
			}
		}
		return false;
	}
}