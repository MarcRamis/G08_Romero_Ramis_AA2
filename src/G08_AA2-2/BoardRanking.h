#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <queue>

#include "Constants.h"

#include "Ranking.h"

class BoardRanking
{
public:

private:
	struct Board
	{
		std::string name;
		int score;
	};
	std::priority_queue<Board> board;
	std::vector<Board> tmpBoard;
	std::string tmpNames[MAX_RANKING_PLAYERS];
	std::string tmpScores[MAX_RANKING_PLAYERS];

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
	
	void LoadRanking();
	void Draw();
};