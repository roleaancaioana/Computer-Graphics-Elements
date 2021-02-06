#include "Heart.h"
#include "vector"
#include <iostream>

using namespace std;

Mesh* Heart::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
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

Heart::Heart() {
	int i = 0;
	vector<VertexFormat> vertices;
	vector<GLushort> indices;

	for (float x = -1.139f; x <= 1.139f; x += 0.001f) {
		float delta = cbrt(x * x) * cbrt(x * x) - 4 * x * x + 4;
		float y1 = (cbrt(x * x) + sqrt(delta)) / 2;
		vertices.push_back(VertexFormat(glm::vec3(x, y1, 0), glm::vec3(1, 0, 0)));
		indices.push_back(i++);
		float y2 = (cbrt(x * x) - sqrt(delta)) / 2;
		vertices.push_back(VertexFormat(glm::vec3(x, y2, 0), glm::vec3(1, 0, 0)));
		indices.emplace_back(i++);
	}

	myHeart = CreateMesh("heart", vertices, indices);
	myHeart->SetDrawMode(GL_TRIANGLE_FAN);
}

Heart::~Heart() {
	delete this->myHeart;
}
