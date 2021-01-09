#include "Bomb.h"
Bomb::Bomb() : position(0, 0, SPRITE_RES, SPRITE_RES), frame(0, SPRITE_RES, SPRITE_RES, SPRITE_RES), planted(false) {}
Bomb::~Bomb() {}

void Bomb::SetValues(VEC2 pos, EBombState _state)
{
	state = _state;
	frame.w = Renderer::GetInstance()->GetTextureSize(T_ITEMS).x / SPRITE_ITEMS_COLS;
	frame.h = Renderer::GetInstance()->GetTextureSize(T_ITEMS).y / SPRITE_ITEMS_ROWS;

	switch (_state)
	{
	case EBombState::NORMAL:
	case EBombState::FLICKERING:
		initCol = 0;
		lastCol = 0/*initCol + SPRITE_ITEMS_COLS*/;
		initRow = 1;
		lastRow = 1/*initRow + SPRITE_ITEMS_ROWS*/;
		break;
	case EBombState::EXPLODING:
		initCol = 1;
		lastCol = initCol + SPRITE_EXPLOSION_COLS;
		initRow = 1;
		lastRow = initRow + SPRITE_EXPLOSION_ROWS;
		break;
	default:
		break;
	}

	frame.x = frame.w * initCol;
	frame.y = frame.h * initRow;

	position.x = pos.x;
	position.y = pos.y;

	bombTickingCheckpoint = clock();
	deltaBombTick = bombTickingCheckpoint;
	deltaBombTick /= CLOCKS_PER_SEC;
}

void Bomb::Update(EBombState state)
{
	deltaBombTick = (clock() - bombTickingCheckpoint);
	deltaBombTick /= CLOCKS_PER_SEC;

	if (deltaBombTick < 2.f)
	{
		state = EBombState::NORMAL;
	}
	else if (deltaBombTick < 3.f)
	{
		state = EBombState::FLICKERING;
	}
	else if (deltaBombTick < 4.f)
	{
		state = EBombState::EXPLODING;
	}

}