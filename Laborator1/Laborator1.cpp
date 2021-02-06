#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		Mesh* teapotMesh = new Mesh("teapot");
		Mesh* sphereMesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		teapotMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		sphereMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
		meshes[teapotMesh->GetMeshID()] = teapotMesh;
		meshes[sphereMesh->GetMeshID()] = sphereMesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (changeBackgroundColor == 1) {
		// sets the clear color for the color buffer
		glClearColor(0, 0, 1, 1);

		// clears the color buffer (using the previously set color) and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//changeBackgroundColor = 0;
	}
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes[shownObject], glm::vec3(x, y, z));


}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->KeyHold(GLFW_KEY_D)) {
			x += speed * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			y -= speed * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			x -= speed * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			y += speed * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_W)) {
			z -= speed * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			z += speed * deltaTime;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
		changeBackgroundColor = counter % 2;
		counter++;
	}
	if (key == GLFW_KEY_G) {
		shownObject = objects[i % numberOfObjects];
		i++;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
