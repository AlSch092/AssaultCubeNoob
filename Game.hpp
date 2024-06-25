#pragma once
#include <Windows.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct Vector2
{
	float x;
	float y;
};

typedef struct Vector3
{
	float x;
	float y;
	float z;
};

namespace Game
{
	Vector2 GetAimPositionOfEntity(Vector3 localPosition, Vector3 entPosition); //3d position to 2d screen translation
}
