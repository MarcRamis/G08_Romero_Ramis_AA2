#pragma once

#include "Types.h"

class Wall
{
private:
	VEC2 position;
	bool destructible;

public:

	void SetPos(VEC2 _position) { position.x = _position.x; position.y = position.y; };
	VEC2 GetPos() { return position; };

	void SetDestructibleWall(bool _destructible) { destructible = _destructible; };
	bool GetDestructibleWall() { return destructible; };
};