#pragma once

#include <include/glm.h>
#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>

class Building
{
public:
	Building();
	~Building();

	Mesh* myBuilding;
};