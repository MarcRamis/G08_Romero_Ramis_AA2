#include "Ranking.h"

Ranking::Ranking(/*ERankingState _state*/)
{
	/*rankingState = _state;*/

	// -- Background --
	r->LoadTexture(T_BG, P_BG);
	r->LoadRect(T_BG, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	// -- Tittle Game -- 
	r->LoadFont({ F_SAIYAN_TITLE, P_TTF_SAIYAN, 60 });
	VEC2 vTemp = r->LoadTextureText(F_SAIYAN_TITLE, { T_TITLE, "BOOMBERENTI", { 0,0,100,255 }, 0, 0 });
	r->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 0, vTemp.x, vTemp.y });
	
	// -- Buttons --
	r->LoadFont({ F_SAIYAN, P_TTF_SAIYAN, 50 });
	// EXIT
	r->LoadTextureText(F_SAIYAN, { T_BTN_EXIT_N, "Exit", { 150,0,0,255 }, 0, 0 });
	vTemp = r->LoadTextureText(F_SAIYAN, { T_BTN_EXIT_H, "Exit", { 100,0,0,255 }, 0, 0 });
	r->LoadTextureText(F_SAIYAN, { T_BTN_EXIT, "Exit", { 0,0,0,0 }, 0, 0 });
	r->LoadRect(T_BTN_EXIT, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 5, vTemp.x, vTemp.y });

	// NAME - SCORE
	r->LoadFont({ F_GAMEOVER, P_TTF_GAMEOVER, 100 });
	
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_BOARDNAME, "Name", { 0,0,200,255 }, 0, 0 });
	r->LoadRect(T_BOARDNAME, { SCREEN_WIDTH / 2 - vTemp.x / 2 - 150, SPRITE_HUD_HEIGHT + SPRITE_RES, vTemp.x, vTemp.y });
	
	r->LoadTextureText(F_GAMEOVER, { T_BOARDSCORE, "Score", { 0,0,200,255 }, 0, 0 });
	r->LoadRect(T_BOARDSCORE, { SCREEN_WIDTH / 2 - vTemp.x / 2 + 150, SPRITE_HUD_HEIGHT + SPRITE_RES, vTemp.x, vTemp.y });
	
	BoardRanking::GetInstance()->ReadRanking();
	BoardRanking::GetInstance()->LoadRanking();
}

Ranking::~Ranking()
{
}

void Ranking::Update(InputManager* input)
{
	// EXIT
	if (Collisions::ExistCollision(input->GetMouseCoords(), r->GetRect(T_BTN_EXIT))) {
		if (input->JustPressed(InputKeys::MOUSE_LEFT))
		{
			SetState(ESceneState::CLICK_EXIT);
		}
		r->SetTexture(T_BTN_EXIT, T_BTN_EXIT_H);
	}
	else r->SetTexture(T_BTN_EXIT, T_BTN_EXIT_N);
}

void Ranking::Draw()
{
	// -- Background --
	r->PushImage(T_BG, T_BG);

	// -- Title -- 
	r->PushImage(T_TITLE, T_TITLE);
	
	// -- BoardGame --
	r->PushImage(T_BOARDNAME, T_BOARDNAME);
	r->PushImage(T_BOARDSCORE, T_BOARDSCORE);

	// -- Button exit --
	r->PushImage(T_BTN_EXIT, T_BTN_EXIT);

	BoardRanking::GetInstance()->Draw();
}