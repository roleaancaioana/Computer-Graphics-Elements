#include "MyScore.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

MyScore::MyScore() {
	myScore = new Mesh("MyScore");
	glm::vec3 color = glm::vec3(0.2f, 0.5f, 0);

	vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(10, 0, 0), color),
		VertexFormat(glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(10, 1, 0), color)
	};

	std::vector<unsigned short> indices = {0,1,3,
										   0,3,2};

	glLineWidth(10.0f);
	myScore->SetDrawMode(GL_TRIANGLE_FAN);
	myScore->InitFromData(vertices, indices);
}

MyScore::~MyScore() {

}


