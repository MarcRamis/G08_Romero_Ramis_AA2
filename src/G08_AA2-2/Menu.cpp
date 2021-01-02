#include "Menu.h"

Menu::Menu()
{
	// -- Background --
	Renderer::GetInstance()->LoadTexture(T_BG, P_BG);
	Renderer::GetInstance()->LoadRect(T_BG, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	// -- MENU INFO --
#pragma region Buttons

	Renderer::GetInstance()->LoadFont({ F_SAIYAN, "../../res/ttf/saiyan.ttf", 50 });
	Renderer::GetInstance()->LoadFont({ F_SAIYAN_TITLE, "../../res/ttf/saiyan.ttf", 60 });

	// TITLE GAME
	VEC2 vTemp = Renderer::GetInstance()->LoadTextureText(F_SAIYAN_TITLE, { T_TITLE, "BOOMBERENTI", { 0,0,100,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 0, vTemp.x, vTemp.y });

	// -- Buttons --

	// PLAY LV1
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV1_N, "Play Level One", { 0,70,70,255 }, 0, 0 });
	vTemp = Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV1_H, "Play Level One", { 0,30,30,255 }, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV1, "Play Level One", { 0,0,0,0 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_BTN_PLAY_LV1, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 1, vTemp.x, vTemp.y });
	
	// PLAY LV2
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV2_N, "Play Level Two", { 0,70,70,255 }, 0, 0 });
	vTemp = Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV2_H, "Play Level Two", { 0,30,30,255 }, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_PLAY_LV2, "Play Level Two", { 0,0,0,0 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_BTN_PLAY_LV2, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 2, vTemp.x, vTemp.y });

	// RANKING
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_RANKING_N, "Consult Ranking", { 150,0,0,255 }, 0, 0 });
	vTemp = Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_RANKING_H, "Consult Ranking", { 100,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_RANKING, "Consult Ranking", { 0,0,0,0 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_BTN_RANKING, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 3, vTemp.x, vTemp.y });

	// EXIT
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_EXIT_N, "Exit", { 150,0,0,255 }, 0, 0 });
	vTemp = Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_EXIT_H, "Exit", { 100,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_EXIT, "Exit", { 0,0,0,0 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_BTN_EXIT, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 5, vTemp.x, vTemp.y });

	// SOUND
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_SOUND_N, "Sound Off/On", { 200,100,0,255 }, 0, 0 });
	vTemp = Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_SOUND_H, "Sound Off/On", { 150,60,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { T_BTN_SOUND, "Sound Off/On", { 0,0,0,0 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_BTN_SOUND, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 4, vTemp.x, vTemp.y });

#pragma endregion

	// -- AUDIO --
	Audio::GetInstance()->LoadAudio(S_MENU, P_MENU);
}

Menu::~Menu() {}

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