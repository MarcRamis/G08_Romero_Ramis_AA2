#include "Game.h"

Game::Game()
{
	gameState = GameState::MENU;
	InputManager::GetInstance()->SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));
}

Game::~Game()
{

}

void Game::Update()
{

}

void Game::Render()
{
	Renderer::GetInstance()->
}

void Game::Run()
{
	while (gameState != GameState::EXIT)
	{
		//UpdateInput();

		switch (gameState)
		{
		case GameState::MENU:
			break;
		case GameState::GAME:
			break;
		case GameState::GAME:

			break;
			defa
		}

		// --- FRAME CONTROL ---

	}
}