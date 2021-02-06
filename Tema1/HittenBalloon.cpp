#include "HittenBalloon.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

HittenBalloon::HittenBalloon(glm::vec3 color) {
	balloon = new Mesh("hittenBalloon");
	this->color = color;
	vector<unsigned short> indices;
	vector<VertexFormat> vertices;
	int counter = 0;

	vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5, 0, 0), color),
		VertexFormat(glm::vec3(4, 10, 0), color),
		VertexFormat(glm::vec3(10, 20, 0), color),
		VertexFormat(glm::vec3(0, 20, 0), color),
		VertexFormat(glm::vec3(2, 10, 0), color)
	};

	indices = {0, 1, 2,
			   0, 2, 5,
			   5, 3, 4,
			   5, 2, 3};

	balloon->SetDrawMode(GL_TRIANGLE_STRIP);
	balloon->InitFromData(vertices, indices);

}

HittenBalloon::~HittenBalloon() {

}


