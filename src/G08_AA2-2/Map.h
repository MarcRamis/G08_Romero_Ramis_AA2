#pragma once
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <sstream>

#include "Wall.h"
#include "Player.h"

#include "Renderer.h"

class Map
{
public:
	
	enum class Cell {NONE, WALL, WALLINDES, WALLDES, POWERUP, BOMB, PL1, PL2, COUNT};
	
private:

	std::vector<std::vector<Cell>> grid;
	std::vector<Wall> wall;
	std::vector<Player> _player;

public:
	Map();
	~Map();
	
	std::vector<Wall> *GetWall() { return &wall; };
	std::vector<Player> *GetPlayer() { return &_player; };
	std::vector<std::vector<Cell>>* GetGrid() { return &grid; };
};