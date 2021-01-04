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

	timeDown = 90;			
	while (timeDown >= 60)		
	{				
		timeDown -= 60;		
		minTimeDown++;		
	}				
	secTimeDown = timeDown;
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

		// -- Update HUD -- 										
		//Update timer											
		if (gameState == GameState::PLAY) secTimeDown -= *input->GetDeltaTime();			
		if (secTimeDown <= 0.f && minTimeDown <= 0.f) gameState = GameState::MENU;			
														
		else {												
			r->LoadFont({ F_TIMER_HUD, "../../res/ttf/game_over.ttf", 100 });	
														
			//Update Timer										
			if (secTimeDown <= 0.f)									
			{											
				secTimeDown = 59;								
				if (minTimeDown > 0)								
				{										
					minTimeDown--;		

				}									
			}
			// ":"
			VEC2 vMidTimerTemp = Renderer::GetInstance()->LoadTextureText(F_TIMER_HUD, { T_PLAY_MIDDLE_SIDE_TIMER, ":", { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PLAY_MIDDLE_SIDE_TIMER, { SCREEN_WIDTH / 2 - vMidTimerTemp.x / 2, TEXT_HUD_VERTICAL_SPACING, vMidTimerTemp.x, vMidTimerTemp.y });
			//Minutes
			lt = F2StrFormat(minTimeDown, 0);
			VEC2 vLeftTimerTemp = Renderer::GetInstance()->LoadTextureText(F_TIMER_HUD, { T_PLAY_LEFT_SIDE_TIMER, lt.c_str(), { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PLAY_LEFT_SIDE_TIMER, { SCREEN_WIDTH / 2 - vLeftTimerTemp.x - vMidTimerTemp.x / 2, TEXT_HUD_VERTICAL_SPACING, vLeftTimerTemp.x, vLeftTimerTemp.y });
			//Seconds
			rt = F2StrFormat(secTimeDown, 0);
			VEC2 vRightTimerTemp = Renderer::GetInstance()->LoadTextureText(F_TIMER_HUD, { T_PLAY_RIGHT_SIDE_TIMER, rt.c_str(), { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PLAY_RIGHT_SIDE_TIMER, { SCREEN_WIDTH / 2 + vMidTimerTemp.x / 2, TEXT_HUD_VERTICAL_SPACING, vRightTimerTemp.x, vRightTimerTemp.y });

			Renderer::GetInstance()->LoadFont({ F_PLAYERS_HUD, "../../res/ttf/game_over.ttf", 80 });

			//Player 1 score text
			VEC2 vP1SCTTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL1_SCORE_TEXT, "PL1: ", { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PL1_SCORE_TEXT, { TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP1SCTTemp.x, vP1SCTTemp.y });

			//Update Score Player 1
			sp1 = F2StrFormat(scorePlayer1, 0);
			VEC2 vP1ScTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL1_SCORE, sp1.c_str(), { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PL1_SCORE, { vP1SCTTemp.x + TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP1ScTemp.x, vP1ScTemp.y });

			//Update Score Player 2
			sp2 = F2StrFormat(scorePlayer2, 0);
			VEC2 vP2ScTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL2_SCORE, sp2.c_str(), { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PL2_SCORE, { SCREEN_WIDTH - vP2ScTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP2ScTemp.x, vP2ScTemp.y });

			//Player 2 score text
			VEC2 vP2SCTTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL2_SCORE_TEXT, "PL2: ", { 0,0,0,255 }, 0, 0 });
			Renderer::GetInstance()->LoadRect(T_PL2_SCORE_TEXT, { SCREEN_WIDTH - vP2SCTTemp.x - vP2ScTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP2SCTTemp.x, vP2SCTTemp.y });

			//Renderer::GetInstance()->LoadTexture(T_PLAYER1, "../../res/img/player1.png");
		}

		break;
	case GameState::RANKING:
		if (input->isPressed(InputKeys::QUIT)) gameState = GameState::EXIT;
		if (input->JustPressed(InputKeys::ESC)) gameState = GameState::MENU;
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
		input->UpdateDeltaTime();
	}
}