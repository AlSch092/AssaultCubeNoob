#include "Entity.hpp"

DWORD Entity::GetTimeOnScreen(DWORD EntityAddress)
{
	if (EntityAddress == 0)
		return 0;

	return DereferenceSafe<DWORD>(EntityAddress + Offsets::Entity::TimeOnScreen);
}

Vector3 Entity::GetHeadPosition(DWORD EntityAddress)
{
	if (EntityAddress == 0)
		return {};

	float x = DereferenceSafe<float>(EntityAddress + Offsets::Entity::HeadX);
	float y = DereferenceSafe<float>(EntityAddress + Offsets::Entity::HeadY);
	float z = DereferenceSafe<float>(EntityAddress + Offsets::Entity::HeadZ);

	return Vector3{ x,y,z };
}

Vector3 Entity::GetFootPosition(DWORD EntityAddress)
{
	if (EntityAddress == 0)
		return {};

	float x = DereferenceSafe<float>(EntityAddress + Offsets::Entity::FeetX);
	float y = DereferenceSafe<float>(EntityAddress + Offsets::Entity::FeetY);
	float z = DereferenceSafe<float>(EntityAddress +  Offsets::Entity::FeetZ);

	return Vector3{ x,y,z };
}

Vector2 Entity::GetAxisPosition(DWORD EntityAddress)
{
	if (EntityAddress == 0)
		return {};

	float x = DereferenceSafe<float>(EntityAddress + Offsets::Entity::AimAxisX);
	float y = DereferenceSafe<float>(EntityAddress + Offsets::Entity::AimAxisY);

	return Vector2{ x,y };
}

 
char* Entity::GetPlayerName(DWORD EntityAddress)
{
	if (EntityAddress == 0)
		return nullptr;

	UINT32 playerNameAddress = (UINT32)(EntityAddress + Offsets::Entity::PlayerName);

	char Name[15]{ 0 };
	strcpy_s(Name, (const char*)playerNameAddress);
	return Name;
}

unsigned int Entity::GetPlayerHealth(DWORD EntityAddress)
{
	return 0;
}

_Entity* Entity::GetLocalPlayer()
{
	DWORD GameBase = (DWORD)GetModuleHandleA("ac_client.exe");

	if (GameBase == NULL)
	{
		printf("[ERROR] Failed to find ac_client.exe!\n");
		return nullptr;
	}

	DWORD LocalPlayerAddr = DereferenceSafe<DWORD>(GameBase + Offsets::dwLocalPlayer);

	if (LocalPlayerAddr == NULL)
	{
		printf("[ERROR] Local Player was NULL!\n");
		return nullptr;
	}

	_Entity* LocalPlayer = new _Entity();
	LocalPlayer->MemoryAddress = LocalPlayerAddr;

	LocalPlayer->FootPosition = Entity::GetFootPosition(LocalPlayerAddr);
	LocalPlayer->HeadPosition = Entity::GetHeadPosition(LocalPlayerAddr);
	LocalPlayer->AxisPosition = Entity::GetAxisPosition(LocalPlayerAddr);

	//fill in rest...

	return LocalPlayer;
}

_Entity* Entity::GetEntity(DWORD EntityBaseAddress)
{
	if (EntityBaseAddress == NULL)
		return nullptr;

	if (DereferenceSafe<DWORD>(EntityBaseAddress) != Entity::ThisPtrSig) //thisptr was wrong, bad ent
		return nullptr;

	_Entity* Player = new _Entity();
	Player->MemoryAddress = EntityBaseAddress;

	Player->FootPosition = Entity::GetFootPosition(EntityBaseAddress);
	Player->HeadPosition = Entity::GetHeadPosition(EntityBaseAddress);
	Player->AxisPosition = Entity::GetAxisPosition(EntityBaseAddress);
	Player->TimeOnScreen = Entity::GetTimeOnScreen(EntityBaseAddress);

	//fill in rest...

	return Player;
}

bool Entity::IsEntOnScreen(_Entity* e) //not the best solution but I prefer finishing this project quickly
{
	DWORD currentTimeOnScreen = GetTimeOnScreen(e->MemoryAddress);

	Sleep(50);

	DWORD deltaTimeOnScreen = GetTimeOnScreen(e->MemoryAddress);

	if (deltaTimeOnScreen > currentTimeOnScreen)
		return true;
	else
		return false;
}

std::vector<_Entity*> Entity::GetList()
{
	std::vector<_Entity*> EntList;

	DWORD EntListAddr = (DWORD)GetModuleHandleA(AC_CLIENT);

	if (EntListAddr == NULL)
	{
		printf("[ERROR] Failed to find ac_client.exe at Entity::GetList!\n");
		return {};
	}

	EntListAddr = (*(DWORD*)(EntListAddr + Offsets::dwEntityList)) + sizeof(DWORD); 	//first 4 bytes is 00, skip over

	bool iterating = true;
	DWORD currentEntAddress = *(DWORD*)EntListAddr;
	int count = 0;

	while (iterating)
	{
		DWORD currentEntAddress = *(DWORD*)(EntListAddr + (count * sizeof(uint32_t)));

		_Entity* e = Entity::GetEntity(currentEntAddress); //the ent list is contiguous ptrs, so the case of a first bad pointer means the list is ended
		
		if (e == nullptr)
		{
			iterating = false;
			break;
		}
		else
		{
			EntList.push_back(e);
		}

		printf("Pushed back entity @ %x\n", currentEntAddress);
		count += 1;
	}

	return EntList;
}

bool Entity::WriteLocalPlayerAim(Vector2 axis)
{
	_Entity* LocalEnt = Entity::GetLocalPlayer();

	if (LocalEnt == nullptr)
		return false;

	printf("Writing aim axis: %f , %f\n", axis.x, axis.y);

	__try
	{
		*(float*)(LocalEnt->MemoryAddress + Offsets::Entity::AimAxisX) = axis.x;
		*(float*)(LocalEnt->MemoryAddress + Offsets::Entity::AimAxisY) = axis.y;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		delete LocalEnt;
		return false;
	}

	delete LocalEnt;
	return true;
}

int Entity::GetHitpoints(DWORD EntityAddress)
{
	if (EntityAddress == 0)
		return {};

	return 	DereferenceSafe<int>(EntityAddress + Offsets::Entity::Hitpoints);
}