#pragma once
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "PowerUp.h"

enum class Level { NONE, LEVEL1, LEVEL2, COUNT };

class Play : public Scene
{
private:

public:
	Play();
	~Play();

	void Draw();
};