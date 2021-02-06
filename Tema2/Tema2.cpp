#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include "Transform3D.h"
#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
	platform = new Platform();
	player = new Player();
	myFuelBar = new FuelBar();
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
		srand((unsigned int)time(NULL));
		camera = new Skyroads::Camera();
		camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		
		projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
		playerY = 0.5f;
		playerX = 0;
		playerZ = 0;
		down = false;
		jump = 0;
		stopPlatforms = 0;
		speed = 3;
		thirdPerson = true;
		orangeSpeed = 8;
		orangeSpeedTime = MAX_ORANGE_TIME;
		playerHitOrangePlatform = 0;
		fall = false;
		fuel = MAX_FUEL;
		whiteRectangleX = 0.35f;
		whiteRectangleY = 0.798f;
		coloredRectangleX = 0.348f;
		coloredRectangleY = 0.7999f;
		hitOrangePlatform = false;

		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = 0; j < TOTAL_COLUMNS; ++j) {
				cubes[i][j].x = i - 1.8f; 
				cubes[i][j].z = -j - 1;
				if (j < 10) {
					cubes[i][j].color = 5;
				}
				else if (rand() % 5 == 0) {
					cubes[i][j].color = rand() % 6;
				}
				else {
					cubes[i][j].color = 5;
				}
				cubes[i][j].isHitten = 0;
			}
		}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("ShaderForPlatform");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderForPlatform.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderForPlatform.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForPlayer");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderForPlayer.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderForPlayer.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForFuel");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderForFuel.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderForFuel.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (fuel <= 0) {
		cout << "Ai ramas fara combustibil! Jocul s-a terminat!" << endl;
		exit(0);
	}

	if (fall == false) {
		fuel -= deltaTimeSeconds * 0.01 * speed;
	}

	if (playerY < -4) {
		cout << "Jocul s-a terminat! Ai pierdut!" << endl;
		exit(0);
	}

	if (fall == true || playerX < -2.3f || playerX > 1.8) {
		fall = true;
		stopPlatforms = 1;
		playerY -= 2 * deltaTimeSeconds;
	}

	if (thirdPerson == true) {
		glm::vec3 pos = glm::vec3(playerX, playerY + 1, 3);
		camera->Set(glm::vec3(pos), pos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	}
	else {
		glm::vec3 pos = glm::vec3(playerX, playerY, playerZ - 1.5f);
		camera->Set(glm::vec3(pos), pos + glm::vec3(0, 0.1f, -0.5f), glm::vec3(0, 1, 0));
	}

	if (hitOrangePlatform == true) {
		orangeSpeedTime -= 7 * deltaTimeSeconds;
		if (orangeSpeedTime < 0) {
			hitOrangePlatform = false;
			speed = oldSpeed;
			orangeSpeedTime = MAX_ORANGE_TIME;
			playerHitOrangePlatform = 0;
		}
	}

	if (jump == 1) {
		if (playerY <= 1.5f && down == false) {
			playerY += 2 * deltaTimeSeconds;
		}
		else if (playerY <= 1.5f && down == true){
			playerY -= 2 * deltaTimeSeconds;
		}

		if (playerY <= 0.5) {
			down = false;
			jump = 0;
			playerY = 0.5;
		}
		if (playerY > 1.5f) {
			down = true;
			playerY = 1.5f;
		}

	}

	if (stopPlatforms == 0) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = 0; j < TOTAL_COLUMNS; ++j) {
				cubes[i][j].z += deltaTimeSeconds * speed;
			}
		}
	}

	showPlatforms(deltaTimeSeconds);
	showPlayer(playerHitOrangePlatform);
	showFuelBar();
	renderPlatformsAgain();
}

void Tema2::renderPlatformsAgain()
{
	if (cubes[0][TOTAL_COLUMNS / 2].z > 0) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			cubes[i][0].z = cubes[i][TOTAL_COLUMNS - 1].z - 1;
			if (rand() % 5 == 0) {
				cubes[i][0].color = rand() % 6;
			}
			else {
				cubes[i][0].color = 5;
			}
			cubes[i][0].isHitten = 0;
		}

		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = 1; j <= TOTAL_COLUMNS / 2; ++j) {
				cubes[i][j].z = cubes[i][j - 1].z - 1;
				if (rand() % 5 == 0) {
					cubes[i][j].color = rand() % 6;
				}
				else {
					cubes[i][j].color = 5;
				}
				cubes[i][j].isHitten = 0;
			}
		}

	} else if (cubes[0][TOTAL_COLUMNS - 1].z > 0) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = TOTAL_COLUMNS - TOTAL_COLUMNS / 2; j < TOTAL_COLUMNS; ++j) {
				cubes[i][j].z = cubes[i][j - 1].z - 1;
			}
		}
	}
}

