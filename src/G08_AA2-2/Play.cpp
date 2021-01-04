#include "Play.h"

Play::Play() 
{
	ReadMap();
	
	#pragma region HUD

	Renderer::GetInstance()->LoadFont({ F_TIMER_HUD, "../../res/ttf/game_over.ttf", 50 });

	// TIME
	// ":"
	VEC2 vMidTimerTemp = Renderer::GetInstance()->LoadTextureText(F_TIMER_HUD, { T_PLAY_MIDDLE_SIDE_TIMER, ":", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PLAY_MIDDLE_SIDE_TIMER, { SCREEN_WIDTH / 2 - vMidTimerTemp.x / 2, TEXT_HUD_VERTICAL_SPACING, vMidTimerTemp.x, vMidTimerTemp.y });
	//Minutes
	VEC2 vLeftTimerTemp = Renderer::GetInstance()->LoadTextureText(F_TIMER_HUD, { T_PLAY_LEFT_SIDE_TIMER, " ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PLAY_LEFT_SIDE_TIMER, { SCREEN_WIDTH / 2 - vLeftTimerTemp.x - vMidTimerTemp.x / 2, TEXT_HUD_VERTICAL_SPACING, vLeftTimerTemp.x, vLeftTimerTemp.y });
	//Seconds
	VEC2 vRightTimerTemp = Renderer::GetInstance()->LoadTextureText(F_TIMER_HUD, { T_PLAY_RIGHT_SIDE_TIMER, " ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PLAY_RIGHT_SIDE_TIMER, { SCREEN_WIDTH / 2 + vMidTimerTemp.x / 2, TEXT_HUD_VERTICAL_SPACING, vRightTimerTemp.x, vRightTimerTemp.y });


	Renderer::GetInstance()->LoadFont({ F_PLAYERS_HUD, "../../res/ttf/game_over.ttf", 80 });

	// PLAYER 1 SCORE_TEXT
	vP1SCTTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL1_SCORE_TEXT, "PL1: ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL1_SCORE_TEXT, { TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP1SCTTemp.x, vP1SCTTemp.y });

	// PLAYER 1 SCORE
	vP1SCTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL1_SCORE, " ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL1_SCORE, { vP1SCTTemp.x + TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP1SCTemp.x, vP1SCTemp.y });

	// PLAYER 2 SCORE
	vP2SCTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL2_SCORE, " ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL2_SCORE, { SCREEN_WIDTH - vP2SCTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP2SCTemp.x, vP2SCTemp.y });

	// PLAYER 2 SCORE_TEXT
	vP2SCTTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL2_SCORE_TEXT, "PL2: ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL2_SCORE_TEXT, { SCREEN_WIDTH - vP2SCTTemp.x - vP2SCTemp.x - TEXT_HUD_HORIZONTAL_SPACING, TEXT_HUD_VERTICAL_SPACING, vP2SCTTemp.x, vP2SCTTemp.y });

	Renderer::GetInstance()->LoadTexture(T_PLAYER1, "../../res/img/player1.png");
	// PLAYER 1 LIVES
	/*Renderer::GetInstance()->GetTextureSize(T_PLAYER1).x, Renderer::GetInstance()->GetTextureSize(T_PLAYER1).y, Player::EPlayerType::PL1
		vTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL1_LIVES, " ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL1_LIVES, { vP1SCTemp.x, 0, vTemp.x, vTemp.y });*/

	Renderer::GetInstance()->LoadTexture(T_PLAYER2, "../../res/img/player2.png");
	// PLAYER 2 LIVES
	/*vTemp = Renderer::GetInstance()->LoadTextureText(F_PLAYERS_HUD, { T_PL2_LIVES, " ", { 0,0,0,255 }, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_PL2_LIVES, { vP2SCTTemp, 0, vTemp.x, vTemp.y });
	PLAYER2_LIVES_WIDTH = vTemp.x;*/


#pragma endregion

	// AUDIO
	//Audio::GetInstance()->LoadAudio(S_GAME_THEME, P_GAME_THEME);
}

Play::~Play() {}

void Play::ReadMap()
{
	// -- Read XML file --
	rapidxml::xml_document<> doc;						// VARIABLE DECLARATION WHERE "doc" IS AN OBJECT FROM xml_document CLASS
	std::ifstream file("../../res/files/config.xml");	// VARIABLE FILE DECLARATION
	std::stringstream buffer;					// BUFFER DECLARATION BECAUSE STRINGSTREAM CAN CONTAIN MASSIVE INFORMATION OF THIS TYPE
	buffer << file.rdbuf();				// SAVE INFORMATION IN BUFFER WHERE "file.rdbuf()" IS A FUNCTION FROM "ifstream" 
	file.close();						// CLOSE FILE BECAUSE WE UPDATED EVERYTHING
	std::string content(buffer.str());	// VARIABLE DECLARATION AND SAVING BUFFER INSIDE. WE DO THIS BECAUSE "doc.parse()" function WORKS WITH STRING NOT STRINGSTREAM
	doc.parse<0>(&content[0]);			// LOOK AT FIRST ELEMENT					

	rapidxml::xml_node<>* pGame = doc.first_node();

	//std::cout << doc.first_node()->name() << "\n";
	for (rapidxml::xml_node<>* pLevel = pGame->first_node(); pLevel; pLevel = pLevel->next_sibling())
	{
		Map tmpMap;
		//std::cout << "\t" << pLevel->name() << "\n";
		//std::cout << "\t\t" << pLevel->first_node("Players")->name() << "\n";

		rapidxml::xml_node<>* pPlayers = pLevel->first_node("Players");
		for (rapidxml::xml_node<>* pPlayer = pPlayers->first_node(); pPlayer; pPlayer = pPlayer->next_sibling())
		{
			Player tmpPlayer;

			tmpPlayer.SetLive(atoi(pPlayer->first_attribute()->value()));
			tmpPlayer.SetPosition(RECT(atoi(pPlayer->first_node()->first_attribute("x")->value()), atoi(pPlayer->first_node()->first_attribute("y")->value())));

			/*std::cout << "\t\t\t" << pPlayer->name() << "\n";
			std::cout << "\t\t\t\t" << pPlayer->first_attribute()->name() << ':' << pPlayer->first_attribute("lives")->value() << "\n";
			std::cout << "\t\t\t\t" << pPlayer->first_node()->name() << "\n";
			std::cout << "\t\t\t\t\t" << pPlayer->first_node()->first_attribute("x")->name() << ':' << pPlayer->first_node()->first_attribute("x")->value() << "\n";
			std::cout << "\t\t\t\t\t" << pPlayer->first_node()->first_attribute("y")->name() << ':' << pPlayer->first_node()->first_attribute("y")->value() << "\n";
			*/
			tmpMap.GetPlayer()->push_back(tmpPlayer);
		}

		//std::cout << "\t\t" << pLevel->first_node("Map")->name() << "\n";

		rapidxml::xml_node<>* pMaps = pLevel->first_node("Map");
		for (rapidxml::xml_node<>* pMap = pMaps->first_node(); pMap; pMap = pMap->next_sibling())
		{
			Wall tmpWall;
			tmpWall.SetDestructible(atoi(pMap->first_attribute("destructible")->value()));
			tmpWall.SetPosition(RECT(atoi(pMap->first_attribute("x")->value()), atoi(pMap->first_attribute("y")->value())));

			//std::cout << "\t\t\t" << pMap->name() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("destructible")->name() << ':' << pMap->first_attribute("destructible")->value() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("x")->name() << ':' << pMap->first_attribute("x")->value() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("y")->name() << ':' << pMap->first_attribute("y")->value() << "\n";
			
			tmpMap.GetWall()->push_back(tmpWall);
		}
		
		levels.push_back(tmpMap);
	}
}

void Play::Draw() 
{
	// -- Background --
	Renderer::GetInstance()->PushImage(T_BG, T_BG);
	//Renderer::GetInstance()->PushImage(T_ITEMS, T_ITEMS);

	// -- Player 1 -- 
	Renderer::GetInstance()->PushImage(T_PL1_SCORE_TEXT, T_PL1_SCORE_TEXT);
	Renderer::GetInstance()->PushImage(T_PL1_SCORE, T_PL1_SCORE);
	//Renderer::GetInstance()->PushSprite(T_PL1_LIVES, T_PL1_LIVES);

	// -- Timer --
	Renderer::GetInstance()->PushImage(T_PLAY_LEFT_SIDE_TIMER, T_PLAY_LEFT_SIDE_TIMER);
	Renderer::GetInstance()->PushImage(T_PLAY_MIDDLE_SIDE_TIMER, T_PLAY_MIDDLE_SIDE_TIMER);
	Renderer::GetInstance()->PushImage(T_PLAY_RIGHT_SIDE_TIMER, T_PLAY_RIGHT_SIDE_TIMER);

	// -- Player 2 --
	Renderer::GetInstance()->PushImage(T_PL2_SCORE_TEXT, T_PL2_SCORE_TEXT);
	Renderer::GetInstance()->PushImage(T_PL2_SCORE, T_PL2_SCORE);
	//Renderer::GetInstance()->PushImage(T_PL2_LIVES, T_PL2_LIVES);

	// -- LEVEL 1--
	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int j = 0; j < MAP_COLS; j++)
		{
			//if (levels.at(j).IsPlayer({ i,j }, j)) {}
			//Renderer::GetInstance()->PushImage()
			//if (levels.at(0).IsNotDestructibleWall())
		}
	}
}