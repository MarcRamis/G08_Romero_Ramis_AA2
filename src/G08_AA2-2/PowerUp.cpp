#include "PowerUp.h"

PowerUp::PowerUp() : position({ 0, 0, SPRITE_RES, SPRITE_RES }), frame({ 0,0,0,0 }), isActive(false)
{
	//Renderer::GetInstance()->LoadTexture(T_ITEMS, P_ITEMS);
}

PowerUp::~PowerUp()
{

}

void PowerUp::SetValues(VEC2 pos)
{
    frame.w = Renderer::GetInstance()->GetTextureSize(T_ITEMS).x / SPRITE_ITEMS_COLS;
    frame.h = Renderer::GetInstance()->GetTextureSize(T_ITEMS).y / SPRITE_ITEMS_ROWS;

    position.x = pos.x;
    position.y = pos.y;

    isActive = true;

    EPowerUpType _type;
    int rnd = rand() % 100;

    if (rnd < 100)
    {
        int rnd2 = rand() % 100;

        if (rnd2 < 50) {
            _type = EPowerUpType::SKATES;
        }
        else if (rnd < 100) {
            _type = EPowerUpType::HELMET;
        }
    }

    type = _type;

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
}

void PowerUp::Draw()
{
    if (isActive)
    {
        Renderer::GetInstance()->PushSprite(T_ITEMS, GetFrame(), GetPosition());
    }
}