#pragma once

#include "Renderer.h"
#include "Types.h"

class PowerUp
{
private:
	RECT position;
	RECT frame;
	bool destructible;

	int initCol, lastCol;
	int initRow, lastRow;
public:
};