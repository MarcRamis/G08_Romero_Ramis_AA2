#pragma once

// ----- SIGHT
#include "InputManager.h"
#include "Audio.h"
#include "Renderer.h"

// ----- MODELS
#include "Collisions.h"

enum class GameState { MENU, PLAY, RANKING, EXIT };

class Game
{
private:
	
	GameState gameState;

public:
	Game();
	~Game();

	void Run();
private:
	void Update();
	void Render();
};