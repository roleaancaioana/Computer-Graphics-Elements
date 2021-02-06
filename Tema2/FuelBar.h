#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>

class FuelBar : public SimpleScene {
public:
	FuelBar();
	~FuelBar();

	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	Mesh* whiteRectangle;
	Mesh* coloredRectangle;
};