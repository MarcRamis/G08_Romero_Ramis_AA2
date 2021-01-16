#include "BoardRanking.h"

BoardRanking::BoardRanking()
{
	rankingFileRead.open(P_RANKING, std::ios::in | std::ofstream::binary);
	if (!rankingFileRead)
	{
		std::cout << "File no exist" << std::endl;
	}
	else
	{
		Board tmpBg;

		size_t len;
		rankingFileRead.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		char* temp = new char[len + 1];
		rankingFileRead.read(temp, len);
		temp[len] = '\0';
		tmpBg.name = temp;
		delete[]temp;

		rankingFileRead.read(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

		rankingFileRead.close();

		board.push(tmpBg);
	}
}

BoardRanking::~BoardRanking()
{

}

BoardRanking* BoardRanking::boardRanking = nullptr;

void BoardRanking::AskName()
{
	Board tmpBg;

	std::cout << "Enter name: " << std::endl;
	std::cin >> tmpBg.name;
	
	// GET GREATER SCORE
	tmpBg.score = 300;		 // ESTA HARDCODEADO -->>> CAMBIAR

	board.push(tmpBg);

	std::ofstream rankingFileWrite(P_RANKING, std::ios::out | std::ofstream::binary);

	size_t len = tmpBg.name.size();
	rankingFileWrite.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	rankingFileWrite.write(tmpBg.name.c_str(), tmpBg.name.size());

	rankingFileWrite.write(reinterpret_cast<char*>(&tmpBg.score), sizeof(int));

	rankingFileWrite.close();
}

void BoardRanking::ShowRanking()
{

}