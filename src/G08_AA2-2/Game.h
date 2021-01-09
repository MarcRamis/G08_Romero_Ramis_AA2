#pragma once

// ----- SIGHT
#include "InputManager.h"
#include "Audio.h"
#include "Renderer.h"

// ----- MODELS
#include "Scene.h"
#include "Menu.h"
#include "Play.h"

#include "Utils.h"

enum class GameState { MENU, PLAY, RANKING, EXIT };

class Game
{
private:
	
	GameState gameState;
	Scene* scenes;
	
	Renderer *r = Renderer::GetInstance();
	InputManager *input = InputManager::GetInstance();
	Audio *au = Audio::GetInstance();
	
	float timeDown;	

public:
	Game();
	~Game();

	void Run();

private:
	
	void Update();
	void Render();
};