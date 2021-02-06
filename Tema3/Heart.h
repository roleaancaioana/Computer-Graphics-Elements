#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>

class Heart : public SimpleScene {
public:
	Heart();
	~Heart();

	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	Mesh* myHeart;
};