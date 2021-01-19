#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <queue>

#include "Constants.h"

class BoardRanking
{
private:
	
	struct Board
	{
		std::string name;
		int score;
	};

	std::priority_queue<Board> board;
	
	//std::ofstream rankingFileWrite;
	//std::ifstream rankingFileRead;

	static BoardRanking* boardRanking;

public:
	BoardRanking();
	~BoardRanking();


	static BoardRanking* GetInstance()
	{
		if (boardRanking == nullptr) { boardRanking = new BoardRanking; }
		return boardRanking;
	};

	void AskName(const int& scPl1, const int& scPl2s);
	void AskName(const int& scPlWinner);
	void ShowRanking();
	friend bool operator<(const BoardRanking::Board& bg1, const BoardRanking::Board& bg2) { return bg1.score < bg2.score; }
};