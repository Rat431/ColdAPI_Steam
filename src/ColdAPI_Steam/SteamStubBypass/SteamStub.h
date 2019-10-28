#pragma once
#include <Windows.h>
#include "../Bridge.h"
namespace SteamStubBypass
{
	bool PatchSteamStub(ULONG_PTR BindStart, ULONG_PTR BindEnd, ULONG_PTR entryexe);
	void Patch();
}
