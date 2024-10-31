#pragma once
#include "Offsets.hpp"

struct HOOK {
	DWORD dwAddress;
	DWORD dwReturn;
	char* szOriginalBytes;
	INT nSize;
};

VOID WriteHookBytes(HOOK hkHook, VOID* lpvHook, BOOL bEnable);