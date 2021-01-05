#include "Map.h"

Map::Map()
{
	grid.resize(MAP_ROWS);
	for (int i = 0; i < grid.size(); i++)
		grid.at(i).resize(MAP_COLS);

	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int j = 0; j < MAP_COLS; j++)
		{
			grid[i][j] = Cell::NONE;
		}
	}

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

			_player.push_back(tmpPlayer);
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
				grid[tmpWall.GetPosition()->y][tmpWall.GetPosition()->x] = Cell::WALLINDES;
				tmpWall.SetDestructible(false);
			}
			else if (sTmp == "true")
			{
				grid[tmpWall.GetPosition()->y][tmpWall.GetPosition()->x] = Cell::WALLDES;
				tmpWall.SetDestructible(true);
			}

			//std::cout << "\t\t\t" << pMap->name() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("destructible")->name() << ':' << tmpWall.GetDestructible() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("x")->name() << ':' << pMap->first_attribute("x")->value() << "\n";
			//std::cout << "\t\t\t\t" << pMap->first_attribute("y")->name() << ':' << pMap->first_attribute("y")->value() << "\n";

			wall.push_back(tmpWall);
		}
	}

	//for (int i = 0; i < MAP_ROWS; i++)
	//{
	//	for (int j = 0; j < MAP_COLS; j++)
	//	{
	//		int k = 0;
	//		while(k < wall.size())
	//		{
	//			if (i == wall.at(k).GetPosition()->x && j == wall.at(k).GetPosition()->y && !wall[k].GetDestructible())
	//			{
	//				grid.at(i).at(j) = Cell::WALLINDES;
	//			}
	//			if (i == wall.at(k).GetPosition()->x && j == wall.at(k).GetPosition()->y && wall[k].GetDestructible())
	//			{
	//				grid.at(i).at(j) = Cell::WALLDES;
	//			}
	//			k++;
	//		}
	//	}
	//}
}

Map::~Map() {}