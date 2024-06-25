#pragma once
#include "Offsets.hpp"

struct HOOK {
	DWORD dwAddress;
	DWORD dwReturn;
	char* szOriginalBytes;
	INT nSize;
};

VOID WriteHookBytes(HOOK hkHook, VOID* lpvHook, BOOL bEnable);

// ---Game hooks for hacking---
CONST HOOK hkSpeedHack = { dwSpeedHack, dwSpeedHack + 8, "\x89\x44\x24\x14\xDB\x44\x24\x14", 8 };
VOID MovespeedHook();

CONST HOOK hkCPUReducer = { dwCPUReducer, dwCPUReducer + 5, "\x83\xEC\x18\x53\x55", 5 };
VOID CPUReducerHook();

CONST HOOK hkVillageSendPacket = { dwSendVillagePacket, dwSendVillagePacket + 5, "\xE8\x91\x38\x00\x00", 5 };
VOID SendHook();