bool Tema2::isCollision(float box_minX, float box_minY, float box_minZ, float box_maxX, float box_maxY, float box_maxZ,
	float point_x, float point_y, float point_z) {
	return (point_x >= box_minX && point_x <= box_maxX) &&
		(point_y >= box_minY && point_y <= box_maxY) &&
		(point_z >= box_minZ && point_z <= box_maxZ);
}

void Tema2::showPlayer(int playerCollide) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(playerX, playerY, playerZ);
	modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
	RenderSimpleMesh(player->myPlayer, shaders["ShaderForPlayer"], modelMatrix, playerCollide, 3);
}

void Tema2::showFuelBar() {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(coloredRectangleX, coloredRectangleY, 0);
	modelMatrix *= Transform3D::Scale(fuel, 1, 1);
	RenderSimpleMesh(myFuelBar->coloredRectangle, shaders["ShaderForFuel"], modelMatrix, 0, 8);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(whiteRectangleX, whiteRectangleY, 0);
	RenderSimpleMesh(myFuelBar->whiteRectangle, shaders["ShaderForFuel"], modelMatrix, 0, 7);
}

void Tema2::showPlatforms(float deltaTimeSeconds) {
	for (int i = 0; i < TOTAL_ROWS; ++i) {
		for (int j = 0; j < TOTAL_COLUMNS; ++j) {
			if (cubes[i][j].color != 0) {
				if (isCollision(cubes[i][j].x - 0.5f, -0.1f, cubes[i][j].z - 0.5f, cubes[i][j].x + 0.5f,
					0.1f, cubes[i][j].z + 0.5f, playerX, playerY - 0.4f, playerZ)) {
					cubes[i][j].isHitten = 1;

					//Platforma portocalie
					if (cubes[i][j].color == 3) {
						oldSpeed = speed;
						speed = orangeSpeed;
						hitOrangePlatform = true;
						playerHitOrangePlatform = 1;
					}

					//Platforma verde
					if (cubes[i][j].color == 4) {
						fuel += deltaTimeSeconds * 0.5;
						if (fuel > MAX_FUEL) {
							fuel = MAX_FUEL;
						}
					}

					//Platforma galbena
					if (cubes[i][j].color == 2) {
						fuel -= deltaTimeSeconds * 0.5;
					}

					//Platforma rosie
					if (cubes[i][j].color == 1) {
						cout << "S-a terminat jocul!" << endl;
						exit(0);
					}

				}
				else {
					cubes[i][j].isHitten = 0;
				}
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix *= Transform3D::Translate(cubes[i][j].x, 0, cubes[i][j].z);
					modelMatrix *= Transform3D::Scale(1, 0.2f, 1);

					RenderSimpleMesh(platform->myPlatform, shaders["ShaderForPlatform"], modelMatrix, cubes[i][j].isHitten, cubes[i][j].color);
			}
			else if (isCollision(cubes[i][j].x - 0.5f, -0.1f, cubes[i][j].z - 0.5f, cubes[i][j].x + 0.5f,
				0.1f, cubes[i][j].z + 0.5f, playerX, playerY - 0.4f, playerZ)) {
				fall = true;
				stopPlatforms = 1;
				playerHitOrangePlatform = 0;
			}
		}
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int isHitten, int color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	auto location_model = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	auto location_color = glGetUniformLocation(shader->GetProgramID(), "Color");
	glUniform1i(location_color, color);

	auto location_clock = glGetUniformLocation(shader->GetProgramID(), "Clock");
	auto time = Engine::GetElapsedTime();
	glUniform1f(location_clock, time);

	if (color != 7 && color != 8) {
		auto location_view = glGetUniformLocation(shader->GetProgramID(), "View");
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		auto location_projection = glGetUniformLocation(shader->program, "Projection");
		glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		auto location_collide = glGetUniformLocation(shader->GetProgramID(), "Collide");
		glUniform1i(location_collide, isHitten);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// add key press event
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (hitOrangePlatform == false) {
			if (window->KeyHold(GLFW_KEY_S)) {
				if (speed < MIN_SPEED) {
					speed = MIN_SPEED;
				}
				else {
					speed -= 5 * deltaTime;
				}
			}

			if (window->KeyHold(GLFW_KEY_W)) {
				if (speed > 5) {
					speed = MAX_SPEED;
				}
				else {
					speed += 5 * deltaTime;
				}
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			playerX -= 3 * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			playerX += 3 * deltaTime;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C) {
		if (thirdPerson == true) {
			thirdPerson = false;
		}
		else {
			thirdPerson = true;
		}
	}
	if (key == GLFW_KEY_SPACE && fall == false) {
		jump = 1;
	}
	// add key press event
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
