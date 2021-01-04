#pragma once

#include "Scene.h"
#include "Map.h"
#include "PowerUp.h"

class Play : public Scene
{
private:
	
	std::vector<Map> levels;

public:
	Play();
	~Play();

	void Draw();
	void Update();

private:
	void ReadMap();
};