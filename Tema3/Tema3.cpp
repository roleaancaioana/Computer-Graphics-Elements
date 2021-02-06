#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include "Transform3D.h"
#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
	platform = new Platform();
	player = new Player();
	myFuelBar = new FuelBar();
	heart = new Heart();
	score = new MyScore();
	cubeLoseLife = new CubeLoseLife();
	cubeKiller = new CubeKiller();
	gift = new Gift();
	santaClaus = new SantaClaus();
	building = new Building();
	quad = new Quad();
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	srand((unsigned int)time(NULL));
	camera = new Skyroads::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "warning.jpg").c_str(), GL_REPEAT);
		mapTextures["warning"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "danger.jpg").c_str(), GL_REPEAT);
		mapTextures["danger"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "snowflakes.PNG").c_str(), GL_REPEAT);
		mapTextures["snowflakes"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "gift.jpg").c_str(), GL_REPEAT);
		mapTextures["gift"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "santaClaus.jpg").c_str(), GL_REPEAT);
		mapTextures["santaClaus"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "snow.jpg").c_str(), GL_REPEAT);
		mapTextures["snow"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sky.jpg").c_str(), GL_REPEAT);
		mapTextures["sky"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building1.jpg").c_str(), GL_REPEAT);
		mapTextures["building1"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building2.jpg").c_str(), GL_REPEAT);
		mapTextures["building2"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building3.jpg").c_str(), GL_REPEAT);
		mapTextures["building3"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "snowman.png").c_str(), GL_REPEAT);
		mapTextures["snowman"] = texture;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	playerY = 0.5f;
	playerX = 0;
	playerZ = 0;
	scoreScale = 0;
	down = false;
	jump = 0;
	stopPlatforms = 0;
	santaCollide = 0;
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
	nrLives = 3.0f;
	angularStep = 0;
	santaClausX = 0;
	santaClausY = 0.35f;
	santaClausZ = -22;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	for (int i = 0; i < MAX_SNOWMANS; ++i) {
		rightSnowmans[i].z = -2 - i * 15;
		rightSnowmans[i].x = 3.2f;
	}

	for (int i = 0; i < MAX_SNOWMANS; ++i) {
		leftSnowmans[i].z = -1 - i * 15;
		leftSnowmans[i].x = -3.2f;
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < MAX_BLOCKS; ++j) {
			rightBlocks[i][j].type = rand() % 2;
			rightBlocks[i][j].x = 4.5f + rand() % 3;
			rightBlocks[i][j].z = -j - 2;
			rightBlocks[i][j].initialZ = rightBlocks[i][j].z;
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < MAX_BLOCKS; ++j) {
			leftBlocks[i][j].type = rand() % 2;
			leftBlocks[i][j].x = -4.5f - rand() % 3;
			leftBlocks[i][j].z = -j - 3;
			leftBlocks[i][j].initialZ = leftBlocks[i][j].z;
		}
	}

	for (int i = 0; i < MAX_CUBES_FOR_LOSING_LIFE; ++i) {
		float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		while (platformOccupied[-j] == 1) {
			j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		}

		platformOccupied[-j] = 1;
		cubesForLosingLife[i].z = j;
		cubesForLosingLife[i].initialZ = j;
		cubesForLosingLife[i].x = -1.8f + rand() % TOTAL_ROWS;
		cubesForLosingLife[i].isHitten = 0;
		cubesForLosingLife[i].color = 1;
	}

	for (int i = 0; i < MAX_CUBES_KILLER; ++i) {
		float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		while (platformOccupied[-j] == 1) {
			j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		}

		platformOccupied[-j] = 1;
		cubesKiller[i].z = j;
		cubesKiller[i].initialZ = j;
		cubesKiller[i].x = -1.8f + rand() % TOTAL_ROWS;
		cubesKiller[i].isHitten = 0;
		cubesKiller[i].color = 2;
	}

	for (int i = 0; i < MAX_SCORE_ELEMENTS; ++i) {
		float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;

		while (platformOccupied[-j] == 1) {
			j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		}

		platformOccupied[-j] = 1;
		gifts[i].z = j;
		gifts[i].initialZ = j;
		gifts[i].x = -1.8f + rand() % TOTAL_ROWS;
		gifts[i].isHitten = 0;
		gifts[i].color = 1;
	}

	for (int i = 0; i < TOTAL_ROWS; ++i) {
		for (int j = 0; j < TOTAL_COLUMNS; ++j) {
			cubes[i][j].x = i - 1.8f;
			cubes[i][j].z = -j - 1;
			if (j < 21) {
				cubes[i][j].color = 5;
			}
			else if (rand() % 5 == 0) {
				cubes[i][j].color = rand() % 8;
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

	{
		Shader* shader = new Shader("ShaderForHeart");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderForHeart.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderForHeart.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForCubeLoseLife");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderForCubeLoseLife.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderForCubeLoseLife.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForGround");
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/VertexShaderForGround.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/FragmentShaderForGround.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForCubeKiller");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderForCubeKiller.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderForCubeKiller.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForGift");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderForGift.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderForGift.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForSantaClaus");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderForSantaClaus.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderForSantaClaus.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForBackground");
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/VertexShaderForBackground.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/FragmentShaderForBackground.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForBuilding");
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/VertexShaderForBuilding.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/FragmentShaderForBuilding.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderForQuad");
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/VertexShaderForQuad.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/OtherShaders/FragmentShaderForQuad.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema3::Update(float deltaTimeSeconds)
{
	if (fuel <= 0) {
		cout << "Ai ramas fara combustibil! Jocul s-a terminat!" << endl;
		exit(0);
	}
	showHeart();
	if (fall == false) {
		fuel -= deltaTimeSeconds * 0.001 * speed;
	}

	if (fall == true || stopPlatforms == 1) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = 0; j < TOTAL_COLUMNS; ++j) {
				if (cubes[i][j].z < 0) {
					cubes[i][j].color = 5;
				}

			}
		}
	}

	if (playerY < -4) {
		nrLives -= 1.0f;
		playerY = 0.5f;
		playerX = 0;
		playerZ = 0;
		fall = false;
		stopPlatforms = 0;
	}

	if (nrLives <= 0.0f) {
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
		else if (playerY <= 1.5f && down == true) {
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
	platformOccupied.clear();

	if (stopPlatforms == 0) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = 0; j < TOTAL_COLUMNS; ++j) {
				cubes[i][j].z += deltaTimeSeconds * speed;
			}
		}

		for (int i = 0; i < MAX_CUBES_FOR_LOSING_LIFE; ++i) {
			cubesForLosingLife[i].z += deltaTimeSeconds * speed;
		}

		for (int i = 0; i < MAX_CUBES_KILLER; ++i) {
			cubesKiller[i].z += deltaTimeSeconds * speed;
		}

		for (int i = 0; i < MAX_SCORE_ELEMENTS; ++i) {
			gifts[i].z += deltaTimeSeconds * speed;
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < MAX_BLOCKS; ++j) {
				leftBlocks[i][j].z += deltaTimeSeconds * speed;
			}
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < MAX_BLOCKS; ++j) {
				rightBlocks[i][j].z += deltaTimeSeconds * speed;
			}
		}

		for (int i = 0; i < MAX_SNOWMANS; ++i) {
			rightSnowmans[i].z += deltaTimeSeconds * speed;
		}

		for (int i = 0; i < MAX_SNOWMANS; ++i) {
			leftSnowmans[i].z += deltaTimeSeconds * speed;
		}

		santaClausZ += deltaTimeSeconds * speed;
	}

	showBackground();
	showSnowman(rightSnowmans);
	showSnowman(leftSnowmans);
	showGround();
	showBuilding(rightBlocks);
	showBuilding(leftBlocks);
	showGift(deltaTimeSeconds);
	showScore(deltaTimeSeconds);
	showCubeKiller();
	showCubeLoseLife();
	showSantaClaus(deltaTimeSeconds);
	showPlatforms(deltaTimeSeconds);
	showPlayer(playerHitOrangePlatform);
	showFuelBar();
	renderSnowmansAgain(rightSnowmans);
	renderSnowmansAgain(leftSnowmans);
	renderBuildingsAgain(rightBlocks);
	renderBuildingsAgain(leftBlocks);
	renderPlatformsAgain();
}

