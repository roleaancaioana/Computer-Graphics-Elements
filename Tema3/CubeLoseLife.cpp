#include "CubeLoseLife.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

CubeLoseLife::CubeLoseLife() {
	myCubeLoseLife = new Mesh("box");
	myCubeLoseLife->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Box.obj");
}

CubeLoseLife::~CubeLoseLife() {
}

