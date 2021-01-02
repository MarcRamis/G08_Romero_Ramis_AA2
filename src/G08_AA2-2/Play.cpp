#include "Play.h"

Play::Play() 
{
	ReadMap();
	
	// AUDIO
	Audio::GetInstance()->LoadAudio(S_GAME_THEME, P_GAME_THEME);
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

	// -- LEVEL 1--
	//for (int i = 0; i < levels.at(0).GetGrid()->size(); i++)
	//{
	//	for (int j = 0; j < levels.at(0).GetGrid()->size(); j++)
	//	{
	//		//Renderer::GetInstance()->PushImage()
	//		//if (levels.at(0).IsNotDestructibleWall())
	//	}
	//	std::cout << std::endl;
	//}
}