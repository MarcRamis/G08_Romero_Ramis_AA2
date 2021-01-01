#pragma once
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <sstream>

#include "Scene.h"
#include "Level.h"
#include "PowerUp.h"

class Play : public Scene
{
private:

	std::vector<Level> levels;

public:
	Play();
	~Play();

	void Draw();

private:
	void ReadMap();
};