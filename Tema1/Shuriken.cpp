#include "Shuriken.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Shuriken::Shuriken() {
	this->star = new Mesh("star");
	vector<unsigned short> indices;
	vector<VertexFormat> vertices;
	glm::vec3 colorArrow = glm::vec3(0, 0.7f, 0.1f);

	vertices = {
		VertexFormat(glm::vec3(0, 0, 0), colorArrow),
		VertexFormat(glm::vec3(30, 0, 0), colorArrow),
		VertexFormat(glm::vec3(30, 30, 0), colorArrow),
		VertexFormat(glm::vec3(0, 30, 0), colorArrow),
		VertexFormat(glm::vec3(-30, 30, 0), colorArrow),
		VertexFormat(glm::vec3(-30, 0, 0), colorArrow),
		VertexFormat(glm::vec3(-30, -30, 0), colorArrow),
		VertexFormat(glm::vec3(0, -30, 0), colorArrow),
		VertexFormat(glm::vec3(30, -30, 0), colorArrow),
	};

	indices = {0, 1, 2,
			   0, 3, 4,
			   0, 5, 6,
			   0, 7, 8};
	star->SetDrawMode(GL_TRIANGLES);
	star->InitFromData(vertices, indices);
}

Shuriken::~Shuriken() {

}