void Tema3::showScore(float deltaTimeSeconds) {
	if (scoreScale / 4 > 0.06) {
		cout << "Ai castigat!" << endl;
		exit(0);
	}
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.35, 0.9, 0);
	modelMatrix *= Transform3D::Scale(scoreScale / 4, 0.05, 0);
	RenderSimpleMesh(score->myScore, shaders["ShaderForHeart"], modelMatrix, 0, 10, NULL);
}

// Coliziunea dintre sfera si platforma
bool Tema3::isCollision(float box_minX, float box_minY, float box_minZ, float box_maxX, float box_maxY, float box_maxZ,
	float point_x, float point_y, float point_z) {
	return (point_x >= box_minX && point_x <= box_maxX) &&
		(point_y >= box_minY && point_y <= box_maxY) &&
		(point_z >= box_minZ && point_z <= box_maxZ);
}

// Coliziunea dintre sfera si obstacole
bool Tema3::obstaclesCollision(float boxMinX, float boxMinY, float boxMinZ, float boxMaxX, float boxMaxY, float boxMaxZ)
{
	auto x = max(boxMinX, min(playerX, boxMaxX));
	auto y = max(boxMinY, min(playerY, boxMaxY));
	auto z = max(boxMinZ, min(playerZ, boxMaxZ));

	auto distance = sqrt((x - playerX) * (x - playerX) +
		(y - playerY) * (y - playerY) +
		(z - playerZ) * (z - playerZ));

	return distance < 0.25f;
}

