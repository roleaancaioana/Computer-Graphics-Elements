#include "NewLife.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

NewLife::NewLife() {
	life = new Mesh("life");
	glm::vec3 color = glm::vec3(0, 0.2f, 0.5f);

	vector<unsigned short> indices;
	vector<VertexFormat> vertices;

	vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-21.15f, -21.15f, 0), color),
		VertexFormat(glm::vec3(-21.15f, 21.15f, 0), color),
		VertexFormat(glm::vec3(21.15f, 21.15f, 0), color),
		VertexFormat(glm::vec3(21.15f, -21.15f, 0), color)
	};

	indices = {0, 2, 1,
			   0, 4, 3};

	life->SetDrawMode(GL_TRIANGLES);
	life->InitFromData(vertices, indices);
}

NewLife::~NewLife() {

}


