#include "Ranking.h"

Ranking::Ranking(ERankingState _state)
{
	state = _state;

	// -- Background --
	r->LoadTexture(T_BG, P_BG);
	r->LoadRect(T_BG, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	// -- Tittle Game -- 
	VEC2 vTemp = r->LoadTextureText(F_SAIYAN_TITLE, { T_TITLE, "BOOMBERENTI", { 0,0,100,255 }, 0, 0 });
	r->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vTemp.x / 2, TEXT_LINESPACING_MENU + (SCREEN_HEIGHT) / TEXTSIZE_MENU * 0, vTemp.x, vTemp.y });
	
	// NAME - SCORE
	r->LoadFont({ F_GAMEOVER, P_TTF_GAMEOVER, 100 });
	
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_BOARDNAME, "Name", { 0,0,100,255 }, 0, 0 });
	r->LoadRect(T_BOARDNAME, { SCREEN_WIDTH / 2 - vTemp.x / 2 - 150, SPRITE_HUD_HEIGHT + SPRITE_RES, vTemp.x, vTemp.y });
	
	r->LoadTextureText(F_GAMEOVER, { T_BOARDSCORE, "Score", { 0,0,100,255 }, 0, 0 });
	r->LoadRect(T_BOARDSCORE, { SCREEN_WIDTH / 2 - vTemp.x / 2 + 150, SPRITE_HUD_HEIGHT + SPRITE_RES, vTemp.x, vTemp.y });

}

Ranking::~Ranking()
{
}

void Ranking::Update(InputManager& input)
{
	switch (state)
	{
	case ERankingState::ASKNAME:
		BoardRanking::GetInstance()->AskName();
		state = ERankingState::RUNNING;
		break;
	case ERankingState::RUNNING:
		BoardRanking::GetInstance();
		break;
	}
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
}