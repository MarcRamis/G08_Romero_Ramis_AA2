#pragma once
#include "Scene.h"

#include "BoardRanking.h"

class Ranking : public Scene
{
public:
	enum class ERankingState { ASKNAME, RUNNING};

private:

	//ERankingState rankingState;
	std::vector<BoardRanking::Board> board;

public:
	
	Ranking(/*ERankingState*/);
	~Ranking();
	
	void Update(InputManager& input);
	void Draw();
};