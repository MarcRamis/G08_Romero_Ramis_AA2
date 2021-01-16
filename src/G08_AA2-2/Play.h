#pragma once

#include "Scene.h"
#include "Level.h"

class Play : public Scene
{
private:

	Level *level;
	
	//float timeDown;
	
public:
	Play(Level::ELevelType);
	~Play();
	
	void Update(InputManager& input);
	void Draw();
};