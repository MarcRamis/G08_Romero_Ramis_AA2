#include "Level.h"

Level::Level(ELevelType _type)
{
	type = _type;

	// -- Read XML file --
	rapidxml::xml_document<> doc;						// VARIABLE DECLARATION WHERE "doc" IS AN OBJECT FROM xml_document CLASS
	std::ifstream file(P_CONFIG);						// VARIABLE FILE DECLARATION
	std::stringstream buffer;					// BUFFER DECLARATION BECAUSE STRINGSTREAM CAN CONTAIN MASSIVE INFORMATION OF THIS TYPE
	buffer << file.rdbuf();				// SAVE INFORMATION IN BUFFER WHERE "file.rdbuf()" IS A FUNCTION FROM "ifstream" 
	file.close();						// CLOSE FILE BECAUSE WE UPDATED EVERYTHING
	std::string content(buffer.str());	// VARIABLE DECLARATION AND SAVING BUFFER INSIDE. WE DO THIS BECAUSE "doc.parse()" function WORKS WITH STRING NOT STRINGSTREAM
	doc.parse<0>(&content[0]);			// LOOK AT FIRST ELEMENT					

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
				tmpMap->SetCell({ tmpWall.GetPosition()->y , tmpWall.GetPosition()->x}, Map::Cell::WALLINDES);
				tmpWall.SetDestructible(false);
			}
			else if (sTmp == "true")
			{
				tmpMap->SetCell({ tmpWall.GetPosition()->y , tmpWall.GetPosition()->x }, Map::Cell::WALLDES);
				tmpWall.SetDestructible(true);
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
				(map.at(0)->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES });
		}

		break;
	case ELevelType::LEVEL2:

		AddPlayer({ (map.at(1)->GetPlayer()->at(0).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
			(map.at(1)->GetPlayer()->at(0).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL1);

		AddPlayer({ (map.at(1)->GetPlayer()->at(1).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
			(map.at(1)->GetPlayer()->at(1).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES }, Player::EPlayerType::PL2);

		for (int i = 0; i < map.at(1)->GetWall()->size(); i++)
		{
			AddWall({ (map.at(1)->GetWall()->at(i).GetPosition()->x * SPRITE_RES) + SPRITE_RES,
				(map.at(1)->GetWall()->at(i).GetPosition()->y * SPRITE_RES) + SPRITE_HUD_HEIGHT + SPRITE_RES });
		}

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

void Level::Update()
{
	for (Player* p : player)
	{
		p->Update(InputManager::GetInstance());
		
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

		if (p->colocateBomb && !p->bombPlanted)
		{
			p->colocateBomb = false;
			p->bombPlanted = true;
			AddBomb({ p->GetPosition()->x, p->GetPosition()->y }, Bomb::EBombState::NORMAL, p->GetPlayerType());
		}

		if (p->bombPlanted)
			p->GetBomb().Update();
		std::cout << (int)p->GetBomb().GetState() << std::endl;
		p->UpdateCheck(InputManager::GetInstance());
	}
}

void Level::Draw(ELevelType _type)
{
	for (Player* p : player)
	{
		if (p->bombPlanted && p->GetBomb().GetState() == Bomb::EBombState::NORMAL)
			Renderer::GetInstance()->PushSprite(T_ITEMS, p->GetBomb().GetFrame(), p->GetBomb().GetPosition());
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

void Level::AddWall(VEC2 pos)
{
	Wall* w = new Wall();

	w->SetValues({ pos.x, pos.y }, false);
	
	walls.push_back(w);
}

void Level::AddBomb(VEC2 pos, Bomb::EBombState state, Player::EPlayerType type)
{
	Bomb* b = new Bomb();
	b->SetValues({ pos.x, pos.y }, Bomb::EBombState::NORMAL);
	switch (type)
	{
	case Player::EPlayerType::PL1:
		player.at(0)->SetBomb(*b);
		//map.at(0)->GetPlayer()->at(0).SetBomb(*b);
		break;
	case Player::EPlayerType::PL2:
		player.at(1)->SetBomb(*b);
		//map.at(0)->GetPlayer()->at(1).SetBomb(*b);
		break;
	default:
		break;
	}
	//player->GetBomb().SetValues({ pos.x, pos.y }, state);
	//player->SetBomb(*b);
	//powerUps.push_back(pw);
}