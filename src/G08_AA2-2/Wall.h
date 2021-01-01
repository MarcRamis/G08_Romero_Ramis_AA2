#pragma once

#include "Types.h"

class Wall
{
private:
	VEC2 position;
	bool destructible;

public:
	
	Wall() : position(VEC2(0,0)), destructible(false) {};
	Wall(VEC2 _pos, bool _destr) : position(_pos), destructible(_destr) {};
	
	void SetPosition(VEC2 _position) { position = _position; };
	inline const VEC2 *GetPosition() { return &position; };
	
	void SetDestructible(bool _destructible) { destructible = _destructible; };
	inline const bool *GetDestructibleWall() { return &destructible; };
};