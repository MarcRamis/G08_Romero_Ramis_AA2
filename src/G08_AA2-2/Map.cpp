#include "Map.h"

Map::Map()
{
	grid.resize(MAP_ROWS);
	for (int i = 0; i < grid.size(); i++)
		grid.at(i).resize(MAP_COLS);

	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int j = 0; j < MAP_COLS; j++)
		{
			grid[i][j] = Cell::NONE;
		}
	}
}

Map::~Map() 
{
	for (int i = 0; i < grid[i].size(); i++)
		grid[i].clear();
	
	grid.clear();
}
