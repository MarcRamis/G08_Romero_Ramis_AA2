#pragma once

#include "Scene.h"
#include "Map.h"
#include "PowerUp.h"

class Play : public Scene
{
private:
	
	std::vector<Player*> players;
	std::vector<Wall*> walls;
	std::vector<PowerUp*> powerUps;

	std::vector<Map*> levels;

public:
	Play();
	~Play();

	void Draw();
	void Update();

private:
	void ReadMap();
	
	void AddPlayer(VEC2, Player::EPlayerType);
	void AddWall(VEC2, bool _destructible);
	void AddBomb(VEC2, Player::EPlayerType type);
	void AddPowerUp(VEC2, PowerUp::EPowerUpType);
};