#include "Menu.h"

Menu::Menu()
{
	//state = ESceneState::RUNNING;

	// -- Background --
	r->LoadTexture(T_BG, P_BG);
	r->LoadRect(T_BG, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	// -- MENU INFO --
	#pragma region Buttons

	r->LoadFont({ F_SAIYAN, P_TTF_SAIYAN, 50 });
	r->LoadFont({ F_SAIYAN_TITLE, P_TTF_SAIYAN, 60 });
	
	// TITLE GAME
	VEC2 vTemp =r->LoadTextureText(F_SAIYAN_TITLE, { T_TITLE, "BOOMBERENTI", { 0,0,100,255 }, 0, 0 });
	r->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 0, vTemp.x, vTemp.y });

	// -- Buttons --

	// PLAY LV1
	r->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV1_N, "Play Level One", { 0,70,70,255 }, 0, 0 });
	vTemp = r->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV1_H, "Play Level One", { 0,30,30,255 }, 0, 0 });
	r->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV1, "Play Level One", { 0,0,0,0 }, 0, 0 });
	r->LoadRect(T_BTN_PLAY_LV1, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 1, vTemp.x, vTemp.y });
	
	// PLAY LV2
	r->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV2_N, "Play Level Two", { 0,70,70,255 }, 0, 0 });
	vTemp = r->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV2_H, "Play Level Two", { 0,30,30,255 }, 0, 0 });
	r->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV2, "Play Level Two", { 0,0,0,0 }, 0, 0 });
	r->LoadRect(T_BTN_PLAY_LV2, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 2, vTemp.x, vTemp.y });

	// RANKING
	r->LoadTextureText(F_SAIYAN, { T_BTN_RANKING_N, "Consult Ranking", { 150,0,0,255 }, 0, 0 });
	vTemp = r->LoadTextureText(F_SAIYAN, { T_BTN_RANKING_H, "Consult Ranking", { 100,0,0,255 }, 0, 0 });
	r->LoadTextureText(F_SAIYAN, { T_BTN_RANKING, "Consult Ranking", { 0,0,0,0 }, 0, 0 });
	r->LoadRect(T_BTN_RANKING, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 3, vTemp.x, vTemp.y });

	// EXIT
	r->LoadTextureText(F_SAIYAN, { T_BTN_EXIT_N, "Exit", { 150,0,0,255 }, 0, 0 });
	vTemp = r->LoadTextureText(F_SAIYAN, { T_BTN_EXIT_H, "Exit", { 100,0,0,255 }, 0, 0 });
	r->LoadTextureText(F_SAIYAN, { T_BTN_EXIT, "Exit", { 0,0,0,0 }, 0, 0 });
	r->LoadRect(T_BTN_EXIT, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 5, vTemp.x, vTemp.y });

	// SOUND
	r->LoadTextureText(F_SAIYAN, { T_BTN_SOUND_N, "Sound Off/On", { 200,100,0,255 }, 0, 0 });
	vTemp = r->LoadTextureText(F_SAIYAN, { T_BTN_SOUND_H, "Sound Off/On", { 150,60,0,255 }, 0, 0 });
	r->LoadTextureText(F_SAIYAN, { T_BTN_SOUND, "Sound Off/On", { 0,0,0,0 }, 0, 0 });
	r->LoadRect(T_BTN_SOUND, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 4, vTemp.x, vTemp.y });

#pragma endregion

	// -- AUDIO --
	au->LoadAudio(S_MENU, P_MENU);
}

Menu::~Menu() 
{
}

void Menu::Update(InputManager& input)
{	
	if (input.isPressed(InputKeys::QUIT)) state = ESceneState::CLICK_QUIT;
	if (input.JustPressed(InputKeys::ESC)) state = ESceneState::CLICK_EXIT;
	
#pragma region Buttons

	// PLAY LEVEL 1
	if (Collisions::ExistCollision(input.GetMouseCoords(), r->GetRect(T_BTN_PLAY_LV1))) {

		if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
			au->PlayMusic(S_GAME_THEME, -1);
			au->VolumeMusic(S_GAME_THEME, 1);
			state = ESceneState::CLICK_PLAY_LV1;
		}
		r->SetTexture(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1_H);
	}
	else r->SetTexture(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1_N);

	// PLAY LEVEL 2
	if (Collisions::ExistCollision(input.GetMouseCoords(), r->GetRect(T_BTN_PLAY_LV2))) {

		if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
			
			au->PlayMusic(S_GAME_THEME, -1);
			au->VolumeMusic(S_GAME_THEME, 1);
			state = ESceneState::CLICK_PLAY_LV2;
		}
		r->SetTexture(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2_H);
	}
	else r->SetTexture(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2_N);
	
	// RANKING
	if (Collisions::ExistCollision(input.GetMouseCoords(), r->GetRect(T_BTN_RANKING))) {
		if (input.JustPressed(InputKeys::MOUSE_LEFT))
		{
			state = ESceneState::CLICK_RANKING;
		}
		r->SetTexture(T_BTN_RANKING, T_BTN_RANKING_H);
	}
	else r->SetTexture(T_BTN_RANKING, T_BTN_RANKING_N);

	// SOUND
	if (Collisions::ExistCollision(input.GetMouseCoords(), r->GetRect(T_BTN_SOUND)))
	{
		if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
			if (!au->MusicIsPaused(S_MENU)) au->PauseMusic(S_MENU);
			else au->ResumeMusic(S_MENU);
		}
		r->SetTexture(T_BTN_SOUND, T_BTN_SOUND_H);
	}
	else r->SetTexture(T_BTN_SOUND, T_BTN_SOUND_N);
	
	// EXIT
	if (Collisions::ExistCollision(input.GetMouseCoords(), r->GetRect(T_BTN_EXIT))) {
		if (input.JustPressed(InputKeys::MOUSE_LEFT))
		{
			state = ESceneState::CLICK_EXIT;
		}
		r->SetTexture(T_BTN_EXIT, T_BTN_EXIT_H);
	}
	else r->SetTexture(T_BTN_EXIT, T_BTN_EXIT_N);

#pragma endregion
}

void Menu::Draw()
{
	// -- Background --
	Renderer::GetInstance()->PushImage(T_BG, T_BG);

	// -- Title -- 
	Renderer::GetInstance()->PushImage(T_TITLE, T_TITLE);
	
	// -- Buttons -- 
	Renderer::GetInstance()->PushImage(T_BTN_PLAY_LV1, T_BTN_PLAY_LV1);
	Renderer::GetInstance()->PushImage(T_BTN_PLAY_LV2, T_BTN_PLAY_LV2);
	Renderer::GetInstance()->PushImage(T_BTN_RANKING, T_BTN_RANKING);
	Renderer::GetInstance()->PushImage(T_BTN_EXIT, T_BTN_EXIT);
	Renderer::GetInstance()->PushImage(T_BTN_SOUND, T_BTN_SOUND);
}