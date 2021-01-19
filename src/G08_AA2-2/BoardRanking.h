#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <queue>

#include "Constants.h"

class BoardRanking
{
public:
	struct Board
	{
		std::string name;
		int score;
	};

private:

	
	std::priority_queue<Board> board;

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
	void ReadRanking();
	friend bool operator<(const BoardRanking::Board& bg1, const BoardRanking::Board& bg2) { return bg1.score < bg2.score; }
	
	std::string LoadRankingName();
	int LoadRankingScore();
};