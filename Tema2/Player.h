#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Player {
public:
	Player();

	~Player();

	Mesh* myPlayer;
};