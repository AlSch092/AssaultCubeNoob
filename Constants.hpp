//By AlSch092 @ github
#pragma once
#include <windows.h>

#define AC_CLIENT "ac_client.exe"

namespace Offsets
{
    static const DWORD dwEntityList = 0x18AC04;
    static const DWORD dwLocalPlayer = 0x17E0A8;

    static const DWORD dwGameSpeed = 0x191F38;

    namespace Entity //entity struct offsets
    {
        static const DWORD ThisPtr = 0x00;

        static const DWORD HeadX = 0x04;
        static const DWORD HeadY = 0x08;
        static const DWORD HeadZ = 0x0C;

        static const DWORD FeetX = 0x28;
        static const DWORD FeetY = 0x2C;
        static const DWORD FeetZ = 0x30;

        static const DWORD AimAxisX = 0x34; //for local player
        static const DWORD AimAxisY = 0x38;
        static const DWORD ViewRotation = 0x3C;

        static const BYTE Team; //todo: find this offset and implement check into aimbot

        static const DWORD TimeOnScreen = 0xE4; //increments over time only when entity is on local player's screen. ideal for auto-aiming
        static const DWORD Hitpoints = 0xEC;

        static const DWORD PlayerName = 0x205;
    }

    namespace Hacks
    {
        static const DWORD dwVacuum = 0xBFD7D; //all entities stuck in same position if changing xmm register
        static const DWORD dwNoAimRecoil = 0xC2EC3;
    }

}