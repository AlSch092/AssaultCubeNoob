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

BYTE* SendData;
INT SendLength;
INT MainCmd;
INT SubCmd;
VOID __declspec(naked)SendHook()
{
	__asm
	{
		push eax
		mov eax, esi; length
		mov SendLength, eax
		mov eax, ecx
		mov SendData, eax
		pop eax

		mov eax, [esp+0x08]
		mov MainCmd, eax
		mov eax, [esp + 0x0C]
		mov SubCmd, eax

		push SubCmd
		push MainCmd
		push SendLength
		push SendData
		call CreatePacket
		add esp, 0x10

		mov eax, 0x0000C804
		jmp hkVillageSendPacket.dwReturn
	}
}
//Hack hooks
int MovespeedMultiplier = 5;
VOID __declspec(naked) MovespeedHook()
{
	__asm
	{
		pushfd
		imul eax, MovespeedMultiplier
		popfd
		mov[esp + 0x14], eax
		fild dword ptr[esp + 0x14]
		jmp hkSpeedHack.dwReturn
	}
}


VOID __declspec(naked) CPUReducerHook() {

	__asm
	{
		pushad
	}

	Sleep(50); //sleeps inside main thread to reduce cpu

	__asm
	{
		popad
			sub esp, 0x18
			push ebx
			push ebp
			jmp hkCPUReducer.dwReturn
	}
}