#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "Platform.h"
#include "Player.h"
#include "FuelBar.h"
#include <string.h>
#include "LabCamera.h"

#define TOTAL_COLUMNS 60
#define TOTAL_ROWS 4
#define MAX_SPEED 8
#define MIN_SPEED 2.5
#define MAX_ORANGE_TIME 25
#define MAX_FUEL 1

using namespace std;

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int isHitten, int color);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void showPlatforms(float deltaTimeSeconds);
	void showPlayer(int playerCollide);
	void showFuelBar();
	void renderPlatformsAgain();
	bool isCollision(float box_minX, float box_minY, float box_minZ, float box_maxX, float box_maxY, float box_maxZ, float point_x, float point_y, float point_z);

	struct Cube
	{
		int isHitten;
		int color;
		float x;
		float z;
	};

	Skyroads::Camera* camera;
	glm::mat4 projectionMatrix;
	Platform* platform;
	Player* player;
	float translateY;
	bool down;
	float speed;
	int jump = 0;
	Cube cubes[TOTAL_ROWS][TOTAL_COLUMNS];
	float playerX, playerY, playerZ;
	bool thirdPerson;
	bool hitOrangePlatform;
	float oldSpeed;
	float orangeSpeed;
	bool fall;
	float orangeSpeedTime;
	int playerHitOrangePlatform;
	float fuel;
	int stopPlatforms;
	FuelBar* myFuelBar;
	float whiteRectangleX;
	float whiteRectangleY;
	float coloredRectangleX;
	float coloredRectangleY;
};
