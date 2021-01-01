#include "Game.h"

Game::Game()
{
	gameState = GameState::MENU;
	input->SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));

	Scene* sc;
	sc = new Menu();
	scenes.push_back(sc);
	sc = new Play();
	scenes.push_back(sc);
}

Game::~Game()
{

}

void Game::Update()
{
	switch (gameState)
	{
	case GameState::MENU:
		if (input->isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
		if (input->JustPressed(InputKeys::ESC)) gameState = GameState::EXIT;

		// Update Buttons
#pragma region Buttons
	// -- Play LV1
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_PLAY_LV1))) {

			if (input->JustPressed(InputKeys::MOUSE_LEFT)) {

			}
			r->SetTexture(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1_H);
		}
		else r->SetTexture(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1_N);

		// -- Play LV2
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_PLAY_LV2))) {

			if (input->JustPressed(InputKeys::MOUSE_LEFT)) {

				gameState = GameState::PLAY;
			}
			r->SetTexture(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2_H);
		}
		else r->SetTexture(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2_N);

		// -- Ranking
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_RANKING))) {
			if (input->JustPressed(InputKeys::MOUSE_LEFT))
			{

			}
			r->SetTexture(T_BTN_RANKING, T_BTN_RANKING_H);
		}
		else r->SetTexture(T_BTN_RANKING, T_BTN_RANKING_N);

		// -- Exit 
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_EXIT))) {
			if (input->JustPressed(InputKeys::MOUSE_LEFT))
			{
				gameState = GameState::EXIT;
			}
			r->SetTexture(T_BTN_EXIT, T_BTN_EXIT_H);
		}
		else r->SetTexture(T_BTN_EXIT, T_BTN_EXIT_N);

		// -- Sound 
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_SOUND)))
		{
			//if (input->JustPressed(InputKeys::MOUSE_LEFT)) {
			//	if (!a->MusicIsPaused(S_MAIN_THEME)) a->PauseMusic(S_MAIN_THEME);
			//	else a->ResumeMusic(S_MAIN_THEME);
			//}
			r->SetTexture(T_BTN_SOUND, T_BTN_SOUND_H);
		}
		else r->SetTexture(T_BTN_SOUND, T_BTN_SOUND_N);
		break;
	case GameState::PLAY:
		if (input->isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
		if (input->JustPressed(InputKeys::ESC)) gameState = GameState::MENU;
		break;
	case GameState::RANKING:
		break;
	default:
		break;
	}


#pragma endregion

}

void Game::Render()
{
	r->Clear();

	switch (gameState)
	{
	case GameState::MENU:
		scenes.at(0)->Draw();
		break;
	case GameState::PLAY:
		scenes.at(1)->Draw();
		break;
	case GameState::RANKING:
		break;
	default:
		break;
	}

	r->Render();
}

void Game::Run()
{
	while (gameState != GameState::EXIT)
	{
		input->Update();
		
		Render();
		Update();
		
		// --- FRAME CONTROL ---
		//input->UpdateDeltaTime();
	}
}