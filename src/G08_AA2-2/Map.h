#pragma once
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <sstream>

#include "Wall.h"
#include "Player.h"

#include "PowerUp.h"
#include "Collisions.h"
#include "Utils.h"

#include "Renderer.h"

class Map
{
public:
	
	//enum class Cell {NONE, WALLINDES, WALLDES, POWERUP, BOMB, PL1, PL2, COUNT};
	enum class ELevelType { NONE, LEVEL1, LEVEL2 };
private:
	
	//std::vector<std::vector<Cell>> grid;
	ELevelType type;
	std::vector<Player> player;
	std::vector<Wall> wall;

public:
	Map(ELevelType);
	~Map();
	
	std::vector<Wall> *GetWall() { return &wall; };
	std::vector<Player> *GetPlayer() { return &player; };
	//std::vector<std::vector<Cell>>* GetGrid() { return &grid; };

	void Draw();

	//bool isDestructibleCell(VEC2 pos, Cell cell) 
	//{
	//	if(grid[pos.x][pos.y] == cell) return true;

	//	else return false;
	//}
	//void SetCell(VEC2 _pos, Cell _cell) { grid[_pos.x][_pos.y] = _cell; };
	void AddPlayer(VEC2, Player::EPlayerType);
	void AddWall(VEC2 pos);
};