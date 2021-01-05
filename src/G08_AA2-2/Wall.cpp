#include "Wall.h"

Wall::Wall() : position({ 0, 0, SPRITE_RES, SPRITE_RES }), destructible(false)
{
	Renderer::GetInstance()->LoadTexture(T_ITEMS, P_ITEMS);
}

Wall::~Wall()
{
	
}

void Wall::SetValues(VEC2 pos, bool _destr)
{
	frame.w = Renderer::GetInstance()->GetTextureSize(T_ITEMS).x / SPRITE_ITEMS_COLS;
	frame.h = Renderer::GetInstance()->GetTextureSize(T_ITEMS).y / SPRITE_ITEMS_ROWS;

	switch (_destr)
	{
	case false:
		initCol = 0;
		lastCol = initCol + SPRITE_ITEMS_COLS;
		initRow = 0;
		lastRow = initRow + SPRITE_ITEMS_ROWS;
		break;
	case true:

		initCol = 1;
		lastCol = initCol + SPRITE_ITEMS_COLS;
		initRow = 0;
		lastRow = initRow + SPRITE_ITEMS_ROWS;
		break;

	default:
		break;
	}

	frame.x = frame.w * initCol;
	frame.y = frame.h * initRow;

	position.x = pos.x;
	position.y = pos.y;
}