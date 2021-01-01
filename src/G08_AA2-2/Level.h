#pragma once

#include "Map.h"
#include "Player.h"

class Level
{
private:

	std::vector<Wall> wall;
	std::vector<Player> player;

public:
	Level();
	~Level();

	std::vector<Wall> *GetWall() { return &wall; };
	std::vector<Player> *GetPlayer() { return &player; };
};