#include "SantaClaus.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

SantaClaus::SantaClaus() {
	mySantaClaus = new Mesh("sphere");
	mySantaClaus->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
}

SantaClaus::~SantaClaus() {
}

