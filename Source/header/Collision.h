#pragma once
#include "DxLib.h"
#include <vector>
#include "Stage_object.h"

// “–‚½‚è”»’è‚ÉŠÖ‚·‚é‚Ü‚Æ‚ßƒNƒ‰ƒX
class  Collision
{
public:
	static bool CheckSphereToSphere(VECTOR centerPosition1, float radius1, VECTOR centerPosition2, float radius2);

	static bool CheckCollisionAABB(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);

	static VECTOR ResolveAABB(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);

	static bool CheckLineToAABB(VECTOR start, VECTOR end, VECTOR boxPos, VECTOR boxSize);

	static bool CheckRayAABB(VECTOR rayStart, VECTOR rayEnd, VECTOR boxCenter, VECTOR boxSize);

	static float GetDistance(VECTOR a, VECTOR b);

private:

};


