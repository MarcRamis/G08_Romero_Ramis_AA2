#pragma once

#include "Renderer.h"
#include "Types.h"

class Wall
{
public:
	bool destructible, destructed;

private:
	RECT position;
	RECT frame;
	
	int initCol, lastCol;
	int initRow, lastRow;
	float frameCount = 0;



public:
	
	Wall();
	~Wall();

	inline const void SetPosition(RECT _position) { position = _position; };
	inline const RECT *GetPosition() { return &position; };
	inline const RECT* GetFrame() const { return &frame; };

	void SetDestructible(bool _destructible) { destructible = _destructible; };
	inline const bool *GetDestructible() { return &destructible; };

	void Update();
	void SetValues(VEC2, bool);
	void Draw();
	
private:
	
	void UpdateSprite();
};