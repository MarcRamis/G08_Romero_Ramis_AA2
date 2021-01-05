#include "PowerUp.h"

PowerUp::PowerUp() : position({ 0, 0, SPRITE_RES, SPRITE_RES }), frame({ 0,0,0,0 })
{
	//Renderer::GetInstance()->LoadTexture(T_ITEMS, P_ITEMS);
}

PowerUp::~PowerUp()
{

}

void PowerUp::SetValues(VEC2 pos, EPowerUpType _type)
{
	type = _type;
	frame.w = Renderer::GetInstance()->GetTextureSize(T_ITEMS).x / SPRITE_ITEMS_COLS;
	frame.h = Renderer::GetInstance()->GetTextureSize(T_ITEMS).y / SPRITE_ITEMS_ROWS;

	switch (_type)
	{
	case EPowerUpType::SKATES:
		initCol = 1;
		lastCol = initCol + SPRITE_ITEMS_COLS;
		initRow = 1;
		lastRow = initRow + SPRITE_ITEMS_ROWS;
		break;
	case EPowerUpType::HELMET:

		initCol = 2;
		lastCol = initCol + SPRITE_ITEMS_COLS;
		initRow = 1;
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