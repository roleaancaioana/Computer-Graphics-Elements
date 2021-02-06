#include "Gift.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Gift::Gift() {
	myGift = new Mesh("box");
	myGift->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Box.obj");
}

Gift::~Gift() {
}

