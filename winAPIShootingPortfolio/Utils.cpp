#include "Utils.h"
#include "stdafx.h"

namespace MY_UTIL
{
	// ���������� �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	//��ŸƮ -> ���� -> ���� ��������
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);

		float angle = acos(x / d);

		if (y > 0) angle = PI_2 - angle;

		return angle;
	}


}
