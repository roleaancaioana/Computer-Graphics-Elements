#include "Platform.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Platform::Platform() {
	this->myPlatform = new Mesh("platform");
	myPlatform->LoadMesh(RESOURCE_PATH::MODELS + "Primitives","Box.obj");
}

Platform::~Platform() {

}


