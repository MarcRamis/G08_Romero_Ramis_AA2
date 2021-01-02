#pragma once

#include "Renderer.h"
#include "Types.h"

class Wall
{
private:
	RECT position;
	RECT frame;
	bool destructible;

	int initCol, lastCol;
	int initRow, lastRow;

public:
	
	Wall();
	~Wall();

	void SetPosition(RECT _position) { position = _position; };
	inline const RECT *GetPosition() { return &position; };
	
	void SetDestructible(bool _destructible) { destructible = _destructible; };
	inline const bool *GetDestructibleWall() { return &destructible; };

	void Update();

private:
	
	void UpdateSprite();
	void SetSprite(int textWidth, int textHeight, int nCol, int nRow);
};