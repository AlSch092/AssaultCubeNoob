//By AlSch092 @ github
#include "Hacks.hpp"

VOID Hacks::WriteHackBytes(HACK hHack, BOOL bEnable) 
{
	if (bEnable) 
	{
		DWORD dwOldProt;
		VirtualProtect((void*)hHack.dwAddress, hHack.nSize, PAGE_EXECUTE_READWRITE, &dwOldProt);
		memcpy((void*)hHack.dwAddress, (void*)hHack.szNewBytes, hHack.nSize);
	}
	else 
	{
		memcpy((void*)hHack.dwAddress, (void*)hHack.szOriginalBytes, hHack.nSize);
	}
}

VOID Hacks::InitializeHacks(bool bEnable)
{
	DWORD GameBase = (DWORD)GetModuleHandleA(AC_CLIENT);

	if (GameBase == NULL)
	{
		printf("[ERROR] Failed to find ac_client.exe!\n");
		return;
	}

	HACK hNoAimRecoil = { GameBase + Offsets::Hacks::dwNoAimRecoil, (BYTE*)"\xF3\x0F\x11\x56\x38", (BYTE*)"\x90\x90\x90\x90\x90", 5 };

	if(bEnable)
		Hacks::WriteHackBytes(hNoAimRecoil, TRUE);
	else
		Hacks::WriteHackBytes(hNoAimRecoil, FALSE);

}

VOID Hacks::DoAimbot()
{
	bool aimbotting = true;

	printf("Starting aimbot...\n");

	while (aimbotting)
	{
		vector<_Entity*> EntityList = Entity::GetList();

		for (_Entity* e : EntityList)
		{
			while (Entity::IsEntOnScreen(e) && Entity::GetHitpoints(e->MemoryAddress) > 0) //also need to check ammo + entity team, will add these later
			{
				_Entity* LocalPlayer = Entity::GetLocalPlayer();
				Vector3 local_current_pos = Entity::GetHeadPosition(LocalPlayer->MemoryAddress);
				Vector3 target_current_pos = Entity::GetHeadPosition(e->MemoryAddress);

				Vector2 aimPos = Game::GetAimPositionOfEntity(local_current_pos, target_current_pos); //get 2d aiming position from 3d location differences
				Entity::WriteLocalPlayerAim(aimPos);

				delete LocalPlayer;
			}
		}
	}
}