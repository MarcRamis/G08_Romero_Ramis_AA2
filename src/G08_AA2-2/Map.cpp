#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

inline const bool Map::IsNotDestructibleWall(const VEC2 gridPos, const int wallIt)
{
	return grid[gridPos.x][gridPos.y] == int(wall.at(wallIt).GetPosition()) && !wall.at(wallIt).GetDestructibleWall();
}

inline const bool Map::IsDestructibleWall(const VEC2 gridPos, const int wallIt)
{
	return grid[gridPos.x][gridPos.y] == int(wall.at(wallIt).GetPosition()) && wall.at(wallIt).GetDestructibleWall();
}

inline const bool Map::IsPlayer(const VEC2 gridPos, const int playerIt)
{
	return grid[gridPos.x][gridPos.y] == int(player.at(playerIt).GetPosition());
}