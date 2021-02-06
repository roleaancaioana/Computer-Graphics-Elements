#include "Building.h"
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <string.h>
#include <Core/Engine.h>

using namespace std;

Building::Building() {
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(-1, -1,  1),
			glm::vec3(0, -1, 1),
			glm::vec3(-1, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(-1, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(-1, 0, 0),
			glm::vec3(0, 0, 0)
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	
			1, 3, 2,			
			2, 3, 7,
			2, 7, 6,
			1, 7, 3,
			1, 5, 7,
			6, 7, 4,
			7, 5, 4,
			0, 4, 1,
			1, 4, 5,
			2, 6, 4,
			0, 2, 4
		};

		std::vector<glm::vec3> normals
		{
			glm::vec3(0, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 0, -1),
			glm::vec3(-1, 0, 0)
		};

		vector<glm::vec2> textureCoordinates = {
			glm::vec2(1, 1),
			glm::vec2(0, 1),
			glm::vec2(1, 0),			
			glm::vec2(0, 0)
		};

		// Create a new mesh from buffer data
		myBuilding = new Mesh("myBuilding");
		myBuilding->InitFromData(vertices, normals, textureCoordinates, indices);
	}
}

Building::~Building() {
}