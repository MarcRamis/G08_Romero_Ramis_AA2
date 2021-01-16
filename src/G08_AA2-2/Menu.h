#pragma once
#include "Scene.h"
class Menu : public Scene
{
private:

public:
	Menu();
	~Menu();

	void Update(InputManager& input);
	void Draw();
};