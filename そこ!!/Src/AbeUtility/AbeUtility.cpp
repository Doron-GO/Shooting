#include "AbeUtility.h"
#include<cmath>

bool AbeUtility::IsHIt(const Vector2& pos1, const Vector2& pos2, const float radius1, const float radius2)
{
	auto diffX = pos1.x - pos2.x;//�s�����悩��s������
	auto diffY = pos1.y - pos2.y;//�s�����悩��s������
	auto distance= hypotf(diffX, diffY);// �Ε�
	float overlapLength = radius2 + radius1 - distance;
	if (overlapLength >= 0.0f)
	{
		return true;
	}
	return false;
}
