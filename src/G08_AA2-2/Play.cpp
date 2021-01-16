#include "Play.h"

Play::Play(Level::ELevelType _level)
{
#pragma region GRID

	level = new Level(_level);
	
#pragma endregion

#pragma region HUD

	//-->TEXT TIMER
	r->LoadFont({ F_GAMEOVER, P_TTF_GAMEOVER, 90 });

	VEC2 vTemp =r->LoadTextureText(F_GAMEOVER, { T_TXT_TIME, " ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_TXT_TIME, { SCREEN_WIDTH / 2, 10, vTemp.x, vTemp.y });
	
	//-->PLAYERS SCORE TXT
	// PL1 SCORE TEXT
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL1_SCORE_TEXT, "PL1: ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL1_SCORE_TEXT, { TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });
	// PL1 SCORE
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL1_SCORE, " ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL1_SCORE, { vTemp.x + TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });
	// PL2 SCORE TEXT
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL2_SCORE_TEXT, "PL2: ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL2_SCORE_TEXT, { SCREEN_WIDTH - vTemp.x - vTemp.x - TEXT_HUD_HORIZONTAL_SPACING + 10, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });
	// PL2 SCORE
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL2_SCORE, " ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL2_SCORE, { SCREEN_WIDTH - vTemp.x - TEXT_HUD_HORIZONTAL_SPACING + 10, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });

#pragma endregion

}

Play::~Play() 
{
	delete level;
}

void Play::Update(InputManager& input)
{
	//timeDown -= *input.GetDeltaTime();;
	level->Update(level->GetType(), input);
	//while (timeDown > 0)
	//{
	//	
	//}
}

void Play::Draw() 
{
	//-->BACKGROUND
	r->PushImage(T_BG, T_BG);
	
	//-->HUD
	// -- Timer --
	r->PushImage(T_TXT_TIME, T_TXT_TIME);
	// -- PL1 -- 
	r->PushImage(T_PL1_SCORE_TEXT, T_PL1_SCORE_TEXT);
	r->PushImage(T_PL1_SCORE, T_PL1_SCORE);

	// -- PL2 --
	r->PushImage(T_PL2_SCORE_TEXT, T_PL2_SCORE_TEXT);
	r->PushImage(T_PL2_SCORE, T_PL2_SCORE);

	//-->LEVELS
	level->Draw(level->GetType());
}