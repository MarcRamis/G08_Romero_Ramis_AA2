#pragma once
#include "Scene.h"

#include "BoardRanking.h"

class Ranking : public Scene
{
public:
	enum class ERankingState { ASKNAME, RUNNING};

private:

	ERankingState rankingState;

public:
	
	Ranking(ERankingState);
	~Ranking();
	
	void Update(InputManager& input);
	void Draw();
};