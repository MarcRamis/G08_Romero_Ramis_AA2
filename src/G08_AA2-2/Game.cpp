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

void Game::UpdateInput()
{
	input->SetFalseKeyDown();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			input->SetKeyValue(InputKeys::QUIT, true);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) input->SetKeyValue(InputKeys::ESC, true);

			if (event.key.keysym.sym == SDLK_w) input->SetKeyValue(InputKeys::W, true);
			if (event.key.keysym.sym == SDLK_a) input->SetKeyValue(InputKeys::A, true);
			if (event.key.keysym.sym == SDLK_s) input->SetKeyValue(InputKeys::S, true);
			if (event.key.keysym.sym == SDLK_d) input->SetKeyValue(InputKeys::D, true);

			if (event.key.keysym.sym == SDLK_UP) input->SetKeyValue(InputKeys::UP, true);
			if (event.key.keysym.sym == SDLK_DOWN) input->SetKeyValue(InputKeys::DOWN, true);
			if (event.key.keysym.sym == SDLK_LEFT) input->SetKeyValue(InputKeys::LEFT, true);
			if (event.key.keysym.sym == SDLK_RIGHT) input->SetKeyValue(InputKeys::RIGHT, true);
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) input->SetKeyValue(InputKeys::ESC, false);

			if (event.key.keysym.sym == SDLK_w) input->SetKeyValue(InputKeys::W, false);
			if (event.key.keysym.sym == SDLK_a) input->SetKeyValue(InputKeys::A, false);
			if (event.key.keysym.sym == SDLK_s) input->SetKeyValue(InputKeys::S, false);
			if (event.key.keysym.sym == SDLK_d) input->SetKeyValue(InputKeys::D, false);

			if (event.key.keysym.sym == SDLK_UP) input->SetKeyValue(InputKeys::UP, false);
			if (event.key.keysym.sym == SDLK_DOWN) input->SetKeyValue(InputKeys::DOWN, false);
			if (event.key.keysym.sym == SDLK_LEFT) input->SetKeyValue(InputKeys::LEFT, false);
			if (event.key.keysym.sym == SDLK_RIGHT) input->SetKeyValue(InputKeys::RIGHT, false);
			break;

		case SDL_MOUSEMOTION:
			input->SetMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) input->SetKeyValue(InputKeys::MOUSE_LEFT, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) input->SetKeyValue(InputKeys::MOUSE_LEFT, false);
			break;
		default:;
		}
	}
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
		UpdateInput();

		Render();
		Update();
		
		// --- FRAME CONTROL ---
		//input->UpdateDeltaTime();
	}
}