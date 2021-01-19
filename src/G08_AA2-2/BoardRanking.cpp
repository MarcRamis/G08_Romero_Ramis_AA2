#include "BoardRanking.h"

BoardRanking::BoardRanking()
{
	for (int i = 0; i < MAX_RANKING_PLAYERS; i++)
	{
		Board tmpBoard;
		tmpBoard.name = "NOPLAYER";
		tmpBoard.score = 0;
		board.push(tmpBoard);
	}
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
	for (int i = 0; i < MAX_RANKING_PLAYERS; i++)
	{
		Board tmpBoard;
		tmpBoard.name = "NOPLAYER";
		tmpBoard.score = 0;
		board.push(tmpBoard);
	}

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

void BoardRanking::LoadRanking()
{
	Renderer::GetInstance()->LoadFont({ F_GAMEOVER, P_TTF_GAMEOVER, 80 });

	for (int i = 0; i < MAX_RANKING_PLAYERS; i++)
	{
		tmpNames[i] = T_BOARDNAME + static_cast<char>(i);
		tmpScores[i] = T_BOARDSCORE + static_cast<char>(i);
		std::string name = board.top().name;
		std::string score = F2StrFormat(board.top().score, 0);
		VEC2 vTemp, vTemp2;

		if (i == 0)
		{
			vTemp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpNames[i], name, { 255,215,0,255 }, 0, 0 });
			vTemp2 = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpScores[i], score, { 255,215,0,255 }, 0, 0 });
		}
		else if (i == 1)
		{
			vTemp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpNames[i], name, { 192,192,192,255 }, 0, 0 });
			vTemp2 = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpScores[i], score, { 192,192,192,255 }, 0, 0 });
		}
		else if (i == 2)
		{
			vTemp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpNames[i], name, {205,127,50,255 }, 0, 0 });
			vTemp2 = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpScores[i], score, {205,127,50,255 }, 0, 0 });

		}
		else
		{
			vTemp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpNames[i], name, { 0,0,0,255 }, 0, 0 });
			vTemp2 = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { tmpScores[i], score, { 0,0,0,255 }, 0, 0 });
		}
		Renderer::GetInstance()->LoadRect(tmpNames[i], { SCREEN_WIDTH / 2 - vTemp.x / 2 - 150, SPRITE_HUD_HEIGHT + SPRITE_RES + 40 * (1 + i), vTemp.x, vTemp.y });
		Renderer::GetInstance()->LoadRect(tmpScores[i], { SCREEN_WIDTH / 2 - vTemp2.x / 2 + 150, SPRITE_HUD_HEIGHT + SPRITE_RES + 40 * (1 + i), vTemp2.x, vTemp2.y });

		board.pop();
	}

	
}

void BoardRanking::Draw()
{
	for (int i = 0; i < MAX_RANKING_PLAYERS; i++)
	{
		Renderer::GetInstance()->PushImage(tmpNames[i], tmpNames[i]);
		Renderer::GetInstance()->PushImage(tmpScores[i], tmpScores[i]);
	}
}