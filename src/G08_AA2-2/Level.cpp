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

		/*AddBomb({ 0, 0 }, player.at(0)->GetPlayerType());
		AddBomb({ 0, 0 }, player.at(1)->GetPlayerType());*/
		AddBomb({ 0, 0 }, player.at(0)->GetPlayerType());
		AddBomb({ 0, 0 }, player.at(1)->GetPlayerType());

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

		/*AddBomb({ 0, 0 }, map.at(1)->GetPlayer()->at(0).GetPlayerType());
		AddBomb({ 0, 0 }, map.at(1)->GetPlayer()->at(1).GetPlayerType());*/
		AddBomb({ 0, 0 }, player.at(0)->GetPlayerType());
		AddBomb({ 0, 0 }, player.at(1)->GetPlayerType());

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

			if (!bomb1.planted && !bomb1.flickering && !bomb1.exploded)
				p->bombPlanted = false;

			std::cout << "Planted:" << bomb1.planted << std::endl;
			std::cout << "Flickering:" << bomb1.flickering << std::endl;
			std::cout << "Exploded:" << bomb1.exploded << std::endl;
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

			if (!bomb2.planted && !bomb2.flickering && !bomb2.exploded)
				p->bombPlanted = false;
		}

		p->UpdateCheck(InputManager::GetInstance());
	}
}

void Level::Draw(ELevelType _type)
{
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
	for (Wall *w : walls)
		Renderer::GetInstance()->PushSprite(T_ITEMS, w->GetFrame(), w->GetPosition());
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