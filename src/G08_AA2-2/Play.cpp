#include "Play.h"

Play::Play(Map::ELevelType _map)
{
	// -- Background --
	r->LoadTexture(T_BG, P_BG);
	r->LoadRect(T_BG, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	#pragma region GRID

	map = new Map(_map);
	
#pragma endregion

	#pragma region HUD

	timeDown = MAX_GAMETIME;

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

	#pragma region SPRITES
	Renderer::GetInstance()->LoadTexture(T_PL1_LIVES, P_PLAYER1);	//SC PL1
	Renderer::GetInstance()->LoadTexture(T_PL2_LIVES, P_PLAYER2);	//SC PL2
	pl1_life_frame = { 48, 96, 48, 48 };
	pl1_life_position = { SPRITE_RES * 3, TEXT_HUD_VERTICAL_SPACING * 2, SPRITE_RES, SPRITE_RES };
	pl2_life_frame = { 48, 96, 48, 48 };
	pl2_life_position = { SCREEN_WIDTH - SPRITE_RES * 5, TEXT_HUD_VERTICAL_SPACING * 2, SPRITE_RES, SPRITE_RES };

	Renderer::GetInstance()->LoadTexture(T_PLAYER1, P_PLAYER1);		//PL1 CHARACTER
	Renderer::GetInstance()->LoadTexture(T_PLAYER2, P_PLAYER2);		//PL2 CHARACTER
	Renderer::GetInstance()->LoadTexture(T_ITEMS, P_ITEMS);			//ITEMS
	Renderer::GetInstance()->LoadTexture(T_EXPLOSION, P_EXPLOSION);			//BOMB EXPLOSION

	AddPlayer({ (map->GetPlayer()->at(0).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
		(map->GetPlayer()->at(0).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES },

		Player::EPlayerType::PL1, map->GetPlayer()->at(0).GetLives());
	initPlayer1Pos = *map->GetPlayer()->at(0).GetPosition();

	AddPlayer({ (map->GetPlayer()->at(1).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
		(map->GetPlayer()->at(1).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES },

		Player::EPlayerType::PL2, map->GetPlayer()->at(1).GetLives());
	initPlayer2Pos = *map->GetPlayer()->at(1).GetPosition();

	for (int i = 0; i < map->GetWall()->size(); i++)
	{
		AddWall({ (map->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
			(map->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, map->GetWall()->at(i).destructible);
	}

	AddBomb({ 0, 0 }, player.at(0)->GetPlayerType());
	AddBomb({ 0, 0 }, player.at(1)->GetPlayerType());

	AddExplosion({ 0, 0 }, player.at(0)->GetPlayerType());
	AddExplosion({ 0, 0 }, player.at(1)->GetPlayerType());
#pragma endregion
}

Play::~Play() 
{
	player.clear();
	walls.clear();
	explosionBomb1.clear();
	explosionBomb2.clear();
	powerUps.clear();
	delete map;
}

void Play::Update(InputManager& input)
{	
	timeDown -= *input.GetDeltaTime();
	if (timeDown <= 0.f || player.at(0)->GetLives() <= 0 || player.at(1)->GetLives() <= 0) state = ESceneState::CLICK_RANKING;
	else
	{
		// Timer
		std::string s = F2StrFormat(trunc(timeDown / 60), 0);
		s += ":" + F2StrFormat(static_cast<int>(timeDown) % 60, 0);
		VEC2 vTemp = r->LoadTextureText(F_GAMEOVER, { T_TXT_TIME, s.c_str(), { 0,0,0,255 }, 0, 0 });
		r->LoadRect(T_TXT_TIME, { SCREEN_WIDTH / 2 - vTemp.x, 10, vTemp.x, vTemp.y });
	}

	for (Player* p : player)
	{
		p->Update(&input);

		for (PowerUp* pw : powerUps)
		{
			if (Collisions::ExistCollision(*p->GetPosition(), *pw->GetPosition()) && pw->isActive)
			{
				pw->isActive = false;
				p->SetBuff(pw->GetType());
			}
		}

		//Collision Player-Wall
		for (int i = 0; i < map->GetWall()->size(); i++)
		{
			if (Collisions::ExistCollision(*p->GetPosition(),
				{ (map->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
				(map->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
				(map->GetWall()->at(i).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
				(map->GetWall()->at(i).GetPosition()->h * SPRITE_RES) + SPRITE_RES }) && !map->GetWall()->at(i).destructed)
			{
				p->movementCheck = false;
			}
		}

		for (int i = 0; i < EXPLOSION_BLOCKS; i++)
		{
			if (Collisions::ExistCollision(*explosionBomb1.at(i)->GetPosition(),
				{ p->GetPosition()->x,
				p->GetPosition()->y,
				p->GetPosition()->w,
				p->GetPosition()->h }) && explosionBomb1.at(i)->exploding
				&& !p->immunity)
			{
				if (p->GetPlayerType() == Player::EPlayerType::PL1 && !p->bomb1DmgDone)
				{
					p->ResetPos({ initPlayer1Pos.x, initPlayer1Pos.y });
					p->RestLives(1);
					p->bomb1DmgDone = true;
				}
				else if (p->GetPlayerType() == Player::EPlayerType::PL2 && !p->bomb1DmgDone)
				{
					p->ResetPos({ initPlayer2Pos.x, initPlayer2Pos.y });
					p->RestLives(1);
					player.at(0)->AddScore(KILL_PLAYER_SCORE);
					p->bomb1DmgDone = true;
				}
			}
			if (Collisions::ExistCollision(*explosionBomb2.at(i)->GetPosition(),
				{ p->GetPosition()->x,
				p->GetPosition()->y,
				p->GetPosition()->w,
				p->GetPosition()->h }) && explosionBomb2.at(i)->exploding)
			{
				if (p->GetPlayerType() == Player::EPlayerType::PL1 && !p->bomb2DmgDone)
				{
					p->ResetPos({ initPlayer1Pos.x, initPlayer1Pos.y });
					p->RestLives(1);
					player.at(1)->AddScore(KILL_PLAYER_SCORE);
					p->bomb2DmgDone = true;
				}
				else if (p->GetPlayerType() == Player::EPlayerType::PL2 && !p->bomb2DmgDone)
				{
					p->ResetPos({ initPlayer2Pos.x, initPlayer2Pos.y });
					p->RestLives(1);
					p->bomb2DmgDone = true;
				}
			}
		}

		//Bomb & Explosion Control & Update
		if (p->GetPlayerType() == Player::EPlayerType::PL1)
		{
			if (p->colocateBomb && !p->bombPlanted)
			{
				p->colocateBomb = false;
				p->bombPlanted = true;
				bomb1.planted = true;
				bomb1.SetBomb({ p->GetPosition()->x, p->GetPosition()->y });
			}

			if (bomb1.planted)
				bomb1.Update();

			//Check if explosion must start
			if (bomb1.exploded && !explosionBomb1.at(0)->exploding)
			{
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					int j = 0;
					for (; j < map->GetWall()->size(); j++)
					{
						explosionBomb1.at(i)->SetExplosionPosition(bomb1.GetPosition(), explosionBomb1.at(i)->GetExplosionType());
						if (Collisions::ExistCollision(*explosionBomb1.at(i)->GetPosition(),
							{ (map->GetWall()->at(j).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
							(map->GetWall()->at(j).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
							(map->GetWall()->at(j).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
							(map->GetWall()->at(j).GetPosition()->h * SPRITE_RES) + SPRITE_RES }) && !map->GetWall()->at(j).destructed)
						{
							explosionBomb1.at(i)->exploding = false;
							if (i == 1)
								explosionBomb1.at(5)->edgeExplodes = false;
							else if (i == 2)
								explosionBomb1.at(6)->edgeExplodes = false;
							else if (i == 3)
								explosionBomb1.at(7)->edgeExplodes = false;
							else if (i == 4)
								explosionBomb1.at(8)->edgeExplodes = false;
							if (map->GetWall()->at(j).destructible)
							{
								//map.at(1)->GetWall()->erase(j);
								//AQUI FEM SETVALUES DEL POWER-UP
								if (i == 5 && !explosionBomb1.at(i)->edgeExplodes)	{}
								else if (i == 6 && !explosionBomb1.at(i)->edgeExplodes) {}
								else if (i == 7 && !explosionBomb1.at(i)->edgeExplodes) {}
								else if (i == 8 && !explosionBomb1.at(i)->edgeExplodes) {}
								else
								{
									map->GetWall()->at(j).destructed = true;
									walls.at(j)->destructed = true;
									player.at(0)->AddScore(DESTROY_WALL_SCORE);
									AddPowerUp({ map->GetWall()->at(j).GetPosition()->x, map->GetWall()->at(j).GetPosition()->y });
								}
							}
							j = map->GetWall()->size();
							//std::cout << "Wall N: " << j << " collided with explosion N: " << i << std::endl;
						}
						else if (explosionBomb1.at(i)->GetPosition()->x < SPRITE_RES ||						//Left border of the map
							explosionBomb1.at(i)->GetPosition()->x + explosionBomb1.at(i)->GetPosition()->w > SCREEN_WIDTH - SPRITE_RES ||			//Right border of the map
							explosionBomb1.at(i)->GetPosition()->y < SPRITE_HUD_HEIGHT + SPRITE_RES ||		//top border of the map
							explosionBomb1.at(i)->GetPosition()->y + explosionBomb1.at(i)->GetPosition()->h > SCREEN_HEIGHT - SPRITE_RES)			//bottom border of the map
						{
							explosionBomb1.at(i)->exploding = false;
							if (i == 1)
								explosionBomb1.at(5)->exploding = false;
							else if (i == 2)
								explosionBomb1.at(6)->exploding = false;
							else if (i == 3)
								explosionBomb1.at(7)->exploding = false;
							else if (i == 4)
								explosionBomb1.at(8)->exploding = false;
						}
						else
						{
							if (i == 5 && !explosionBomb1.at(i)->edgeExplodes)
							{
								explosionBomb1.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else if (i == 6 && !explosionBomb1.at(i)->edgeExplodes)
							{
								explosionBomb1.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else if (i == 7 && !explosionBomb1.at(i)->edgeExplodes)
							{
								explosionBomb1.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else if (i == 8 && !explosionBomb1.at(i)->edgeExplodes)
							{
								explosionBomb1.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else
							explosionBomb1.at(i)->exploding = true;
						}
					}
				}
			}

			if (explosionBomb1.at(0)->exploding)
			{
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					explosionBomb1.at(i)->UpdateSprite(bomb1.GetDeltaBombTick());
				}
			}

			if (!bomb1.planted && !bomb1.flickering && !bomb1.exploded)
			{
				p->bombPlanted = false;
				p->bomb1DmgDone = false;
				p->bomb2DmgDone = false;
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					explosionBomb1.at(i)->exploding = false;
				}
			}

		}
		else if (p->GetPlayerType() == Player::EPlayerType::PL2)
		{
			if (p->colocateBomb && !p->bombPlanted)
			{
				p->colocateBomb = false;
				p->bombPlanted = true;
				bomb2.planted = true;
				bomb2.SetBomb({ p->GetPosition()->x, p->GetPosition()->y });
			}

			if (bomb2.planted)
				bomb2.Update();

			//Check if explosion must start
			if (bomb2.exploded && !explosionBomb2.at(0)->exploding)
			{
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					int j = 0;
					for (; j < map->GetWall()->size(); j++)
					{
						explosionBomb2.at(i)->SetExplosionPosition(bomb2.GetPosition(), explosionBomb2.at(i)->GetExplosionType());
						if (Collisions::ExistCollision(*explosionBomb2.at(i)->GetPosition(),
							{ (map->GetWall()->at(j).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
							(map->GetWall()->at(j).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
							(map->GetWall()->at(j).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
							(map->GetWall()->at(j).GetPosition()->h * SPRITE_RES) + SPRITE_RES })
							&& !map->GetWall()->at(j).destructed)
						{
							explosionBomb2.at(i)->exploding = false;
							if (i == 1)
								explosionBomb2.at(5)->edgeExplodes = false;
							else if (i == 2)
								explosionBomb2.at(6)->edgeExplodes = false;
							else if (i == 3)
								explosionBomb2.at(7)->edgeExplodes = false;
							else if (i == 4)
								explosionBomb2.at(8)->edgeExplodes = false;
							if (map->GetWall()->at(j).destructible)
							{
								if (i == 5 && !explosionBomb2.at(i)->edgeExplodes) {}
								else if (i == 6 && !explosionBomb2.at(i)->edgeExplodes) {}
								else if (i == 7 && !explosionBomb2.at(i)->edgeExplodes) {}
								else if (i == 8 && !explosionBomb2.at(i)->edgeExplodes) {}
								else
								{
									map->GetWall()->at(j).destructed = true;
									walls.at(j)->destructed = true;
									player.at(1)->AddScore(DESTROY_WALL_SCORE);
									AddPowerUp({ map->GetWall()->at(j).GetPosition()->x, map->GetWall()->at(j).GetPosition()->y });
								}
							}
							j = map->GetWall()->size();
						}
						else if (explosionBomb2.at(i)->GetPosition()->x < SPRITE_RES ||						//Left border of the map
							explosionBomb2.at(i)->GetPosition()->x + explosionBomb2.at(i)->GetPosition()->w > SCREEN_WIDTH - SPRITE_RES ||			//Right border of the map
							explosionBomb2.at(i)->GetPosition()->y < SPRITE_HUD_HEIGHT + SPRITE_RES ||		//top border of the map
							explosionBomb2.at(i)->GetPosition()->y + explosionBomb2.at(i)->GetPosition()->h > SCREEN_HEIGHT - SPRITE_RES)			//bottom border of the map
						{
							explosionBomb2.at(i)->exploding = false;
							if (i == 1)
								explosionBomb2.at(5)->exploding = false;
							else if (i == 2)
								explosionBomb2.at(6)->exploding = false;
							else if (i == 3)
								explosionBomb2.at(7)->exploding = false;
							else if (i == 4)
								explosionBomb2.at(8)->exploding = false;
						}
						else
						{
							if (i == 5 && !explosionBomb2.at(i)->edgeExplodes)
							{
								explosionBomb2.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else if (i == 6 && !explosionBomb2.at(i)->edgeExplodes)
							{
								explosionBomb2.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else if (i == 7 && !explosionBomb2.at(i)->edgeExplodes)
							{
								explosionBomb2.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else if (i == 8 && !explosionBomb2.at(i)->edgeExplodes)
							{
								explosionBomb2.at(i)->exploding = false;
								j = map->GetWall()->size();
							}
							else
								explosionBomb2.at(i)->exploding = true;
						}
					}
				}
			}

			if (explosionBomb2.at(0)->exploding)
			{
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					explosionBomb2.at(i)->UpdateSprite(bomb2.GetDeltaBombTick());
				}
			}

			if (!bomb2.planted && !bomb2.flickering && !bomb2.exploded)
			{
				p->bombPlanted = false;
				p->bomb1DmgDone = false;
				p->bomb2DmgDone = false;
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					explosionBomb2.at(i)->exploding = false;
				}
			}
		}

		//Second check for player Collisions
		p->UpdateCheck(&input);
	}
	//Score Player 1
	std::string sp1 = F2StrFormat(player.at(0)->GetScore(), 0);
	VEC2 vTemp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { T_PL1_SCORE, sp1.c_str(), { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL1_SCORE, { TEXT_HUD_HORIZONTAL_SPACING + 70, TEXT_HUD_VERTICAL_SPACING, vTemp.x, vTemp.y });

	//Score Player 2
	std::string sp2 = F2StrFormat(player.at(1)->GetScore(), 0);
	VEC2 vTemp2 = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { T_PL2_SCORE, sp2.c_str(), { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL2_SCORE, { SCREEN_WIDTH - vTemp2.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vTemp2.x, vTemp2.y });

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
	//map->Draw(map->GetType());
	for (Wall* w : walls)
		w->Draw();

	for (PowerUp* pw : powerUps)
		pw->Draw();

	for (Player* p : player)
	{
		//Bomb 1
		//First 2 sec
		if (player.at(0)->GetPlayerType() == Player::EPlayerType::PL1 && bomb1.planted && !bomb1.flickering && !bomb1.exploded)
			Renderer::GetInstance()->PushSprite(T_ITEMS, bomb1.GetFrame(), bomb1.GetPosition());
		//Flickering 3rd second
		else if (player.at(0)->GetPlayerType() == Player::EPlayerType::PL1 && bomb1.planted && bomb1.flickering && !bomb1.exploded &&
			(bomb1.GetDeltaBombTick() > 2.f && bomb1.GetDeltaBombTick() <= 2.2f) ||
			(bomb1.GetDeltaBombTick() > 2.4f && bomb1.GetDeltaBombTick() <= 2.6f) ||
			(bomb1.GetDeltaBombTick() > 2.8f && bomb1.GetDeltaBombTick() < 3.f))
			Renderer::GetInstance()->PushSprite(T_ITEMS, bomb1.GetFrame(), bomb1.GetPosition());
		//Exploding 4th second
		for (int i = 0; i < EXPLOSION_BLOCKS; i++)
		{
			if (player.at(0)->GetPlayerType() == Player::EPlayerType::PL1 && explosionBomb1.at(i)->exploding)
				Renderer::GetInstance()->PushSprite(T_EXPLOSION, explosionBomb1.at(i)->GetFrame(), explosionBomb1.at(i)->GetPosition());
		}
		//Bomb 2
		//First 2 sec
		if (player.at(1)->GetPlayerType() == Player::EPlayerType::PL2 && bomb2.planted && !bomb2.flickering && !bomb2.exploded)
			Renderer::GetInstance()->PushSprite(T_ITEMS, bomb2.GetFrame(), bomb2.GetPosition());
		//Flickering 3rd second
		else if (player.at(1)->GetPlayerType() == Player::EPlayerType::PL2 && bomb2.planted && bomb2.flickering && !bomb2.exploded &&
			(bomb2.GetDeltaBombTick() > 2.f && bomb2.GetDeltaBombTick() <= 2.2f) || (bomb2.GetDeltaBombTick() > 2.4f && bomb2.GetDeltaBombTick() <= 2.6f) ||
			(bomb2.GetDeltaBombTick() > 2.8f && bomb2.GetDeltaBombTick() < 3.f))
			Renderer::GetInstance()->PushSprite(T_ITEMS, bomb2.GetFrame(), bomb2.GetPosition());
		//Exploding 4th second
		for (int i = 0; i < EXPLOSION_BLOCKS; i++)
		{
			if (player.at(1)->GetPlayerType() == Player::EPlayerType::PL2 && explosionBomb2.at(i)->exploding)
			{
				Renderer::GetInstance()->PushSprite(T_EXPLOSION, explosionBomb2.at(i)->GetFrame(), explosionBomb2.at(i)->GetPosition());
			}
		}
	}
	for (int i = 0; i < player.at(0)->GetLives(); i++)
	{
		pl1_life_position.x = SPRITE_RES * 3.5f;
		pl1_life_position.x += SPRITE_RES * i;
		Renderer::GetInstance()->PushSprite(T_PL1_LIVES, &pl1_life_frame, &pl1_life_position);
	}
	for (int i = 0; i < player.at(1)->GetLives(); i++)
	{
		pl2_life_position.x = SCREEN_WIDTH - SPRITE_RES * 5;
		pl2_life_position.x -= SPRITE_RES * i;
		Renderer::GetInstance()->PushSprite(T_PL2_LIVES, &pl2_life_frame, &pl2_life_position);
	}

	Renderer::GetInstance()->PushSprite(T_PLAYER1, player.at(0)->GetFrame(), player.at(0)->GetPosition());
	Renderer::GetInstance()->PushSprite(T_PLAYER2, player.at(1)->GetFrame(), player.at(1)->GetPosition());

}

void Play::AddPlayer(VEC2 pos, Player::EPlayerType type, int lives)
{
	Player* p = new Player();
	p->SetPlayerValues({ pos.x, pos.y }, type);
	p->SetLive(lives);
	player.push_back(p);
}

void Play::AddWall(VEC2 pos, bool des)
{
	Wall* w = new Wall();

	w->SetValues({ pos.x, pos.y }, des);

	walls.push_back(w);
}

void Play::AddBomb(VEC2 pos, Player::EPlayerType type)
{
	switch (type)
	{
	case Player::EPlayerType::PL1:
		bomb1.SetValues({ pos.x, pos.y });
		break;
	case Player::EPlayerType::PL2:
		bomb2.SetValues({ pos.x, pos.y });
		break;
	default:
		break;
	}
}

void Play::AddExplosion(VEC2 bombPos, Player::EPlayerType type)
{
	for (int i = 0; i < EXPLOSION_BLOCKS; i++)
	{
		Explosion* ex = new Explosion();
		ex->SetValues({ bombPos.x, bombPos.y }, i);
		switch (type)
		{
		case Player::EPlayerType::PL1:
			explosionBomb1.push_back(ex);
			break;
		case Player::EPlayerType::PL2:
			explosionBomb2.push_back(ex);
			break;
		default:
			break;
		}
	}
}

void Play::AddPowerUp(VEC2 wallPos)
{
	PowerUp* pow = new PowerUp();
	pow->SetValues({ (wallPos.x * SPRITE_RES) + SPRITE_RES, (wallPos.y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES });
	powerUps.push_back(pow);
}