bool Tema3::goodCollision(float x, float y, float z) {
	auto distance = sqrt((playerX - x) * (playerX - x) +
		(playerY - y) * (playerY - y) +
		(playerZ - z) * (playerZ - z));

	return distance < (0.25f + 0.25f);
}

void Tema3::showPlayer(int playerCollide) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(playerX, playerY, playerZ);
	modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
	RenderSimpleMesh(player->myPlayer, shaders["ShaderForPlayer"], modelMatrix, playerCollide, 3, NULL);
}

void Tema3::showFuelBar() {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(coloredRectangleX, coloredRectangleY, 0);
	modelMatrix *= Transform3D::Scale(fuel, 1, 1);
	RenderSimpleMesh(myFuelBar->coloredRectangle, shaders["ShaderForFuel"], modelMatrix, 0, 8, NULL);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(whiteRectangleX, whiteRectangleY, 0);
	RenderSimpleMesh(myFuelBar->whiteRectangle, shaders["ShaderForFuel"], modelMatrix, 0, 9, NULL);
}

void Tema3::showHeart() {
	for (float i = 0; i < nrLives; i = i + 1.0f) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.8 - i * 0.1, 0.6, 0);
		modelMatrix *= Transform3D::Scale(0.03, 0.06, 0);
		RenderSimpleMesh(heart->myHeart, shaders["ShaderForHeart"], modelMatrix, 0, 1, NULL);
	}
}

void Tema3::showBuilding(Cube blocks[3][MAX_BLOCKS]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < MAX_BLOCKS; ++j) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(blocks[i][j].x, 4, blocks[i][j].z);
			modelMatrix *= Transform3D::Scale(0.5f, 5, 0.5f);
			if (blocks[i][j].type == 0) {
				RenderSimpleMesh(building->myBuilding, shaders["ShaderForBuilding"], modelMatrix, 0, 1, mapTextures["building2"]);
			}
			else {
				RenderSimpleMesh(building->myBuilding, shaders["ShaderForBuilding"], modelMatrix, 0, 1, mapTextures["building1"]);
			}
		}
	}
}

void Tema3::showSnowman(Cube snowmans[MAX_SNOWMANS]) {
	for (int i = 0; i < MAX_SNOWMANS; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(snowmans[i].x, -0.23f, snowmans[i].z);
		modelMatrix *= Transform3D::Scale(1, 2, 1);
		RenderSimpleMesh(quad->myQuad, shaders["ShaderForQuad"], modelMatrix, 1, 1, mapTextures["snowman"]);
	}
}

void Tema3::showSantaClaus(float deltaTimeSeconds) {
	if (santaCollide == 0 && goodCollision(santaClausX, santaClausY, santaClausZ)) {
		scoreScale += 2 * deltaTimeSeconds;
		santaCollide = 1;
	}

	if (santaClausZ < 0) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(santaClausX, santaClausY, santaClausZ);
		modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
		RenderSimpleMesh(santaClaus->mySantaClaus, shaders["ShaderForSantaClaus"], modelMatrix, santaCollide, 3, mapTextures["santaClaus"]);
		platformOccupied[-santaClausZ] = 1;
	}
	else {
		santaClausX = -1.8f + rand() % TOTAL_ROWS;
		santaClausY = 0.5f;
		float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		// Caut o platforma goala pe care sa plasez obiectul
		while (platformOccupied[-j] == 1) {
			j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
		}
		platformOccupied[-j] = 1;
		santaClausZ = j;
		santaCollide = 0;
	}
}

