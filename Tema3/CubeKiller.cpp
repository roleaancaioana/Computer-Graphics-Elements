#include "CubeKiller.h"
#include <iostream>
#include <Core/Engine.h>

using namespace std;

CubeKiller::CubeKiller() {
	myCubeKiller = new Mesh("box");
	myCubeKiller->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Box.obj");
}

CubeKiller::~CubeKiller() {
}

