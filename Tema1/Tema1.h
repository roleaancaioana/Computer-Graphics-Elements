#pragma once
#include "Bow.h"
#include "Balloon.h"
#include "Shuriken.h"
#include "PowerRectangle.h"
#include "HittenBalloon.h"
#include "NewLife.h"
#include "Score.h"
#include <vector>
#include <Core/Engine.h>
#include <Component/SimpleScene.h>

#define TOTAL_SHURIKENS 2
#define TOTAL_BALLOONS 8
#define MAX_POWER_SPEED 150

using namespace std;
class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void showBalloons(int id, float deltaTimeSeconds, int type);
	void showShuriken(int id, float deltaTimeSeconds);
	void showBow(float deltaTimeSeconds);
	void showPower(float deltaTimeSeconds);
	void showScore(float deltaTimeSeconds);
	void showNewLife(float deltaTimeSeconds);

protected:
	Bow* myBow;
	Balloon* goodBalloon;
	Balloon* badBalloon;
	HittenBalloon* goodHittenBalloon;
	HittenBalloon* badHittenBalloon;
	NewLife* newLife;
	Score* myScore;
	Shuriken* myShuriken;
	glm::mat3 modelMatrix;
	vector<float> balloonX;
	vector<float> balloonY;
	vector<float> hittenBalloonY;
	vector<float> shurikenX;
	vector<float> shurikenY;
	vector<float> hittenShurikenX;
	vector<int> hitten;
	vector<int> hittenShuriken;
	vector<int> type;
	PowerRectangle *powerRectangle;
	int lives = 3;
	float scoreScale = 0;
	bool isFinalGame = false;
	bool moveArrowAndBow;
	bool goArrow = false;
	float speedBalloon = 200.0f;
	float speedShuriken = 200.0f;
	float scalePower = 1;
	int speedArrow = 0;
	float hittenLife;
	float angleArrow, oldAngleArrow;
	float tempMouseX = 0;
	float tempMouseY = 0;
	int counter = 0;
	float newLifeX = 1280;
	float newLifeY = 0;
	float arrowX = 200;
	float arrowY = 400;
	float bowX = 200;
	float bowY = 400;
	float speedNewLife = 200.0f;
	float angleShuriken;
};
