#include "Tema1.h"
#include "Transforms.h"
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <math.h>

#include <Core/Engine.h>

using namespace std;

Tema1::Tema1()
{
	angleShuriken = 0;
	oldAngleArrow = 0.f;
	angleArrow = 0.f;
	goodBalloon = new Balloon(glm::vec3(1, 0, 0));
	badBalloon = new Balloon(glm::vec3(1, 1, 0));
	goodHittenBalloon = new HittenBalloon(glm::vec3(1, 0, 0));
	badHittenBalloon = new HittenBalloon(glm::vec3(1, 1, 0));
	myBow = new Bow();
	myShuriken = new Shuriken();
	powerRectangle = new PowerRectangle();
	newLife = new NewLife();
	myScore = new Score();
	hittenLife = 0;
	moveArrowAndBow = false;
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	srand((unsigned int) time(NULL));
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	for (int i = 0; i < TOTAL_BALLOONS; ++i) {
		hittenBalloonY.push_back(0);
		hitten.push_back(0); //baloanele nu sunt lovite initial
		balloonX.push_back((float) (rand() % 600 + 600));
		balloonY.push_back((float)(-rand() % 1000));
		if (i < TOTAL_BALLOONS / 2) {
			type.push_back(1);
		}
		else {
			type.push_back(rand() % 2);
		}
	}

	for (int i = 0; i < TOTAL_SHURIKENS; ++i) {
		shurikenX.push_back((float)(rand() % 700 + 1280));
		shurikenY.push_back((float)(rand() % 700));
		hittenShuriken.push_back(0);
		hittenShurikenX.push_back(0);
	}
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.7f, 0.8f, 0.7f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	if (isFinalGame == true) {
		cout << "Ai pierdut! Scor:" << scoreScale << endl;
		exit(0);
	}
	else {
		showBow(deltaTimeSeconds);
		showPower(deltaTimeSeconds);

		// Daca un shuriken iese din scena, il voi randa iar
		for (int i = 0; i < TOTAL_SHURIKENS; ++i) {
			if (shurikenX[i] <= 0 || shurikenY[i] < 0) {
				speedShuriken += 10;
				hittenShuriken[i] = 0;
				shurikenX[i] = (float) (rand() % 700 + 1280);
				shurikenY[i] = (float) (rand() % 700);
			}
		}

		// Daca sageata iese din scena, o voi aduce din nou in pozitia initiala
		if (arrowX > 1280 || arrowY > 720) {
			goArrow = false;
			arrowX = bowX;
			arrowY = bowY;
		}

		if (goArrow == true) {
			arrowX += 13 * speedArrow * cos(oldAngleArrow) * deltaTimeSeconds;
			arrowY += 13 * speedArrow * sin(oldAngleArrow) * deltaTimeSeconds;
		}

		// Stelutele trebuie sa se miste pe axa OX la fiecare frame
		for (int i = 0; i < TOTAL_SHURIKENS; ++i) {
			shurikenX[i] -= deltaTimeSeconds * speedShuriken;
		}

		if (hittenLife == 0) {
			newLifeX -= deltaTimeSeconds * speedNewLife;
			newLifeY += deltaTimeSeconds * speedNewLife;
		}

		if (newLifeY > 720) {
			hittenLife = 0;
			newLifeY = 0;
			newLifeX = 1280;
		}

		if (newLifeY < 0) {
			hittenLife = 0;
			newLifeY = 0;
			newLifeX = 1280;
		}

		// Coliziunea dintre sageata si obiectul care da o viata in plus
		if (hittenLife == 0 && goArrow == true) {
			if (sqrt((arrowX + 150 - newLifeX) * (arrowX + 150 - newLifeX) + (arrowY + 5 - newLifeY) * (arrowY + 5 - newLifeY)) < 30) {
				hittenLife = 1;
				if (lives < 3) {
					lives++;
					cout << "Ai castigat o viata!" << endl;
				}
			}
		}

		if (hittenLife == 1) {
			speedNewLife++;
			newLifeY -= speedNewLife * deltaTimeSeconds;
		}

		showNewLife(deltaTimeSeconds);

		for (int i = 0; i < TOTAL_SHURIKENS; ++i) {
			if (hittenShuriken[i] == 1) {
				shurikenY[i] -= speedShuriken * deltaTimeSeconds;
			}
		}

		// Coliziunea dintre shuriken si sageata
		for (int i = 0; i < TOTAL_SHURIKENS; ++i) {
			if (hittenShuriken[i] == 0 && goArrow == true) {
				if (sqrt((arrowX + 150 - shurikenX[i]) * (arrowX + 150 - shurikenX[i]) + (arrowY + 5 - shurikenY[i]) * (arrowY + 5 - shurikenY[i])) < 42.3) {
					hittenShurikenX[i] = shurikenX[i];
					hittenShuriken[i] = 1;
					scoreScale += 30;
					cout << "Scorul este: " << scoreScale << endl;;
				}
			}
		}

		for (int i = 0; i < TOTAL_SHURIKENS; ++i) {
			showShuriken(i, deltaTimeSeconds);
		}

		// Coliziunea dintre shuriken si arc
		for (int i = 0; i < TOTAL_SHURIKENS; i++) {
			if (hittenShuriken[i] == 0) {
				if (sqrt((bowX - (shurikenX[i] - 30)) * (bowX - (shurikenX[i] - 30)) + (bowY - (shurikenY[i] - 30)) * (bowY - (shurikenY[i] - 30))) < 105) {
					lives--;
					hittenShurikenX[i] = shurikenX[i];
					hittenShuriken[i] = 1;
				}
			}
		}

		// Baloanele trebuie sa urce pe axa OY, prin urmare trebuie sa modific componenta Y la fiecare frame
		for (int i = 0; i < TOTAL_BALLOONS; ++i) {
			if (hitten[i] == 0) {
				balloonY[i] += deltaTimeSeconds * speedBalloon;
			}
		}

		// Daca balonul s-a spart, trebuie sa coboare pe axa Oy
		for (int i = 0; i < TOTAL_BALLOONS; ++i) {
			if (hitten[i] == 1) {
				hittenBalloonY[i] -= speedBalloon * deltaTimeSeconds;
			}
		}

		// Coliziunea dintre baloane si sageata
		for (int i = 0; i < TOTAL_BALLOONS; ++i) {
			if (hitten[i] == 0) {
				if (sqrt((arrowX + 150 - balloonX[i]) * (arrowX + 150 - balloonX[i]) + (arrowY + 5 - balloonY[i]) * (arrowY + 5 - balloonY[i])) < 52) {
					hitten[i] = 1;
					hittenBalloonY[i] = balloonY[i];
					if (type[i] == 1) {
						scoreScale += 20;
						cout << "Scorul este: " << scoreScale << endl;
					}
					else {
						scoreScale -= 40;
						cout << "Scorul este: " << scoreScale << endl;
					}
				}
			}
		}

		for (int i = 0; i < TOTAL_BALLOONS; ++i) {
			if (hittenBalloonY[i] < 0) {
				hittenBalloonY[i] = 0;
				balloonX[i] = (float) (rand() % 600 + 600);
				balloonY[i] = (float) (-100);
				hitten[i] = 0;
			}
		}

		// Daca un balon iese din scena, il voi randa iar
		for (int i = 0; i < TOTAL_BALLOONS; ++i) {
			if (balloonY[i] >= 800) {
				speedBalloon += 10;
				balloonX[i] = (float) (rand() % 600 + 600);
				balloonY[i] = 0;
				hitten[i] = 0;
			}
		}

		for (int i = 0; i < TOTAL_BALLOONS; ++i) {
			showBalloons(i, deltaTimeSeconds, type[i]);
		}
		showScore(deltaTimeSeconds);

		if (lives == 0) {
			isFinalGame = true;
		}
	}

}

