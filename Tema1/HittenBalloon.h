#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class HittenBalloon
{
public:
	HittenBalloon(glm::vec3 color);
	~HittenBalloon();

	glm::vec3 color;
	Mesh* balloon;
};