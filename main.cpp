//By AlSch092 @ github
#include "Hacks.hpp"
#include <fstream>

extern BOOL Hacks::IsAimbotEnabled;

HANDLE aimbotThread = NULL;

void CheckHotkeys() 
{
	bool enabledHacks = false;

	while (true) 
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000) //control + f1 = enable
		{
			if (!Hacks::IsAimbotEnabled)
			{
				Hacks::IsAimbotEnabled = true;
				aimbotThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Hacks::DoAimbot, 0, 0, 0);
			}
			else
			{
				printf("Disabled aimbot");
				Hacks::IsAimbotEnabled = false;
				TerminateThread(aimbotThread, 0);
			}
		}
		else if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			if (enabledHacks)
			{
				printf("[INFO] Disabled no-recoil!\n");
				Hacks::InitializeHacks(false);
				enabledHacks = false;

			}
			else
			{
				printf("[INFO] Enabled no-recoil!\n");
				Hacks::InitializeHacks(true);
				enabledHacks = true;
			}
		}

		Sleep(100); // Sleep for a short duration to reduce CPU usage
	}
}

VOID Initialize()
{
	AllocConsole();
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CheckHotkeys, 0, 0, 0);
}

//no need to worry about detection, so we'll just make it a .dll instead of .exe
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) 
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, 0, 0, 0);
	}break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

