#include "Player.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Player::Player() {
	myPlayer = new Mesh("sphere");
	myPlayer->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
}

Player::~Player() {
}

