#include "AbeUtility.h"
#include<cmath>

bool AbeUtility::IsHIt(const Vector2& pos1, const Vector2& pos2, const float radius1, const float radius2)
{
	auto diffX = pos1.x - pos2.x;//行った先から行った元
	auto diffY = pos1.y - pos2.y;//行った先から行った元
	auto distance= hypotf(diffX, diffY);// 斜辺
	float overlapLength = radius2 + radius1 - distance;
	if (overlapLength >= 0.0f)
	{
		return true;
	}
	return false;
}
