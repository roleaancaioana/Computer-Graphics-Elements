#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Platform
{
public:
	Platform();
	~Platform();

	Mesh* myPlatform;
};