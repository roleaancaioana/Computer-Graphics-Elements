#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "..\Tema2\Platform.h"
#include "..\Tema2\Player.h"
#include "..\Tema2\FuelBar.h"
#include "..\Tema2\LabCamera.h"
#include "Heart.h"
#include "MyScore.h"
#include "CubeLoseLife.h"
#include "CubeKiller.h"
#include "Gift.h"
#include "SantaClaus.h"
#include "Building.h"
#include "Quad.h"

#define TOTAL_COLUMNS 60
#define TOTAL_ROWS 4
#define MAX_SPEED 8
#define MIN_SPEED 2.5
#define MAX_ORANGE_TIME 25
#define MAX_FUEL 1
#define MAX_CUBES_FOR_LOSING_LIFE 1
#define MAX_CUBES_KILLER 1
#define MAX_SCORE_ELEMENTS 2
#define MAX_BLOCKS 50
#define MAX_SNOWMANS 6

using namespace std;

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

private:
	struct Cube
	{
		int type;
		int isHitten;
		int color;
		float x;
		float z;
		int initialZ;
	};

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int isHitten, int color, Texture2D* texture1);
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
	bool obstaclesCollision(const float xmin, const float ymin, const float zmin, const float xmax, const float ymax, const float zmax);
	void showFuelBar();
	void showHeart();
	void showScore(float deltaTimeSeconds);
	void showCubeKiller();
	void showCubeLoseLife();
	void showBackground();
	void showSnowman(Cube snowmans[MAX_SNOWMANS]);
	void renderPlatformsAgain();
	void renderBuildingsAgain(Cube blocks[3][MAX_BLOCKS]);
	void showBuilding(Cube blocks[3][MAX_BLOCKS]);
	void showGround();
	void renderSnowmansAgain(Cube snowmans[MAX_SNOWMANS]);
	void showGift(float deltaTimeSeconds);
	void showSantaClaus(float deltaTimeSeconds);
	bool goodCollision(float x, float y, float z);
	bool isCollision(float box_minX, float box_minY, float box_minZ, float box_maxX, float box_maxY, float box_maxZ, float point_x, float point_y, float point_z);

	Skyroads::Camera* camera;
	CubeLoseLife* cubeLoseLife;
	CubeKiller* cubeKiller;
	glm::mat4 projectionMatrix;
	Platform* platform;
	Player* player;
	Gift* gift;
	Quad* quad;
	SantaClaus* santaClaus;
	float translateY;
	bool down;
	float speed;
	int jump = 0;
	unordered_map<float, float> platformOccupied;
	Cube cubesKiller[MAX_CUBES_KILLER];
	Cube cubesForLosingLife[MAX_CUBES_FOR_LOSING_LIFE];
	Cube rightSnowmans[MAX_SNOWMANS];
	Cube leftSnowmans[MAX_SNOWMANS];
	Cube cubes[TOTAL_ROWS][TOTAL_COLUMNS];
	Cube gifts[MAX_SCORE_ELEMENTS];
	Cube rightBlocks[3][MAX_BLOCKS];
	Cube leftBlocks[3][MAX_BLOCKS];
	unordered_map<string, Texture2D*> mapTextures;
	float playerX, playerY, playerZ;
	bool thirdPerson;
	bool hitOrangePlatform;
	float oldSpeed;
	float orangeSpeed;
	bool fall;
	float orangeSpeedTime;
	int playerHitOrangePlatform;
	float fuel;
	float angularStep;
	int stopPlatforms;
	FuelBar* myFuelBar;
	Building* building;
	Heart* heart;
	MyScore* score;
	float santaClausX, santaClausY, santaClausZ;
	int santaCollide;
	float scoreScale;
	float nrLives;
	float whiteRectangleX;
	float whiteRectangleY;
	float coloredRectangleX;
	float coloredRectangleY;
};
