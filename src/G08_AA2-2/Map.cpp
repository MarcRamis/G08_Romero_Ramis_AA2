#include "Map.h"

Map::Map(ELevelType _type)
{
	type = _type;
	std::string tmpLevelName = "";
	switch (type)
	{
	case ELevelType::LEVEL1:
		tmpLevelName = "Level1";
		break;
	case ELevelType::LEVEL2:
		tmpLevelName = "Level2";
		break;
	}

	// -- Read XML file --
	rapidxml::xml_document<> doc;
	std::ifstream file(P_CONFIG);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<>* pGame = doc.first_node();
	rapidxml::xml_node<>* pLevel = pGame->first_node(tmpLevelName.c_str());

	rapidxml::xml_node<>* pPlayers = pLevel->first_node("Players");
	for (rapidxml::xml_node<>* pPlayer = pPlayers->first_node(); pPlayer; pPlayer = pPlayer->next_sibling())
	{
		Player tmpPlayer;

		tmpPlayer.SetLive(atoi(pPlayer->first_attribute()->value()));
		tmpPlayer.SetPosition(RECT(atoi(pPlayer->first_node()->first_attribute("x")->value()), atoi(pPlayer->first_node()->first_attribute("y")->value())));

		player.push_back(tmpPlayer);
	}

	rapidxml::xml_node<>* pMaps = pLevel->first_node("Map");
	for (rapidxml::xml_node<>* pMap = pMaps->first_node(); pMap; pMap = pMap->next_sibling())
	{
		Wall tmpWall;

		tmpWall.SetPosition(RECT(atoi(pMap->first_attribute("x")->value()), atoi(pMap->first_attribute("y")->value())));

		std::string sTmp = pMap->first_attribute("destructible")->value();
		if (sTmp == "false")
		{
			tmpWall.destructible = false;
		}
		else if (sTmp == "true")
		{
			tmpWall.destructible = true;
		}

		wall.push_back(tmpWall);
	}
}

Map::~Map() 
{
	player.clear();
	wall.clear();
}
