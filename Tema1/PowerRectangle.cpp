#include "PowerRectangle.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

PowerRectangle::PowerRectangle() {
	vector<unsigned short> indices;
	vector<VertexFormat> vertices;
	rectangle = new Mesh("rectangle");
	glm::vec3 colorArrow = glm::vec3(0.3f, 0, 0.5f);

	vertices = {
		VertexFormat(glm::vec3(0, 0, 0), colorArrow),
		VertexFormat(glm::vec3(4, 0, 0), colorArrow),
		VertexFormat(glm::vec3(0, 3, 0), colorArrow),
		VertexFormat(glm::vec3(4, 3, 0), colorArrow)
	};

	indices = {0, 1, 3,
			   0, 3, 2};

	glLineWidth(10.0f);
	rectangle->SetDrawMode(GL_TRIANGLE_FAN);
	rectangle->InitFromData(vertices, indices);
}

PowerRectangle::~PowerRectangle() {

}


