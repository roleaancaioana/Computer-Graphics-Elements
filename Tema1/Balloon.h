#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Balloon
{
public:
	Balloon(glm::vec3 color);
	~Balloon();

	Mesh* circleBalloon;
	Mesh* lineBalloon;
	glm::vec3 color;
};