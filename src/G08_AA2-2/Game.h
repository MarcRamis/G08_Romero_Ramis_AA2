#pragma once

// ----- SIGHT
#include "InputManager.h"			
#include "Audio.h"
#include "Renderer.h"
#include "BoardRanking.h"

// ----- MODELS
#include "Scene.h"
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"

#include "Utils.h"

enum class GameState { MENU, PLAY, RANKING, EXIT };

class Game
{
private:
	
	GameState gameState;
	Scene* scenes;
	
	Renderer *r = Renderer::GetInstance();
	Audio *au = Audio::GetInstance();
	
	InputManager input;

	float timeDown;	

public:
	Game();
	~Game();

	void Run();

private:
	
	void Update();
	void Render();
};