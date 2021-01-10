#include "Level.h"

Level::Level(ELevelType _type)
{
	type = _type;

	// -- Read XML file --
	rapidxml::xml_document<> doc;		
	std::ifstream file(P_CONFIG);		
	std::stringstream buffer;			
	buffer << file.rdbuf();				
	file.close();						
	std::string content(buffer.str());	
	doc.parse<0>(&content[0]);			

	rapidxml::xml_node<>* pGame = doc.first_node();

	//std::cout << doc.first_node()->name() << "\n";
	for (rapidxml::xml_node<>* pLevel = pGame->first_node(); pLevel; pLevel = pLevel->next_sibling())
	{
		Map *tmpMap = new Map();
		//std::cout << "\t" << pLevel->name() << "\n";
		//std::cout << "\t\t" << pLevel->first_node("Players")->name() << "\n";

		rapidxml::xml_node<>* pPlayers = pLevel->first_node("Players");
		for (rapidxml::xml_node<>* pPlayer = pPlayers->first_node(); pPlayer; pPlayer = pPlayer->next_sibling())
		{
			Player tmpPlayer;

			tmpPlayer.SetLive(atoi(pPlayer->first_attribute()->value()));
			tmpPlayer.SetPosition(RECT(atoi(pPlayer->first_node()->first_attribute("x")->value()), atoi(pPlayer->first_node()->first_attribute("y")->value())));

			//std::cout << "\t\t\t" << pPlayer->name() << "\n";
			//std::cout << "\t\t\t\t" << pPlayer->first_attribute()->name() << ':' << pPlayer->first_attribute("lives")->value() << "\n";
			//std::cout << "\t\t\t\t" << pPlayer->first_node()->name() << "\n";
			//std::cout << "\t\t\t\t\t" << pPlayer->first_node()->first_attribute("x")->name() << ':' << pPlayer->first_node()->first_attribute("x")->value() << "\n";
			//std::cout << "\t\t\t\t\t" << pPlayer->first_node()->first_attribute("y")->name() << ':' << pPlayer->first_node()->first_attribute("y")->value() << "\n";
			
			tmpMap->GetPlayer()->push_back(tmpPlayer);
		}

		//std::cout << "\t\t" << pLevel->first_node("Map")->name() << "\n";

		rapidxml::xml_node<>* pMaps = pLevel->first_node("Map");
		for (rapidxml::xml_node<>* pMap = pMaps->first_node(); pMap; pMap = pMap->next_sibling())
		{
			Wall tmpWall;

			tmpWall.SetPosition(RECT(atoi(pMap->first_attribute("x")->value()), atoi(pMap->first_attribute("y")->value())));

			std::string sTmp = pMap->first_attribute("destructible")->value();
			if (sTmp == "false")
			{
				//tmpMap->SetCell({ tmpWall.GetPosition()->y , tmpWall.GetPosition()->x}, Map::Cell::WALLINDES);
				//tmpWall.SetDestructible(false);
				tmpWall.destructible = false;
			}
			else if (sTmp == "true")
			{
				//tmpMap->SetCell({ tmpWall.GetPosition()->y , tmpWall.GetPosition()->x }, Map::Cell::WALLDES);
				//tmpWall.SetDestructible(true);
				tmpWall.destructible = true;
			}

			//std::cout << "\t\t\t" << pMap->name() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("destructible")->name() << ':' << tmpWall.GetDestructible() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("x")->name() << ':' << pMap->first_attribute("x")->value() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("y")->name() << ':' << pMap->first_attribute("y")->value() << "\n";
			
			tmpMap->GetWall()->push_back(tmpWall);
		}
		map.push_back(tmpMap);
	}
	
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

	switch (_type)
	{
	case ELevelType::LEVEL1:

		AddPlayer({ (map.at(0)->GetPlayer()->at(0).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
		(map.at(0)->GetPlayer()->at(0).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL1);
		
		AddPlayer({ (map.at(0)->GetPlayer()->at(1).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
			(map.at(0)->GetPlayer()->at(1).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL2);

		for (int i = 0; i < map.at(0)->GetWall()->size(); i++)
		{
			AddWall({ (map.at(0)->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
				(map.at(0)->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, map.at(0)->GetWall()->at(i).destructible);
		}

		AddBomb({ 0, 0 }, player.at(0)->GetPlayerType());
		AddBomb({ 0, 0 }, player.at(1)->GetPlayerType());

		AddExplosion({ 0, 0 }, player.at(0)->GetPlayerType());
		AddExplosion({ 0, 0 }, player.at(1)->GetPlayerType());

		break;
	case ELevelType::LEVEL2:

		AddPlayer({ (map.at(1)->GetPlayer()->at(0).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
			(map.at(1)->GetPlayer()->at(0).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL1);

		AddPlayer({ (map.at(1)->GetPlayer()->at(1).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
			(map.at(1)->GetPlayer()->at(1).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL2);

		for (int i = 0; i < map.at(1)->GetWall()->size(); i++)
		{
			AddWall({ (map.at(1)->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
				(map.at(1)->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, map.at(1)->GetWall()->at(i).destructible);
		}

		AddBomb({ 0, 0 }, player.at(0)->GetPlayerType());
		AddBomb({ 0, 0 }, player.at(1)->GetPlayerType());

		AddExplosion({ 0, 0 }, player.at(0)->GetPlayerType());
		AddExplosion({ 0, 0 }, player.at(1)->GetPlayerType());

		break;
	}
}

Level::~Level()
{
	map.clear();
}

void Level::InitLevelScene(ELevelType _type)
{
	switch (_type)
	{
	case ELevelType::LEVEL1:
		break;
	case ELevelType::LEVEL2:
		break;
	}
}

void Level::Update(ELevelType _type)
{
	for (Player* p : player)
	{
		p->Update(InputManager::GetInstance());
		
		//Collision Player-Wall
		switch (_type)
		{
		case ELevelType::LEVEL1:
			for (int i = 0; i < map.at(0)->GetWall()->size(); i++)
			{
				if (Collisions::ExistCollision(*p->GetPosition(),
					{ (map.at(0)->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
					(map.at(0)->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
					(map.at(0)->GetWall()->at(i).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
					(map.at(0)->GetWall()->at(i).GetPosition()->h * SPRITE_RES) + SPRITE_RES }))
				{
					p->movementCheck = false;
				}
			}
			break;
		case ELevelType::LEVEL2:
			for (int i = 0; i < map.at(1)->GetWall()->size(); i++)
			{
				if (Collisions::ExistCollision(*p->GetPosition(),
					{ (map.at(1)->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
					(map.at(1)->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
					(map.at(1)->GetWall()->at(i).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
					(map.at(1)->GetWall()->at(i).GetPosition()->h * SPRITE_RES) + SPRITE_RES }))
				{
					p->movementCheck = false;
				}
			}
			break;
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
				for (int i = EXPLOSION_BLOCKS - 1; i >= 0; i--)
				{
					int j = 0;
					for (; j < map.at(0)->GetWall()->size(); j++)
					{
						explosionBomb1.at(i)->SetExplosionPosition(bomb1.GetPosition(), explosionBomb1.at(i)->GetExplosionType());
						if (Collisions::ExistCollision(*explosionBomb1.at(i)->GetPosition(),
							{ (map.at(0)->GetWall()->at(j).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
							(map.at(0)->GetWall()->at(j).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
							(map.at(0)->GetWall()->at(j).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
							(map.at(0)->GetWall()->at(j).GetPosition()->h * SPRITE_RES) + SPRITE_RES }))
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
							j = map.at(0)->GetWall()->size();
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
				for (int i = EXPLOSION_BLOCKS - 1; i >= 0; i--)
				{
					int j = 0;
					for (; j < map.at(0)->GetWall()->size(); j++)
					{
						explosionBomb2.at(i)->SetExplosionPosition(bomb2.GetPosition(), explosionBomb2.at(i)->GetExplosionType());
						if (Collisions::ExistCollision(*explosionBomb2.at(i)->GetPosition(),
							{ (map.at(0)->GetWall()->at(j).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
							(map.at(0)->GetWall()->at(j).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES,
							(map.at(0)->GetWall()->at(j).GetPosition()->w * SPRITE_RES) + SPRITE_RES,
							(map.at(0)->GetWall()->at(j).GetPosition()->h * SPRITE_RES) + SPRITE_RES }))
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
							j = map.at(0)->GetWall()->size();
							//std::cout << "Wall N: " << j << " collided with explosion N: " << i << std::endl;
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
				for (int i = 0; i < EXPLOSION_BLOCKS; i++)
				{
					explosionBomb2.at(i)->exploding = false;
				}
			}
		}

		//Second check for player Collisions
		p->UpdateCheck(InputManager::GetInstance());
	}
}

void Level::Draw(ELevelType _type)
{
	for (Wall* w : walls)
		Renderer::GetInstance()->PushSprite(T_ITEMS, w->GetFrame(), w->GetPosition());
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
			(bomb2.GetDeltaBombTick() > 2.f && bomb2.GetDeltaBombTick() <= 2.2f) ||	(bomb2.GetDeltaBombTick() > 2.4f && bomb2.GetDeltaBombTick() <= 2.6f) ||
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
	for (int i = 0; i < map.at(0)->GetPlayer()->at(0).GetLives(); i++)
	{
		pl1_life_position.x = SPRITE_RES * 3;
		pl1_life_position.x += SPRITE_RES * i;
		Renderer::GetInstance()->PushSprite(T_PL1_LIVES, &pl1_life_frame, &pl1_life_position);
	}
	for (int i = 0; i < map.at(0)->GetPlayer()->at(1).GetLives(); i++)
	{
		pl2_life_position.x = SCREEN_WIDTH - SPRITE_RES * 5;
		pl2_life_position.x -= SPRITE_RES * i;
		Renderer::GetInstance()->PushSprite(T_PL2_LIVES, &pl2_life_frame, &pl2_life_position);
	}
	
	Renderer::GetInstance()->PushSprite(T_PLAYER1, player.at(0)->GetFrame(), player.at(0)->GetPosition());
	Renderer::GetInstance()->PushSprite(T_PLAYER2, player.at(1)->GetFrame(), player.at(1)->GetPosition());

}

void Level::AddPlayer(VEC2 pos, Player::EPlayerType type)
{
	Player* p = new Player();
	p->SetPlayerValues({ pos.x, pos.y }, type);
	player.push_back(p);
}

void Level::AddWall(VEC2 pos, bool des)
{
	Wall* w = new Wall();

	w->SetValues({ pos.x, pos.y }, des);
	
	walls.push_back(w);
}

void Level::AddBomb(VEC2 pos, Player::EPlayerType type)
{
	//Bomb* b = new Bomb();
	//b->SetValues({ pos.x, pos.y });
	switch (type)
	{
	case Player::EPlayerType::PL1:
		bomb1.SetValues({ pos.x, pos.y });
		//player.at(0)->SetBomb(*b);
		//map.at(0)->GetPlayer()->at(0).SetBomb(*b);
		break;
	case Player::EPlayerType::PL2:
		bomb2.SetValues({ pos.x, pos.y });
		//player.at(1)->SetBomb(*b);
		//map.at(0)->GetPlayer()->at(1).SetBomb(*b);
		break;
	default:
		break;
	}
}

void Level::AddExplosion(VEC2 bombPos, Player::EPlayerType type)
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