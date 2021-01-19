#include "BoardRanking.h"

BoardRanking::BoardRanking()
{
	std::ifstream rankingFileRead(P_RANKING, std::ios::in | std::ifstream::binary);
	if (!rankingFileRead)
	{
		std::cout << "File no exist" << std::endl;
	}
	else
	{
		Board tmpBg;

		while (!rankingFileRead.eof())
		{
			size_t len;
			rankingFileRead.read(reinterpret_cast<char*>(&len), sizeof(size_t));
			char* temp = new char[len + 1];
			rankingFileRead.read(temp, len);
			temp[len] = '\0';
			tmpBg.name = temp;
			delete[]temp;

			rankingFileRead.read(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

			board.push(tmpBg);
			std::cout << "Name: " << board.top().name << "\nScore: " << board.top().score << std::endl;
		}

		rankingFileRead.close();
	}
}

BoardRanking::~BoardRanking()
{
	while (!board.empty()) {
		board.pop();
	}
}

BoardRanking* BoardRanking::boardRanking = nullptr;

void BoardRanking::AskName(const int &scPl1, const int &scPl2)
{
	Board tmpBg;

	std::cout << "Enter name: " << std::endl;
	std::cin >> tmpBg.name;
	
	// GET GREATER SCORE
	if (scPl1 > scPl2) tmpBg.score = scPl1;
	else tmpBg.score = scPl2;

	std::cout << "Name: " << tmpBg.name << "\nScore1: " << scPl1 << "\nScore2: " << scPl2 << std::endl;

	std::ofstream rankingFileWrite(P_RANKING, std::ios::app | std::ios::out | std::ofstream::binary);

	size_t len = tmpBg.name.size();
	rankingFileWrite.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	rankingFileWrite.write(tmpBg.name.c_str(), tmpBg.name.size());

	rankingFileWrite.write(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

	rankingFileWrite.close();
}

void BoardRanking::AskName(const int& scPlWinner)
{
	Board tmpBg;

	std::cout << "Enter name: " << std::endl;
	std::cin >> tmpBg.name;

	tmpBg.score = scPlWinner;
	
	std::cout << "Name: " << tmpBg.name << "\nScore: " << scPlWinner << std::endl;
	
	std::ofstream rankingFileWrite(P_RANKING, std::ios::app | std::ios::out | std::ofstream::binary);

	size_t len = tmpBg.name.size();
	rankingFileWrite.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	rankingFileWrite.write(tmpBg.name.c_str(), tmpBg.name.size());
	rankingFileWrite.write(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

	rankingFileWrite.close();
}

void BoardRanking::ShowRanking()
{

}