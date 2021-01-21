#include "Game.h"

Game::Game()
{
	gameState = GameState::MENU;
	input.SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));

	scenes = new Menu();

	// -- AUDIO --
	au->LoadAudio(S_MENU, P_MENU);
	au->LoadAudio(S_GAME_THEME, P_GAME_THEME);

	au->PlayMusic(S_MENU, -1);
	au->VolumeMusic(S_MENU, 1);
}

Game::~Game()
{
}

void Game::Update()
{
	scenes->Update(&input);
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
				delete scenes;
				scenes = new Play(Map::ELevelType::LEVEL1);
				gameState = GameState::PLAY;
				break;

			case Scene::ESceneState::CLICK_PLAY_LV2:
				delete scenes;
				scenes = new Play(Map::ELevelType::LEVEL2);
				gameState = GameState::PLAY;
				break;

			case Scene::ESceneState::CLICK_RANKING:
				delete scenes;
				scenes = new Ranking();
				gameState = GameState::RANKING;
				break;

			case Scene::ESceneState::CLICK_EXIT:
				delete scenes;
				gameState = GameState::EXIT;
				break;

			case Scene::ESceneState::CLICK_QUIT:;
				delete scenes;
				gameState = GameState::EXIT;
				break;

			case Scene::ESceneState::RUNNING:
				Update();
				Render();
				break;
			default:
				break;
			}
			break;

		case GameState::PLAY:

			if (input.isPressed(InputKeys::QUIT)) scenes->SetState(Scene::ESceneState::CLICK_QUIT);
			if (input.JustPressed(InputKeys::ESC))
			{
				au->PauseMusic(S_GAME_THEME);
				au->PlayMusic(S_MENU, 1);
				scenes->SetState(Scene::ESceneState::CLICK_EXIT);
			}
			switch (*scenes->GetState())
			{
			case Scene::ESceneState::CLICK_EXIT:

				delete scenes;
				scenes = new Menu();
				gameState = GameState::MENU;
				break;
			case Scene::ESceneState::CLICK_QUIT:
				delete scenes;
				break;
			case Scene::ESceneState::CLICK_RANKING:
				delete scenes;
				scenes = new Ranking();
				gameState = GameState::RANKING;
				break;

			case Scene::ESceneState::RUNNING:
				Update();
				Render();
				break;

			default:
				break;
			}
			break;

		case GameState::RANKING:
			
			if (input.isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
			if (input.JustPressed(InputKeys::ESC)) scenes->SetState(Scene::ESceneState::CLICK_EXIT);

			switch (*scenes->GetState())
			{
			case Scene::ESceneState::CLICK_EXIT:
				delete scenes;
				scenes = new Menu();
				gameState = GameState::MENU;
				break;
				
			case Scene::ESceneState::RUNNING:
				Update();
				Render();
				break;

			default:
				break;
			}
			break;
		default:
			break;
		}

		// --- FRAME CONTROL ---
		input.UpdateDeltaTime();
	}
}