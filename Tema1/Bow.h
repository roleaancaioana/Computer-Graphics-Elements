#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Bow
{
public:
	Bow();
	~Bow();

	Mesh* arrow;
	Mesh* bow;
};