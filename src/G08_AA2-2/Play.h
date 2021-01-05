#pragma once

#include "Scene.h"
#include "Map.h"
#include "PowerUp.h"

class Play : public Scene
{
private:
	
	std::vector<Player*> players;
	std::vector<Map> levels;

public:
	Play();
	~Play();

	void Draw();
	void Update();

private:
	void ReadMap();
	
	void AddPlayer(int, int, VEC2, Player::EPlayerType type);
};