#include "Play.h"

Play::Play() 
{
#pragma region GRID
	//ReadMap();


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

	// -- PLAYERS --
	AddPlayer({100,300}, Player::EPlayerType::PL1);
	AddPlayer({200,300}, Player::EPlayerType::PL2);
	
	//Walls
	// INSERTAR FOR DE TODAS LAS WALLS---------------------------
	AddWall({ 500,500 }, false);
	AddWall({ 500,600 }, true);
	
	//PowerUps

	//Bomb
	
#pragma endregion

	//-->AUDIO
	//au->LoadAudio(S_GAME_THEME, P_GAME_THEME);
}

Play::~Play() {}

void Play::ReadMap()
{
	// -- Read XML file --
	rapidxml::xml_document<> doc;						// VARIABLE DECLARATION WHERE "doc" IS AN OBJECT FROM xml_document CLASS
	std::ifstream file(P_CONFIG);	// VARIABLE FILE DECLARATION
	std::stringstream buffer;					// BUFFER DECLARATION BECAUSE STRINGSTREAM CAN CONTAIN MASSIVE INFORMATION OF THIS TYPE
	buffer << file.rdbuf();				// SAVE INFORMATION IN BUFFER WHERE "file.rdbuf()" IS A FUNCTION FROM "ifstream" 
	file.close();						// CLOSE FILE BECAUSE WE UPDATED EVERYTHING
	std::string content(buffer.str());	// VARIABLE DECLARATION AND SAVING BUFFER INSIDE. WE DO THIS BECAUSE "doc.parse()" function WORKS WITH STRING NOT STRINGSTREAM
	doc.parse<0>(&content[0]);			// LOOK AT FIRST ELEMENT					

	rapidxml::xml_node<>* pGame = doc.first_node();

	std::cout << doc.first_node()->name() << "\n";
	for (rapidxml::xml_node<>* pLevel = pGame->first_node(); pLevel; pLevel = pLevel->next_sibling())
	{
		Map tmpMap;
		std::cout << "\t" << pLevel->name() << "\n";
		std::cout << "\t\t" << pLevel->first_node("Players")->name() << "\n";

		rapidxml::xml_node<>* pPlayers = pLevel->first_node("Players");
		for (rapidxml::xml_node<>* pPlayer = pPlayers->first_node(); pPlayer; pPlayer = pPlayer->next_sibling())
		{
			Player tmpPlayer;

			tmpPlayer.SetLive(atoi(pPlayer->first_attribute()->value()));
			tmpPlayer.SetPosition(RECT(atoi(pPlayer->first_node()->first_attribute("x")->value()), atoi(pPlayer->first_node()->first_attribute("y")->value())));

			std::cout << "\t\t\t" << pPlayer->name() << "\n";
			std::cout << "\t\t\t\t" << pPlayer->first_attribute()->name() << ':' << pPlayer->first_attribute("lives")->value() << "\n";
			std::cout << "\t\t\t\t" << pPlayer->first_node()->name() << "\n";
			std::cout << "\t\t\t\t\t" << pPlayer->first_node()->first_attribute("x")->name() << ':' << pPlayer->first_node()->first_attribute("x")->value() << "\n";
			std::cout << "\t\t\t\t\t" << pPlayer->first_node()->first_attribute("y")->name() << ':' << pPlayer->first_node()->first_attribute("y")->value() << "\n";
			
			tmpMap.GetPlayer()->push_back(tmpPlayer);
		}

		std::cout << "\t\t" << pLevel->first_node("Map")->name() << "\n";

		rapidxml::xml_node<>* pMaps = pLevel->first_node("Map");
		for (rapidxml::xml_node<>* pMap = pMaps->first_node(); pMap; pMap = pMap->next_sibling())
		{
			Wall tmpWall;
			tmpWall.SetDestructible(atoi(pMap->first_attribute("destructible")->value()));
			tmpWall.SetPosition(RECT(atoi(pMap->first_attribute("x")->value()), atoi(pMap->first_attribute("y")->value())));

			std::cout << "\t\t\t" << pMap->name() << "\n";
			std::cout << "\t\t\t\t" << pMap->first_attribute("destructible")->name() << ':' << pMap->first_attribute("destructible")->value() << "\n";
			std::cout << "\t\t\t\t" << pMap->first_attribute("x")->name() << ':' << pMap->first_attribute("x")->value() << "\n";
			std::cout << "\t\t\t\t" << pMap->first_attribute("y")->name() << ':' << pMap->first_attribute("y")->value() << "\n";
			
			tmpMap.GetWall()->push_back(tmpWall);
		}
		
		levels.push_back(tmpMap);
	}
}

void Play::AddPlayer(VEC2 pos, Player::EPlayerType type)
{
	Player* p = new Player();
	p->SetPlayerValues({ pos.x, pos.y }, type);
	players.push_back(p);
}

void Play::Update()
{
	for (Player* p : players)
		p->Update(InputManager::GetInstance());
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
	// -- Desctructible Walls --
	// -- Not desctructible Walls --
	
	//-->POWERUPS
	// -- 1 --
	// -- 2 --
	// -- 3 --

	//-->BOMB
	// -- Bomb --
	// -- Explosion Bomb --
}