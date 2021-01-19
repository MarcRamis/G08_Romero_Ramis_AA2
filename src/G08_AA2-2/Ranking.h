#pragma once
#include "Scene.h"

#include "BoardRanking.h"
#include "Utils.h"

class Ranking : public Scene
{
public:
	enum class ERankingState { ASKNAME, RUNNING};

private:

	

public:
	
	Ranking();
	~Ranking();
	
	void Update(InputManager& input);
	void Draw();
};