#include "Wall.h"

Wall::Wall() : position({ 0, 0, SPRITE_RES, SPRITE_RES }), destructible(false)
{
	//Renderer::GetInstance()->LoadTexture(T_ITEMS, P_ITEMS);
	//Renderer::GetInstance()->LoadRect(T_ITEMS, { 0, 0, Renderer::GetInstance()->GetTextureSize(T_ITEMS).x, Renderer::GetInstance()->GetTextureSize(T_ITEMS).y });
}

Wall::~Wall()
{
	
}

void Wall::SetSprite(int textWidth, int textHeight, int nCol, int nRow)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
	
	initCol = 0;
	lastCol = initCol + 0;
	initRow = 0;
	lastRow = initRow + 0;
}