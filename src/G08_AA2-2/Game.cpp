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
	Renderer::GetInstance()->Clear();
	//Background

	//UI

	//Objects

	//Timer

	Renderer::GetInstance()->Render();
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
		case GameState::PLAY:
			break;
		case GameState::RANKING:
			break;

		
		}

		// --- FRAME CONTROL ---

	}
}