#include "Bomb.h"
Bomb::Bomb() : position(0, 0, SPRITE_RES, SPRITE_RES), frame(0, SPRITE_RES, SPRITE_RES, SPRITE_RES), planted(false), flickering(false), exploded(false) {}
Bomb::~Bomb() {}

void Bomb::SetValues(VEC2 pos)
{
	frame.w = Renderer::GetInstance()->GetTextureSize(T_ITEMS).x / SPRITE_ITEMS_COLS;
	frame.h = Renderer::GetInstance()->GetTextureSize(T_ITEMS).y / SPRITE_ITEMS_ROWS;

		initCol = 0;
		lastCol = 0/*initCol + SPRITE_ITEMS_COLS*/;
		initRow = 1;
		lastRow = 1/*initRow + SPRITE_ITEMS_ROWS*/;

		/*initCol = 1;
		lastCol = initCol + SPRITE_EXPLOSION_COLS;
		initRow = 1;
		lastRow = initRow + SPRITE_EXPLOSION_ROWS;*/

	frame.x = frame.w * initCol;
	frame.y = frame.h * initRow;

	position.x = pos.x;
	position.y = pos.y;
}

void Bomb::SetBomb(VEC2 pos)
{
	bombTickingCheckpoint = clock();
	deltaBombTick = (clock() - bombTickingCheckpoint);
	deltaBombTick /= CLOCKS_PER_SEC;

	position.x = pos.x;
	position.y = pos.y;
}


void Bomb::Update()
{
	deltaBombTick = (clock() - bombTickingCheckpoint);
	deltaBombTick /= CLOCKS_PER_SEC;

	if (deltaBombTick < 2.f)
	{
		flickering = false;
		exploded = false;
	}
	else if (deltaBombTick < 3.f)
	{
		flickering = true;
		//state = EBombState::FLICKERING;
	}
	else if (deltaBombTick < 4.f)
	{
		exploded = true;
		//state = EBombState::EXPLODING;
	}
	else if (deltaBombTick > 4.f)
	{
		//state = EBombState::DISSAPEAR;
		planted = false;
		flickering = false;
		exploded = false;
	}
}