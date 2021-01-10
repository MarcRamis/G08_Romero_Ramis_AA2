#include "Wall.h"

Wall::Wall() : position({ 0, 0, SPRITE_RES, SPRITE_RES }), frame({ 0,0,0,0 }), destructed(false) {}

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
		destructed = false;
		initCol = 0;
		lastCol = initCol + SPRITE_ITEMS_COLS;
		initRow = 0;
		lastRow = initRow + SPRITE_ITEMS_ROWS;
		break;
	case true:
		destructed = false;
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

void Wall::Draw()
{
	if (!destructed)
	{
		Renderer::GetInstance()->PushSprite(T_ITEMS, GetFrame(), GetPosition());
	}
}