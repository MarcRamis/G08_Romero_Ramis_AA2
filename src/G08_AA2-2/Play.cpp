#include "Play.h"

Play::Play() 
{
#pragma region GRID

	ReadMap();

	Map* tmpMap = new Map();
	levels.push_back(tmpMap);

#pragma endregion

#pragma region HUD

	// -- TEXT TIMER --
	r->LoadFont({ F_GAMEOVER, P_TTF_GAMEOVER, 100 });

	VEC2 vTemp =r->LoadTextureText(F_GAMEOVER, { T_TXT_TIME, " ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_TXT_TIME, { SCREEN_WIDTH / 2, 10, vTemp.x, vTemp.y });
	
	// -- PLAYER 1 SCORE TXT
	// PL1 SCORE TEXT
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL1_SCORE_TEXT, "PL1: ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL1_SCORE_TEXT, { TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });
	// PL2 SCORE TEXT
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL2_SCORE_TEXT, "PL2: ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL2_SCORE_TEXT, { SCREEN_WIDTH - vTemp.x - vTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });

	// PLAYER 1 SCORE
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL1_SCORE, " ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL1_SCORE, { vTemp.x + TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });
	// PLAYER 2 SCORE
	vTemp = r->LoadTextureText(F_GAMEOVER, { T_PL2_SCORE, " ", { 0,0,0,255 }, 0, 0 });
	r->LoadRect(T_PL2_SCORE, { SCREEN_WIDTH - vTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });

	//// PLAYER 2 SCORE_TEXT

	//Renderer::GetInstance()->LoadTexture(T_PLAYER1, "../../res/img/player1.png");
	//// PLAYER 1 LIVES
	///*Renderer::GetInstance()->GetTextureSize(T_PLAYER1).x, Renderer::GetInstance()->GetTextureSize(T_PLAYER1).y, Player::EPlayerType::PL1
	//	vTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL1_LIVES, " ", { 0,0,0,255 }, 0, 0 });
	//Renderer::GetInstance()->LoadRect(T_PL1_LIVES, { vP1SCTemp.x, 0, vTemp.x, vTemp.y });*/

	//Renderer::GetInstance()->LoadTexture(T_PLAYER2, "../../res/img/player2.png");
	//// PLAYER 2 LIVES
	///*vTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL2_LIVES, " ", { 0,0,0,255 }, 0, 0 });
	//Renderer::GetInstance()->LoadRect(T_PL2_LIVES, { vP2SCTTemp, 0, vTemp.x, vTemp.y });
	//PLAYER2_LIVES_WIDTH = vTemp.x;*/

#pragma endregion

#pragma region Sprite

	//-->PLAYERS
	// -- Player1 --
	Renderer::GetInstance()->LoadTexture(T_PLAYER1, P_PLAYER1);
	int l = 0;
	AddPlayer({ (levels.at(0)->GetPlayer()->at(l).GetPosition()->x * SPRITE_RES) + SPRITE_RES, 
		(levels.at(0)->GetPlayer()->at(l).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL1);
	// -- Player2 --
	Renderer::GetInstance()->LoadTexture(T_PLAYER2, P_PLAYER2);
	l = 1;
	AddPlayer({ (levels.at(0)->GetPlayer()->at(l).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
		(levels.at(0)->GetPlayer()->at(l).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL2);


	//Walls
	Renderer::GetInstance()->LoadTexture(T_ITEMS, P_ITEMS);
	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int j = 0;  j < MAP_COLS; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				AddWall({ (levels.at(0)->GetWall()->at(k).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
					(levels.at(0)->GetWall()->at(k).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, 
					false/*levels.at(0)->GetWall()->at(k).GetDestructible()*/);
			}
		}
	}
	// INSERTAR FOR DE TODAS LAS WALLS---------------------------
	//for (int k = 0; k < levels.size(); k++)
	//{
	//	for (int i = 0; i < MAP_ROWS; i++)
	//	{
	//		int p = 0;
	//		for (int j = 0; j < MAP_COLS; j++)
	//		{
	//			while (p < levels.at(k)->GetWall()->size())
	//			{
	//				if (i == levels.at(k)->GetWall()->at(p).GetPosition()->x && j == levels.at(k)->GetWall()->at(p).GetPosition()->y)
	//				{
	//					AddWall({ i,j }, levels.at(k)->GetWall()->at(p).GetDestructibleWall());
	//				}
	//				p++;
	//			}

	//		}
	//	}

	//}

	//AddWall({ 500,500 }, levels.at(0)->GetWall()->at(62).GetDestructible());
	//AddWall({ 500,600 }, levels.at(0)->GetWall()->at(25).GetDestructible());

	//PowerUps
	AddPowerUp({ 300,500 }, PowerUp::EPowerUpType::SKATES);
	AddPowerUp({ 300,600 }, PowerUp::EPowerUpType::HELMET);

	//Bomb
	
#pragma endregion

	//-->AUDIO
	//au->LoadAudio(S_GAME_THEME, P_GAME_THEME);
}

Play::~Play() {}

void Play::ReadMap()
{
}

void Play::AddPlayer(VEC2 pos, Player::EPlayerType type)
{
	Player* p = new Player();
	p->SetPlayerValues({ pos.x, pos.y }, type);
	players.push_back(p);
}

void Play::AddWall(VEC2 pos, bool _destr)
{
	Wall* w = new Wall();
	w->SetValues({ pos.x, pos.y }, _destr);
	walls.push_back(w);
}

void Play::AddPowerUp(VEC2 pos, PowerUp::EPowerUpType type)
{
	PowerUp* pw = new PowerUp();
	pw->SetValues({ pos.x, pos.y }, type);
	powerUps.push_back(pw);
}

void Play::Update()
{
	for (Player* p : players)
		p->Update(InputManager::GetInstance());
	
	// AQUI COLISIONES DEL PLAYER PERO NO SÉ SI INPUT TIENE QUE IR
	// DE MOMENTO PONEMOS EL INPUT CON SUS COLISIONES AQUI :)
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
	// -- LEVEL 1 --
	//for (int i = 0; i < MAP_ROWS; i++)
	//{
	//	for (int j = 0; j < MAP_COLS; j++)
	//	{
	//		//if (levels.at(j).IsPlayer({ i,j }, j)) {}
	//		//Renderer::GetInstance()->PushImage()
	//		//if (levels.at(0).IsNotDestructibleWall())
	//	}
	//}
	// -- LEVEL 2 -- 
	
	//-->PLAYERS
	r->PushSprite(T_PLAYER1, players.at(0)->GetFrame(), players.at(0)->GetPosition());
	r->PushSprite(T_PLAYER2, players.at(1)->GetFrame(), players.at(1)->GetPosition());
	
	//-->WALLS
	//r->PushSprite(T_ITEMS, walls.at(0)->GetFrame(), walls.at(0)->GetPosition());
	//r->PushSprite(T_ITEMS, walls.at(1)->GetFrame(), walls.at(1)->GetPosition());
	
	for (Wall* w: walls)
		r->PushSprite(T_ITEMS, w->GetFrame(), w->GetPosition());
	// -- Desctructible Walls --
	// -- Not desctructible Walls --

	//-->POWERUPS
	for (PowerUp* pw : powerUps)
		r->PushSprite(T_ITEMS, pw->GetFrame(), pw->GetPosition());

	//-->BOMB
	// -- Bomb --
	// -- Explosion Bomb --
}