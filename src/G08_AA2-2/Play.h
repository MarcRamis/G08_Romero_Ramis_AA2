#pragma once

#include "Scene.h"
#include "Map.h"
#include "PowerUp.h"

class Play : public Scene
{
private:
	
	std::vector<Map> levels;

	VEC2 vP1SCTTemp;	
	VEC2 vP1SCTemp;		
	VEC2 vP2SCTemp;		
	VEC2 vP2SCTTemp;

public:
	Play();
	~Play();

	void Draw();

private:
	void ReadMap();
};