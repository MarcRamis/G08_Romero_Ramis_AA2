#pragma once

#include "Scene.h"
#include "Level.h"

class Play : public Scene
{
private:
	
	//std::vector<Player*> players;
	
	//std::vector<Wall*> walls;
	//std::vector<PowerUp*> powerUps;
	//std::vector<Map*> levels;

	Level *level;

public:
	Play(Level::ELevelType);
	~Play();

	void Draw();
	void Update();

private:
	
	//void AddPowerUp(VEC2, PowerUp::EPowerUpType);
};