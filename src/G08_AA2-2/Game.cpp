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

	au->PlayMusic(S_MENU, -1);
	au->VolumeMusic(S_MENU, 1);

	timeDown = MAX_GAMETIME;
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
				au->PlayMusic(S_GAME_THEME, -1);
				au->VolumeMusic(S_GAME_THEME, 1);
				gameState = GameState::PLAY;
			}
			r->SetTexture(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1_H);
		}
		else r->SetTexture(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1_N);

		// -- Play LV2
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_PLAY_LV2))) {

			if (input->JustPressed(InputKeys::MOUSE_LEFT)) {
				au->PlayMusic(S_GAME_THEME, -1);
				au->VolumeMusic(S_GAME_THEME, 1);
				gameState = GameState::PLAY;
			}
			r->SetTexture(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2_H);
		}
		else r->SetTexture(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2_N);

		// -- Ranking
		if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_RANKING))) {
			if (input->JustPressed(InputKeys::MOUSE_LEFT))
			{
				gameState = GameState::RANKING;
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
			if (input->JustPressed(InputKeys::MOUSE_LEFT)) {
				if (!au->MusicIsPaused(S_MENU)) au->PauseMusic(S_MENU);
				else au->ResumeMusic(S_MENU);
			}
			r->SetTexture(T_BTN_SOUND, T_BTN_SOUND_H);
		}
		else r->SetTexture(T_BTN_SOUND, T_BTN_SOUND_N);
		break;
	case GameState::PLAY:
		if (input->isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
		if (input->JustPressed(InputKeys::ESC)) 
		{
			au->PlayMusic(S_MENU, -1);
			au->VolumeMusic(S_MENU, 1);
			gameState = GameState::MENU;
		}

		// -- Update Scene --
		scenes.at(1)->Update();

		// -- Update HUD -- 
		if (gameState == GameState::PLAY) timeDown -= *input->GetDeltaTime();;
		if (timeDown <= 0.f) gameState = GameState::MENU;
		
		else 
		{
			// Timer
			std::string s = F2StrFormat(trunc(timeDown / 60), 0);
			s += ":" + F2StrFormat(static_cast<int>(timeDown) % 60, 0);
			VEC2 vTemp = r->LoadTextureText(F_GAMEOVER, { T_TXT_TIME, s.c_str(), { 0,0,0,255 }, 0, 0 });
			r->LoadRect(T_TXT_TIME, { SCREEN_WIDTH / 2 - vTemp.x, 10, vTemp.x, vTemp.y });
														
			// Score Player 1
			//std::string sp1 = F2StrFormat(200, 0);
			//vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL1_SCORE, sp1.c_str(), { 0,0,0,255 }, 0, 0 });
			//r->LoadRect(T_PL1_SCORE, { vTemp.x + TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });

			// Score Player 2
			//std::string sp2 = F2StrFormat(220, 0);
			//vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL2_SCORE, sp2.c_str(), { 0,0,0,255 }, 0, 0 });
			//r->LoadRect(T_PL1_SCORE, { SCREEN_WIDTH - vTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });
		}


		break;
	case GameState::RANKING:
		if (input->isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
		if (input->JustPressed(InputKeys::ESC)) gameState = GameState::MENU;
		break;
	default:
		break;
	}


//#pragma endregion

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
		input->UpdateDeltaTime();
	}
}