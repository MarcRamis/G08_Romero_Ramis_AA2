#pragma once
#include "Map.h"
//#include "Bomb.h"
#include "Collisions.h"

class Level
{
public:
	enum class ELevelType {NONE, LEVEL1, LEVEL2};
private:

	ELevelType type;
	std::vector<Map*> map;

	std::vector<Player*> player;
	std::vector<Wall*> walls;
	Bomb bomb1;
	Bomb bomb2;
	
	RECT pl1_life_frame;
	RECT pl1_life_position;
	RECT pl2_life_frame;
	RECT pl2_life_position;

public:
	Level(ELevelType);
	~Level();
	
	ELevelType GetType() { return type; };
	std::vector<Map*> GetMap() { return map; };
	std::vector<Player*> GetPlayer() { return player; };
	
	void Update(ELevelType);
	void Draw(ELevelType);

private:
	
	void InitLevelScene(ELevelType _type);

	void AddPlayer(VEC2 pos, Player::EPlayerType type);
	void AddWall(VEC2 pos, bool des);
	void AddBomb(VEC2 pos, Player::EPlayerType type);
};