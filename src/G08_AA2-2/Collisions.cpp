#include "Collisions.h"

bool Collisions::ExistCollision(VEC2 p1, RECT r1)
{
	return (p1.x > r1.x && p1.x < (r1.x + r1.w)) && (p1.y > r1.y && p1.y < (r1.y + r1.h));
}

bool Collisions::ExistCollision(RECT r1, RECT r2)
{
	return ExistCollision(VEC2(r1.x, r1.y), r2) ||
		ExistCollision(VEC2(r1.x + r1.w, r1.y), r2) ||
		ExistCollision(VEC2(r1.x + r1.w, r1.y + r1.h), r2) ||
		ExistCollision(VEC2(r1.x, r1.y + r1.h), r2);
}