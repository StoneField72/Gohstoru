#include "Collision.h"
#include "Master.h"

VECTOR VDivScalar(VECTOR vec, float scalar);

bool Collision::CheckSphereToSphere(VECTOR centerPosition1, float radius1, VECTOR centerPosition2, float radius2)
{
    return HitCheck_Sphere_Sphere(centerPosition1, radius1, centerPosition2, radius2);
}


//óßï˚ëÃÇ∆óßï˚ëÃÇÃìñÇΩÇËîªíË
bool Collision::CheckCollisionAABB(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize)
{
    return abs(aPos.x - bPos.x) < (aSize.x + bSize.x) / 2 &&
        abs(aPos.y - bPos.y) < (aSize.y + bSize.y) / 2 &&
        abs(aPos.z - bPos.z) < (aSize.z + bSize.z) / 2;
}

//âüÇµñﬂÇ∑èàóù
VECTOR Collision::ResolveAABB(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize)
{
    VECTOR delta = { bPos.x - aPos.x, bPos.y - aPos.y, bPos.z - aPos.z };
    VECTOR overlap = {
        (aSize.x + bSize.x) / 2 - abs(delta.x),
        (aSize.y + bSize.y) / 2 - abs(delta.y),
        (aSize.z + bSize.z) / 2 - abs(delta.z)
    };

    // ç≈Ç‡èdÇ»ÇËÇ™è¨Ç≥Ç¢é≤ÇíTÇ∑
    if (overlap.x < overlap.y && overlap.x < overlap.z) 
    {
        aPos.x += (delta.x > 0) ? -overlap.x : overlap.x;
    }
    else if (overlap.y < overlap.z) 
    {
        aPos.y += (delta.y > 0) ? -overlap.y : overlap.y;
    }
    else 
    {
        aPos.z += (delta.z > 0) ? -overlap.z : overlap.z;
    }

    return aPos;
}


bool Collision::CheckLineToAABB(VECTOR start, VECTOR end, VECTOR boxPos, VECTOR boxSize)
{
    const int steps = 20;
    for (int i = 0; i <= steps; i++) 
    {
        float t = (float)i / steps;
        VECTOR point;
        point.x = start.x + (end.x - start.x) * t;
        point.y = start.y + (end.y - start.y) * t;
        point.z = start.z + (end.z - start.z) * t;

        if (Collision::CheckCollisionAABB(point, VGet(1, 1, 1), boxPos, boxSize)) 
        {
            return true; // è·äQï®Ç…ìñÇΩÇ¡ÇΩ
        }
    }

    return false; // è·äQï®Ç»Çµ
}

//ê¸ï™Ç∆óßï˚ëÃÇÃìñÇΩÇËîªíË
bool Collision::CheckRayAABB(VECTOR rayStart, VECTOR rayEnd, VECTOR boxCenter, VECTOR boxSize)
{
    VECTOR dir = VSub(rayEnd, rayStart); // ê¸ï™ÇÃï˚å¸

    VECTOR halfSize = VDivScalar(boxSize, 2.0f);
    VECTOR minBox = VSub(boxCenter, halfSize);
    VECTOR maxBox = VAdd(boxCenter, halfSize);

    float tMin = 0.0f;
    float tMax = 1.0f;

    for (int i = 0; i < 3; i++) 
    {
        float rayOrigin = (&rayStart.x)[i];
        float rayDir = (&dir.x)[i];
        float boxMin = (&minBox.x)[i];
        float boxMax = (&maxBox.x)[i];

        if (fabs(rayDir) < 1e-6f) 
        {
            // ê¸ï™Ç™Ç±ÇÃé≤Ç…ïΩçs Å® îÕàÕäOÇ»ÇÁåç∑Ç»Çµ
            if (rayOrigin < boxMin || rayOrigin > boxMax) 
            {
                return false;
            }
        }
        else 
        {
            float t1 = (boxMin - rayOrigin) / rayDir;
            float t2 = (boxMax - rayOrigin) / rayDir;

            if (t1 > t2) std::swap(t1, t2);

            tMin = max(tMin, t1);
            tMax = min(tMax, t2);

            if (tMin > tMax) {
                return false; // åç∑Ç»Çµ
            }
        }
    }

    return true; // åç∑Ç†ÇË
}

VECTOR VDivScalar(VECTOR vec, float scalar)
{
    VECTOR result;
    result.x = vec.x / scalar;
    result.y = vec.y / scalar;
    result.z = vec.z / scalar;
    return result;
}

float Collision::GetDistance(VECTOR a, VECTOR b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}