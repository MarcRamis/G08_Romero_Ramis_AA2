#pragma once

#include "Wall.h"

class Map
{
private:
	Wall *wall;

public:
	
	Wall* GetWall() { return wall; };
};