void Tema3::showBackground() {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Scale(300, 300, 300);
	RenderSimpleMesh(meshes["box"], shaders["ShaderForBackground"], modelMatrix, 0, 0, mapTextures["sky"]);
}

void Tema3::showGround() {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-1, -1, -2);
	modelMatrix *= Transform3D::Scale(100, 0, 100);
	RenderSimpleMesh(meshes["box"], shaders["ShaderForGround"], modelMatrix, 0, 0, mapTextures["snow"]);
}

void Tema3::showGift(float deltaTimeSeconds) {
	for (int i = 0; i < MAX_SCORE_ELEMENTS; ++i) {
		if (gifts[i].isHitten == 0 && obstaclesCollision(gifts[i].x - 0.25f, 0.1f, gifts[i].z - 0.25f, gifts[i].x + 0.25f, 0.6f, gifts[i].z + 0.25f)) {
			gifts[i].isHitten = 1;
			scoreScale += 2 * deltaTimeSeconds;
		}
		if (gifts[i].z < 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(gifts[i].x, 0.35f, gifts[i].z);
			angularStep += 30 * deltaTimeSeconds;
			modelMatrix *= Transform3D::RotateOY(RADIANS(angularStep));
			modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
			RenderSimpleMesh(gift->myGift, shaders["ShaderForGift"], modelMatrix, 0, 1, mapTextures["gift"]);
			platformOccupied[-gifts[i].z] = 1;
		}
		else {
			float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
			// Caut o platforma goala pe care sa plasez obiectul
			while (platformOccupied[-j] == 1) {
				j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
			}
			platformOccupied[-j] = 1;
			gifts[i].z = j;
			gifts[i].initialZ = j;
			gifts[i].x = -1.8f + rand() % TOTAL_ROWS;
			gifts[i].isHitten = 0;
			gifts[i].color = 1;
		}
	}
}

void Tema3::showCubeLoseLife() {
	for (int i = 0; i < MAX_CUBES_FOR_LOSING_LIFE; ++i) {
		if (cubesForLosingLife[i].isHitten == 0 && obstaclesCollision(cubesForLosingLife[i].x - 0.25f, 0.1f, cubesForLosingLife[i].z - 0.25f, cubesForLosingLife[i].x + 0.25f, 0.6f, cubesForLosingLife[i].z + 0.25f)) {
			nrLives--;
			cubesForLosingLife[i].isHitten = 1;
		}
		if (cubesForLosingLife[i].z < 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(cubesForLosingLife[i].x, 0.35f, cubesForLosingLife[i].z);
			modelMatrix *= Transform3D::RotateOY(RADIANS(45));
			modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
			RenderSimpleMesh(cubeLoseLife->myCubeLoseLife, shaders["ShaderForCubeLoseLife"], modelMatrix, 0, cubesForLosingLife[i].color, mapTextures["warning"]);
			platformOccupied[-cubesForLosingLife[i].z] = 1;
		}
		else {
			//platformOccupied[-cubesForLosingLife[i].initialZ] = 0;
			float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
			// Caut o platforma goala pe care sa plasez obiectul
			while (platformOccupied[-j] == 1) {
				j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
			}
			platformOccupied[-j] = 1;
			cubesForLosingLife[i].z = j;
			cubesForLosingLife[i].initialZ = j;
			cubesForLosingLife[i].x = -1.8f + rand() % TOTAL_ROWS;
			cubesForLosingLife[i].isHitten = 0;
			cubesForLosingLife[i].color = 1;
		}

	}
}

void Tema3::showCubeKiller() {
	for (int i = 0; i < MAX_CUBES_KILLER; ++i) {
		if (cubesKiller[i].isHitten == 0 && obstaclesCollision(cubesKiller[i].x - 0.25f, 0.1f, cubesKiller[i].z - 0.25f, cubesKiller[i].x + 0.25f, 0.6f, cubesKiller[i].z + 0.25f)) {
			cout << "Ai fost doborat de obstacolul ucigator!" << endl;
			cubesKiller[i].isHitten = 1;
			exit(0);
		}
		if (cubesKiller[i].z < 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(cubesKiller[i].x, 0.35f, cubesKiller[i].z);
			modelMatrix *= Transform3D::RotateOY(RADIANS(45));
			modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
			RenderSimpleMesh(cubeKiller->myCubeKiller, shaders["ShaderForCubeKiller"], modelMatrix, 0, cubesKiller[i].color, mapTextures["danger"]);
			platformOccupied[-cubesKiller[i].z] = 1;
		}
		else {
			float j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
			// Caut o platforma goala pe care sa plasez obiectul
			while (platformOccupied[-j] == 1) {
				j = (-1) * (rand() % TOTAL_COLUMNS) - 15;
			}
			platformOccupied[-j] = 1;
			cubesKiller[i].z = j;
			cubesKiller[i].initialZ = j;
			cubesKiller[i].x = -1.8f + rand() % TOTAL_ROWS;
			cubesKiller[i].isHitten = 0;
			cubesKiller[i].color = 1;
		}

	}
}

