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

enum class GameState { MENU, PLAY, RANKING, EXIT };

class Game
{
private:
	
	GameState gameState;
	std::vector<Scene*> scenes;

	Renderer *r = Renderer::GetInstance();
	InputManager *input = InputManager::GetInstance();
	
public:
	Game();
	~Game();

	void Run();
private:
	
	void Update();
	void Render();
};