#include "Bow.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Bow::Bow() {
	arrow = new Mesh("arrow");
	vector<VertexFormat> vertices;
	vector<VertexFormat> otherVertices;
	vector<unsigned short> otherIndices;
	bow = new Mesh("bow");
	glm::vec3 colorArrow = glm::vec3(0.3f, 0, 0.5f);
	vector<unsigned short> indices;

	vertices = {
		VertexFormat(glm::vec3(0, 0, 0), colorArrow),
		VertexFormat(glm::vec3(0, 10, 0), colorArrow),
		VertexFormat(glm::vec3(120, 10, 0), colorArrow),
		VertexFormat(glm::vec3(120, 0, 0), colorArrow),
		VertexFormat(glm::vec3(150, 5, 0), colorArrow)
	};

	indices = {0,1,2,
			   2,4,3,
			   0,2,3};

	arrow->InitFromData(vertices, indices);

	int counter = 0;
	glm::vec3 color = glm::vec3(1, 0, 1);
	GLfloat radius = 75;

	for (float i = 0.0f; i <= M_PI; i += 0.1f) {
		otherIndices.push_back(counter);
		otherVertices.push_back(VertexFormat(glm::vec3((radius * cos(-i)), (radius * sin(-i)), 0), color));
		counter++;
	}

	bow->SetDrawMode(GL_LINE_LOOP);
	bow->InitFromData(otherVertices, otherIndices);
}

Bow::~Bow() {

}


