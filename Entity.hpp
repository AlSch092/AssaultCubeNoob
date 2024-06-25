#pragma once
#include "Constants.hpp"
#include "Pointer.hpp"
#include "Game.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

typedef struct _Entity
{
	DWORD MemoryAddress;

	Vector3 HeadPosition;
	Vector3 FootPosition;

	Vector2 AxisPosition;

	DWORD Health;

	DWORD TimeOnScreen;

	char PlayerName[15];
};

namespace Entity
{
	static const DWORD ThisPtrSig = 0x0054D07C;

	int GetHitpoints(DWORD EntityAddress);

	DWORD GetTimeOnScreen(DWORD EntityAddress);
	Vector3 GetHeadPosition(DWORD EntityAddress);
	Vector3 GetFootPosition(DWORD EntityAddress);
	Vector2 GetAxisPosition(DWORD EntityAddress);

	char* GetPlayerName(DWORD EntityAddress);
	unsigned int GetPlayerHealth(DWORD EntityAddress);

	_Entity* GetLocalPlayer();
	_Entity* GetEntity(DWORD EntityBaseAddress);

	bool IsEntOnScreen(_Entity* e);

	vector<_Entity*> GetList();

	bool WriteLocalPlayerAim(Vector2 axis);
}