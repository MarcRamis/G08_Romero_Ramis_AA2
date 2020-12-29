#pragma once

#include "Map.h"
#include "Player.h"

class Level
{
private:
	
	//VEC2 *grid;

	Map *map;
	std::vector<Player>* player(2);

public:
	//VEC2 *GetGrid() { return grid; }
	//void *SetGrid(VEC2 _grid) { grid = _grid; }
	
	Map* GetMap() { return map; };
	std::vector<Player>* GetPlayer() { return player; };
};