#pragma once

#include "Wall.h"

class Map
{
private:

	std::vector<Wall> wall;

public:
	
	std::vector<Wall> GetWall() { return wall; };
};