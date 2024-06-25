//By AlSch092 @ github
#pragma once
#include "Entity.hpp"
#include <stdio.h>

struct HACK 
{
	UINT64 dwAddress;
	BYTE* szOriginalBytes;
	BYTE* szNewBytes;
	INT nSize;
};

namespace Hacks
{
	VOID WriteHackBytes(HACK hHack, BOOL bEnable);

	VOID InitializeHacks(bool bEnable);

	VOID DoAimbot();
	static BOOL IsAimbotEnabled = false;

	static BOOL IsNoRecoilEnabled = false;
}