void Tema1::showScore(float deltaTimeSeconds) {
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::myTranslate(30, 700);
	modelMatrix *= Transform2D::myScale(scoreScale / 4, 1);
	RenderMesh2D(myScore->score, shaders["VertexColor"], modelMatrix);
}

void Tema1::showBalloons(int id, float deltaTimeSeconds, int type) {
	if (hitten[id] == 0) {
		if (type == 1) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::myTranslate(balloonX[id], balloonY[id] - 52);
			RenderMesh2D(goodBalloon->lineBalloon, shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::myTranslate(balloonX[id], balloonY[id]);
			modelMatrix *= Transform2D::myScale(0.7f, 1.3f);
			RenderMesh2D(goodBalloon->circleBalloon, shaders["VertexColor"], modelMatrix);
		}
		else if (type == 0) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::myTranslate(balloonX[id], balloonY[id] - 52);
			RenderMesh2D(badBalloon->lineBalloon, shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::myTranslate(balloonX[id], balloonY[id]);
			modelMatrix *= Transform2D::myScale(0.7f, 1.3f);
			RenderMesh2D(badBalloon->circleBalloon, shaders["VertexColor"], modelMatrix);
		}
	}
	else if (type == 0) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::myTranslate(balloonX[id], hittenBalloonY[id]);
		modelMatrix *= Transform2D::myScale(4, 4);
		RenderMesh2D(badHittenBalloon->balloon, shaders["VertexColor"], modelMatrix);
	}
	else if (type == 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::myTranslate(balloonX[id], hittenBalloonY[id]);
		modelMatrix *= Transform2D::myScale(4, 4);
		RenderMesh2D(goodHittenBalloon->balloon, shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::showNewLife(float deltaTimeSeconds) {
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::myTranslate(newLifeX, newLifeY);
	RenderMesh2D(newLife->life, shaders["VertexColor"], modelMatrix);
}

void Tema1::showBow(float deltaTimeSeconds) {
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::myTranslate(bowX, bowY);
	modelMatrix *= Transform2D::myRotate(1.57f);
	if (moveArrowAndBow == true) {
		modelMatrix *= Transform2D::myRotate(angleArrow);
	}
	RenderMesh2D(myBow->bow, shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::myTranslate(arrowX, arrowY);
	// Sageata se va roti fie odata cu arcul, fie dupa unghiul pe care l-a avut atunci cand s-a apasat pe mouse
	if (goArrow == true) {
		modelMatrix *= Transform2D::myRotate(oldAngleArrow); // sageata a plecat din arc, deci are alt unghi de rotatie
	} else if (moveArrowAndBow == true) {
		modelMatrix *= Transform2D::myRotate(angleArrow); // sageata se roteste odata cu arcul
	}
	RenderMesh2D(myBow->arrow, shaders["VertexColor"], modelMatrix);
}

void Tema1::showShuriken(int id, float deltaTimeSeconds) {
	if (hittenShuriken[id] == 1) {
		angleShuriken += deltaTimeSeconds * 90;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::myTranslate(hittenShurikenX[id], shurikenY[id]);
		modelMatrix *= Transform2D::myRotate(angleShuriken);
		RenderMesh2D(myShuriken->star, shaders["VertexColor"], modelMatrix);
	}
	else {
		angleShuriken += deltaTimeSeconds * 90;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::myTranslate(shurikenX[id], shurikenY[id]);
		modelMatrix *= Transform2D::myRotate(angleShuriken);
		RenderMesh2D(myShuriken->star, shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::showPower(float deltaTimeSeconds) {
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::myTranslate(30, 200);
	modelMatrix *= Transform2D::myScale(scalePower / 2, 1);
	RenderMesh2D(powerRectangle->rectangle, shaders["VertexColor"], modelMatrix);
}

void Tema1::FrameEnd()
{

}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		bowY += 200 * deltaTime;
		arrowY += 200 * deltaTime;
		tempMouseY += 200 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		bowY -= 200 * deltaTime;
		arrowY -= 200 * deltaTime;
		tempMouseY -= 200 * deltaTime;
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		oldAngleArrow = angleArrow;
		if (scalePower <= MAX_POWER_SPEED) {
			scalePower += 2;
			speedArrow = (int) (scalePower);
		}
	}

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	moveArrowAndBow = true;
	float auxArrowY = (float)arrowY - tempMouseY;
	float x = (float)mouseX - (float)arrowX;

	if (x < 0) {
		x *= -1;
	}

	angleArrow = atan(((float)auxArrowY - (float)mouseY - tempMouseY)/ x); // unghiul pentru sageata atunci cand e in bow
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		goArrow = true;
		scalePower = 1;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
