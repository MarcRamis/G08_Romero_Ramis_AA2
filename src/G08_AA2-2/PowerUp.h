#pragma once

#include "Renderer.h"
#include "Types.h"

class PowerUp
{
public:

	enum class EPowerUpType { NONE, SKATES, HELMET, COUNT };

private:
	RECT position;
	RECT frame;
	EPowerUpType type;

	int initCol, lastCol;
	int initRow, lastRow;
public:
	
	PowerUp();
	~PowerUp();

	inline const void SetPosition(RECT _position) { position = _position; };
	inline const RECT* GetPosition() { return &position; };
	inline const RECT* GetFrame() const { return &frame; };

	void SetValues(VEC2, EPowerUpType);
};