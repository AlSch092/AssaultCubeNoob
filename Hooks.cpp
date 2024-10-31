#include "Hooks.hpp"
#include "Pointer.hpp"
#include "Packets.hpp"

VOID WriteHookBytes(HOOK hkHook, VOID* lpvHook, BOOL bEnable) {
	if (bEnable) {
		DWORD dwOldProt;
		VirtualProtect((void*)hkHook.dwAddress, (DWORD)hkHook.dwReturn - (DWORD)hkHook.dwAddress, PAGE_EXECUTE_READWRITE, &dwOldProt);
		*(UCHAR *)hkHook.dwAddress = 0xE9;
		*(UINT*)(hkHook.dwAddress + 1) = (DWORD)lpvHook - hkHook.dwAddress - 5;
		for (int i = 0; i < hkHook.nSize - 5; i++) {
			memcpy((VOID*)(hkHook.dwAddress + i + 5), (VOID*) "\x90", 1);
		}
	}
	else {
		memcpy((VOID*)hkHook.dwAddress, (VOID*)hkHook.szOriginalBytes, hkHook.nSize);
	}
}