#pragma once

#include "Scene.h"
#include "Map.h"
#include "BoardRanking.h"

class Play : public Scene
{
private:

	Map *map;

	std::vector<Player*> player;
	std::vector<Wall*> walls;
	Bomb bomb1;
	Bomb bomb2;
	std::vector<Explosion*> explosionBomb1;
	std::vector<Explosion*> explosionBomb2;
	std::vector<PowerUp*>powerUps;

	RECT initPlayer1Pos;
	RECT initPlayer2Pos;

	RECT pl1_life_frame;
	RECT pl1_life_position;
	RECT pl2_life_frame;
	RECT pl2_life_position;

	bool onceExplPl1 = false;
	bool onceExplPl2 = false;

	float timeDown;
	
public:
	Play(Map::ELevelType);
	~Play();
	
	void Update(InputManager& input);
	void Draw();

	void AddPlayer(VEC2 pos, Player::EPlayerType type, int lives);
	void AddWall(VEC2 pos, bool des);
	void AddBomb(VEC2 pos, Player::EPlayerType type);
	void AddExplosion(VEC2 pos, Player::EPlayerType type);
	void AddPowerUp(VEC2 pos);
};