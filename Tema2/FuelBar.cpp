#include "FuelBar.h"
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <string.h>
#include <Core/Engine.h>

using namespace std;

Mesh* FuelBar::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

FuelBar::FuelBar() {
	vector<unsigned short> whiteIndices;
	vector<VertexFormat> whiteVertices;
	whiteVertices = {
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(0.6f, 0, 0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(0.6f, 0.08f, 0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(0, 0.08f, 0), glm::vec3(1, 1, 1))
	};

	whiteIndices = { 0, 1, 2,
			   0, 2, 3 };

	whiteRectangle = CreateMesh("whiteRectangle", whiteVertices, whiteIndices);

	vector<unsigned short> coloredIndices;
	vector<VertexFormat> coloredVertices;
	coloredVertices = {
		VertexFormat(glm::vec3(0.01f, 0, 0), glm::vec3(0, 0.4333f, 1)),
		VertexFormat(glm::vec3(0.596f, 0, 0), glm::vec3(0, 0.4333f, 1)),
		VertexFormat(glm::vec3(0.596f, 0.07f, 0), glm::vec3(0, 0.4333f, 1)),
		VertexFormat(glm::vec3(0.01f, 0.07f, 0), glm::vec3(0, 0.4333f, 1))
	};

	coloredIndices = { 0, 1, 2,
					   0, 2, 3 };

	coloredRectangle = CreateMesh("coloredRectangle", coloredVertices, coloredIndices);
}

FuelBar::~FuelBar() {
}