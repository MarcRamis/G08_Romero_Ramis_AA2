#include "BoardRanking.h"

BoardRanking::BoardRanking()
{
}
BoardRanking::~BoardRanking()
{
	while (!board.empty()) {
		board.pop();
	}
}

BoardRanking* BoardRanking::boardRanking = nullptr;

void BoardRanking::ReadRanking()
{
	std::ifstream rankingFileRead(P_RANKING, std::ios::in | std::ios::binary);
	if (!rankingFileRead)
	{
		std::cout << "File no exist" << std::endl;
	}
	else
	{
		Board tmpBg;
		std::vector<Board> vtmpBg;


		while (rankingFileRead)
		{
			size_t len;
			rankingFileRead.read(reinterpret_cast<char*>(&len), sizeof(size_t));
			char* temp = new char[len + 1];
			rankingFileRead.read(temp, len);
			temp[len] = '\0';
			tmpBg.name = temp;
			delete[] temp;

			rankingFileRead.read(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

			vtmpBg.push_back(tmpBg);
		}

		rankingFileRead.close();

		for (int i = 0; i < vtmpBg.size() - 1; i++)
		{
			board.push(vtmpBg.at(i));
		}
	}

}

void BoardRanking::AskName(const int &scPl1, const int &scPl2)
{
	Board tmpBg;

	std::cout << "Enter name: " << std::endl;
	std::cin >> tmpBg.name;
	
	// GET GREATER SCORE
	if (scPl1 > scPl2) tmpBg.score = scPl1;
	else tmpBg.score = scPl2;

	std::ofstream rankingFileWrite(P_RANKING, std::ios::app | std::ios::out | std::ios::binary);

	rankingFileWrite.write(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));
	size_t len = tmpBg.name.size();
	rankingFileWrite.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	rankingFileWrite.write(tmpBg.name.c_str(), tmpBg.name.size());

	rankingFileWrite.close();

	board.push(tmpBg);
}
void BoardRanking::AskName(const int& scPlWinner)
{
	Board tmpBg;

	std::cout << "Enter name: " << std::endl;
	std::cin >> tmpBg.name;

	tmpBg.score = scPlWinner;

	std::ofstream rankingFileWrite(P_RANKING, std::ios::app | std::ios::out | std::ios::binary);
	
	size_t len = tmpBg.name.size();
	rankingFileWrite.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	rankingFileWrite.write(tmpBg.name.c_str(), tmpBg.name.size());
	rankingFileWrite.write(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

	rankingFileWrite.close();

	board.push(tmpBg);
}

std::string BoardRanking::LoadRankingName() {

	std::string tmpName;
	std::cout << "Name: " << board.top().name << " - Score: " << board.top().score << std::endl;
	tmpName = board.top().name;

	board.pop();

	return tmpName;
}
int BoardRanking::LoadRankingScore() {
	return 0;
}