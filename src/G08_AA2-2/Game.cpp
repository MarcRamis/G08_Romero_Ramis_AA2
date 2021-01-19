#include "Game.h"

Game::Game()
{
	gameState = GameState::MENU;
	input.SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));

	scenes = new Menu();

	au->PlayMusic(S_MENU, -1);
	au->VolumeMusic(S_MENU, 1);
}

Game::~Game()
{

}

void Game::Update()
{
	scenes->Update(input);
}
void Game::Render()
{
	r->Clear();
	scenes->Draw();
	r->Render();
}

void Game::Run()
{
	while (gameState != GameState::EXIT)
	{
		input.Update();

		switch (gameState)
		{
		case GameState::MENU:

			switch (*scenes->GetState())
			{
			case Scene::ESceneState::CLICK_PLAY_LV1:
				std::cout << "State is CLICK_PLAY_LV1 -> Menu" << std::endl;
				delete scenes;
				scenes = new Play(Map::ELevelType::LEVEL1);
				gameState = GameState::PLAY;
				break;

			case Scene::ESceneState::CLICK_PLAY_LV2:
				std::cout << "State is CLICK_PLAY_LV2 -> Menu" << std::endl;
				delete scenes;
				scenes = new Play(Map::ELevelType::LEVEL2);
				gameState = GameState::PLAY;
				break;

			case Scene::ESceneState::CLICK_RANKING:
				delete scenes;
				scenes = new Ranking(Ranking::ERankingState::RUNNING);
				std::cout << "State is CLICK_RANKING -> Menu" << std::endl;
				gameState = GameState::RANKING;
				break;

			case Scene::ESceneState::CLICK_EXIT:
				std::cout << "State is CLICK_EXIT - > Menu" << std::endl;
				delete scenes;
				gameState = GameState::EXIT;
				break;

			case Scene::ESceneState::CLICK_QUIT:
				std::cout << "State is CLICK_QUIT - > Menu" << std::endl;
				delete scenes;
				gameState = GameState::EXIT;
				break;

			case Scene::ESceneState::RUNNING:
				Update();
				Render();
				//std::cout << "State is RUNNING -> Menu" << std::endl;
				break;
			default:
				//std::cout << "No state in Scene -> Menu" << std::endl;
				break;
			}
			break;

		case GameState::PLAY:

			if (input.isPressed(InputKeys::QUIT)) scenes->SetState(Scene::ESceneState::CLICK_QUIT);
			if (input.JustPressed(InputKeys::ESC)) scenes->SetState(Scene::ESceneState::CLICK_EXIT);

			switch (*scenes->GetState())
			{
			case Scene::ESceneState::CLICK_EXIT:
				std::cout << "State is CLICK_EXIT - > Play" << std::endl;
				delete scenes;
				scenes = new Menu();
				gameState = GameState::MENU;
				break;
			case Scene::ESceneState::CLICK_QUIT:
				std::cout << "State is CLICK_QUIT - > Play" << std::endl;
				delete scenes;
				break;
			case Scene::ESceneState::CLICK_RANKING:
				std::cout << "State is CLICK_RANKING -> Play" << std::endl;
				delete scenes;
				scenes = new Ranking(Ranking::ERankingState::RUNNING);
				gameState = GameState::RANKING;
				break;

			case Scene::ESceneState::RUNNING:
				//std::cout << "State is RUNNING -> Play" << std::endl;
				Update();
				Render();
				break;

			default:
				std::cout << "No state in Scene -> Play" << std::endl;
				break;
			}
			break;

		case GameState::RANKING:
			
			if (input.isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
			if (input.JustPressed(InputKeys::ESC)) scenes->SetState(Scene::ESceneState::CLICK_EXIT);

			switch (*scenes->GetState())
			{
			case Scene::ESceneState::CLICK_EXIT:
				std::cout << "State is CLICK_EXIT -> Ranking" << std::endl;
				delete scenes;
				scenes = new Menu();
				gameState = GameState::MENU;
				break;
				
			case Scene::ESceneState::RUNNING:
				//std::cout << "State is RUNNING -> Ranking" << std::endl;
				Update();
				Render();
				break;

			default:
				std::cout << "No state in Scene -> Ranking" << std::endl;
				break;
			}
			break;
		default:
			std::cout << "No state in GameState" << std::endl;
			break;
		}

		//Update();
		//Render();

		// --- FRAME CONTROL ---
		input.UpdateDeltaTime();
	}
}