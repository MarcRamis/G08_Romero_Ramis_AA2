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

	enum class Cell {NONE, WALL, PLAYER, POWERUP, BOMB, COUNT};
	
private:
	
	std::vector<std::vector<Cell>> grid;
	std::vector<Wall> wall;
	std::vector<Player> player;

public:
	Map();
	~Map();
	
	std::vector<Wall> *GetWall() { return &wall; };
	std::vector<Player> *GetPlayer() { return &player; };
	std::vector<std::vector<Cell>>* GetGrid() { return &grid; };

	inline const bool IsNotDestructibleWall(const VEC2, const int);
	inline const bool IsDestructibleWall(const VEC2, const int);
	inline const bool IsPlayer(const VEC2, const int);
};