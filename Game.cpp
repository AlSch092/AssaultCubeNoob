//By AlSch092 @ github
#include "Game.hpp"

Vector2 Game::GetAimPositionOfEntity(Vector3 localPosition, Vector3 entPosition)
{
	Vector2 aimDest;

    float deltaX = entPosition.x - localPosition.x;
    float deltaY = entPosition.y - localPosition.y;
    float deltaZ = entPosition.z - localPosition.z;

    aimDest.x = atan2f(deltaY, deltaX) * (180.0f / M_PI);

    if (aimDest.x < 0) 
    {
        aimDest.x += 360.0f;
    }

    float distanceXY = sqrtf(deltaX * deltaX + deltaY * deltaY);
    aimDest.y = atan2f(deltaZ, distanceXY) * (180.0f / M_PI);

    aimDest.x += 90.0f;

    return aimDest;
}
