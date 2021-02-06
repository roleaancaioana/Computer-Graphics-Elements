#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 myTranslate(float translateX, float translateY)
	{
		// TODO implement translate matrix
		return glm::transpose(glm::mat3(1, 0, translateX,
			0, 1, translateY,
			0, 0, 1));
	}

	// Scale matrix
	inline glm::mat3 myScale(float scaleX, float scaleY)
	{
		// TODO implement scale matrix
		return glm::transpose(glm::mat3(scaleX, 0, 0,
			0, scaleY, 0,
			0, 0, 1));
	}

	// Rotate matrix
	inline glm::mat3 myRotate(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(glm::mat3(cos(radians), -sin(radians), 0,
			sin(radians), cos(radians), 0,
			0, 0, 1));
	}
}
