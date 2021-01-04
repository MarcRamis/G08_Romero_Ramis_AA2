#pragma once

// ----- SIGHT
#include "InputManager.h"
#include "Audio.h"
#include "Renderer.h"

// ----- MODELS
#include "Collisions.h"
#include "Scene.h"
#include "Menu.h"
#include "Play.h"

#include "Utils.h"

enum class GameState { MENU, PLAY, RANKING, EXIT };

class Game
{
private:
	
	GameState gameState;
	std::vector<Scene*> scenes;
	
	Renderer *r = Renderer::GetInstance();
	InputManager *input = InputManager::GetInstance();
	Audio *au = Audio::GetInstance();
	
	//remaining play time
	float timeDown;		
	float minTimeDown;	
	float secTimeDown;	
				
	//player scores		
	int scorePlayer1;	
	int scorePlayer2;	
	std::string sp1;	
	std::string sp2;	
	std::string lt;		
	std::string rt;		

	VEC2 vMidTimerTemp;
	VEC2 vLeftTimerTemp;
	VEC2 vRightTimerTemp;
	VEC2 vP1SCTTemp;
	VEC2 vP1ScTemp;
	VEC2 vP2ScTemp;
	VEC2 vP2SCTTemp;

public:
	Game();
	~Game();

	void Run();
	void addPlayerLifeSprite(int texWidth, int texHeight, Player::EPlayerType type);
private:
	
	void Update();
	void Render();
};