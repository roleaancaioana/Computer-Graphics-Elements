#include "Quad.h"
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <string.h>
#include <Core/Engine.h>

using namespace std;

Quad::Quad() {
	vector<glm::vec3> vertices
	{
		glm::vec3(0.5f,   0.5f, 0.0f),	
		glm::vec3(0.5f,  -0.5f, 0.0f),	
		glm::vec3(-0.5f, -0.5f, 0.0f),	
		glm::vec3(-0.5f,  0.5f, 0.0f),	
	};

	vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	// TODO : Complete texture coordinates for the square
	vector<glm::vec2> textureCoords
	{
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	};

	vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	myQuad = new Mesh("myQuad");
	myQuad->InitFromData(vertices, normals, textureCoords, indices);
}

Quad::~Quad() {
}