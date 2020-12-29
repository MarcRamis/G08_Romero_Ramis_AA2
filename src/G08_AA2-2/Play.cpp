#include "Play.h"

Play::Play() 
{
	// -- Read XML file --
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<>* pRoot = doc.first_node();

	for (rapidxml::xml_node<>* pEnemy = pRoot->first_node(); pEnemy; pEnemy = pEnemy->next_sibling())
	{

		Level level;
		level.GetPlayer()->at(0).SetLive((int)pEnemy->first_attribute("lives")->value())
		enemy.name = (std::string)pEnemy->first_attribute("name")->value();
		enemy.live = atoi(pEnemy->first_node("live")->value());			//conversion a la C
		enemy.damage = atoi(pEnemy->first_node("damage")->value());		//conversion a la C
		enemy.shield = atoi(pEnemy->first_node("shield")->value());		//conversion a la C
		enemy.hitSpeed = atof(pEnemy->first_node("hitSpeed")->value());	//conversion a la C
		enemy.experience = atoi(pEnemy->first_node("exp")->value());

		rapidxml::xml_node<>* pWeapons = pEnemy->first_node("weapons"); //necesario ya que se han agrupado las weapons
		for (rapidxml::xml_node<>* pWeapon = pWeapons->first_node("weapon"); pWeapon; pWeapon = pWeapon->next_sibling())
		{
			Weapon weapon;
			weapon.name = (std::string)pWeapon->first_attribute("name")->value();
			weapon.SetTypeFromString((std::string)pWeapon->first_node("type")->value());
			weapon.range = atoi(pWeapon->first_node("range")->value());
			enemy.weapons.push_back(weapon);
		};

		levels.push_back(level);

	};
}

Play::~Play() {}

void Play::Draw() {}