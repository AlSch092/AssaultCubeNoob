//By AlSch092 @ github
#pragma once
#include <Windows.h>

template<class T>
T ReadPointer(UINT32 ulBase, int iOffset)
{
	__try
	{
		return *(T*)(*(UINT32*)ulBase + iOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return -1; }
}

template<class T>
bool WritePointer(UINT32 ulBase, UINT32 iOffset, T iValue)
{
	__try { *(T*)(*(UINT32*)ulBase + iOffset) = iValue; return true; }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

template<class T>
T DereferenceSafe(UINT32 ulAddress)
{
	__try
	{
		return *(T*)ulAddress;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return 0xDEADBEEF; }
}

template<class T>
T DereferenceSafeWithAddedOffset(UINT32 ulAddress, UINT32 Offset)
{
	__try
	{
		T val = *(T*)(ulAddress);
		return val;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return 0xDEADBEEF; }
}