void Tema3::showPlatforms(float deltaTimeSeconds) {
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

					//Platforma roz
					if (cubes[i][j].color == 6) {
						if (nrLives < 3.0f) {
							nrLives += 0.1f;
						}
					}

					//Platforma bleu
					if (cubes[i][j].color == 7) {
						nrLives -= 0.1f;
					}

				}
				else {
					cubes[i][j].isHitten = 0;
				}
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix *= Transform3D::Translate(cubes[i][j].x, 0, cubes[i][j].z);
				modelMatrix *= Transform3D::Scale(1, 0.2f, 1);

				RenderSimpleMesh(platform->myPlatform, shaders["ShaderForPlatform"], modelMatrix, cubes[i][j].isHitten, cubes[i][j].color, mapTextures["snowflakes"]);
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

void Tema3::renderSnowmansAgain(Cube snowmans[MAX_SNOWMANS]) {
	if (snowmans[MAX_SNOWMANS / 2].z > 0) {
		snowmans[0].z = snowmans[MAX_SNOWMANS - 1].z - 15;
		for (int j = 1; j <= MAX_SNOWMANS / 2; ++j) {
			snowmans[j].z = snowmans[j - 1].z - 15;
		}

	}
	else if (snowmans[MAX_SNOWMANS - 1].z > 0) {
		for (int j = MAX_SNOWMANS - MAX_SNOWMANS / 2; j < MAX_SNOWMANS; ++j) {
			snowmans[j].z = snowmans[j - 1].z - 15;
		}
	}
}

void Tema3::renderBuildingsAgain(Cube blocks[3][MAX_BLOCKS]) {
	if (blocks[0][MAX_BLOCKS / 2].z > 0) {
		for (int i = 0; i < 3; ++i) {
			blocks[i][0].z = blocks[i][MAX_BLOCKS - 1].z - 1;
			blocks[i][0].type = rand() % 2;
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 1; j <= MAX_BLOCKS / 2; ++j) {
				blocks[i][j].z = blocks[i][j - 1].z - 1;
				blocks[i][j].type = rand() % 2;
			}
		}

	}
	else if (blocks[0][MAX_BLOCKS - 1].z > 0) {
		for (int i = 0; i < 3; ++i) {
			for (int j = MAX_BLOCKS - MAX_BLOCKS / 2; j < MAX_BLOCKS; ++j) {
				blocks[i][j].z = blocks[i][j - 1].z - 1;
			}
		}
	}
}

void Tema3::renderPlatformsAgain()
{
	if (cubes[0][TOTAL_COLUMNS / 2].z > 0) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			cubes[i][0].z = cubes[i][TOTAL_COLUMNS - 1].z - 1;
			if (rand() % 5 == 0) {
				cubes[i][0].color = rand() % 8;
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
					cubes[i][j].color = rand() % 8;
				}
				else {
					cubes[i][j].color = 5;
				}
				cubes[i][j].isHitten = 0;
			}
		}

	}
	else if (cubes[0][TOTAL_COLUMNS - 1].z > 0) {
		for (int i = 0; i < TOTAL_ROWS; ++i) {
			for (int j = TOTAL_COLUMNS - TOTAL_COLUMNS / 2; j < TOTAL_COLUMNS; ++j) {
				cubes[i][j].z = cubes[i][j - 1].z - 1;
			}
		}
	}
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int isHitten, int color, Texture2D* texture1)
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

	if (color != 9 && color != 8) {
		auto location_view = glGetUniformLocation(shader->GetProgramID(), "View");
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		auto location_projection = glGetUniformLocation(shader->program, "Projection");
		glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		auto location_collide = glGetUniformLocation(shader->GetProgramID(), "Collide");
		glUniform1i(location_collide, isHitten);
	}

	if (texture1)
	{
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
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

void Tema3::OnKeyPress(int key, int mods)
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

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
