#include "Balloon.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Balloon::Balloon(glm::vec3 color) {
	this->color = color;
	this->circleBalloon = new Mesh("circleBalloon");
	this->lineBalloon = new Mesh("lineBalloon");

	vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(15, -20, 0), color),
		VertexFormat(glm::vec3(0, -40, 0), color),
		VertexFormat(glm::vec3(15, -60, 0), color)
	};

	vector<unsigned short> indices = {0,1,2,3};

	lineBalloon->SetDrawMode(GL_LINE_STRIP);
	lineBalloon->InitFromData(vertices, indices);

	vector<VertexFormat> otherVertices;
	vector<GLushort> otherIndices;
	int counter = 0;
	GLfloat radius = 40;

	for (float i = 0.0; i <= M_PI * 2; i += 0.1) {
		otherIndices.push_back(counter);
		otherVertices.push_back(VertexFormat(glm::vec3((radius * cos(-i)), (radius * sin(-i)), 0), color));
		counter++;
	}

	circleBalloon->SetDrawMode(GL_TRIANGLE_FAN);
	circleBalloon->InitFromData(otherVertices, otherIndices);

}

Balloon::~Balloon() {

}


