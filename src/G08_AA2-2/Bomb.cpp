#include "Bomb.h"
Bomb::Bomb() : position(0, 0, SPRITE_RES, SPRITE_RES),
frame(0, SPRITE_RES, SPRITE_RES, SPRITE_RES),
planted(false),
flickering(false),
exploded(false) {}
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
Explosion::Explosion() : position(0, 0, SPRITE_RES, SPRITE_RES),
frame(0, SPRITE_RES, SPRITE_RES, SPRITE_RES),
exploding(false) {}
Explosion::~Explosion() {}

void Explosion::SetValues(VEC2 pos, int direction)
{
	frame.w = Renderer::GetInstance()->GetTextureSize(T_EXPLOSION).x / (SPRITE_EXPLOSION_COLS + 1);
	frame.h = Renderer::GetInstance()->GetTextureSize(T_EXPLOSION).y / (SPRITE_EXPLOSION_ROWS + 1);

	switch (direction)
	{
	case 0:
		dir = EExplosionDirection::CENTER;
		break;
	case 1:
		dir = EExplosionDirection::MID_LEFT;
		break;
	case 2:
		dir = EExplosionDirection::MID_TOP;
		break;
	case 3:
		dir = EExplosionDirection::MID_RIGHT;
		break;
	case 4:
		dir = EExplosionDirection::MID_DOWN;
		break;
	case 5:
		dir = EExplosionDirection::FAR_LEFT;
		break;
	case 6:
		dir = EExplosionDirection::FAR_TOP;
		break;
	case 7:
		dir = EExplosionDirection::FAR_RIGHT;
		break;
	case 8:
		dir = EExplosionDirection::FAR_DOWN;
		break;
	default:
		break;
	}

	initCol = 0;
	lastCol = initCol + SPRITE_EXPLOSION_COLS;
	initRow = 0;
	lastRow = initRow + SPRITE_EXPLOSION_ROWS;

	frame.x = frame.w * initCol;
	frame.y = frame.h * initRow;

	position.x = pos.x;
	position.y = pos.y;
}

void Explosion::SetExplosionPosition(const RECT* bombPos, EExplosionDirection direction)
{
	switch (direction)
	{
	case Explosion::EExplosionDirection::CENTER:
		position.x = bombPos->x;
		position.y = bombPos->y;
		break;
	case Explosion::EExplosionDirection::MID_LEFT:
		position.x = bombPos->x - SPRITE_RES;
		position.y = bombPos->y;
		break;
	case Explosion::EExplosionDirection::MID_TOP:
		position.x = bombPos->x;
		position.y = bombPos->y - SPRITE_RES;
		break;
	case Explosion::EExplosionDirection::MID_RIGHT:
		position.x = bombPos->x + SPRITE_RES;
		position.y = bombPos->y;
		break;
	case Explosion::EExplosionDirection::MID_DOWN:
		position.x = bombPos->x;
		position.y = bombPos->y + SPRITE_RES;
		break;
	case Explosion::EExplosionDirection::FAR_LEFT:
		position.x = bombPos->x - SPRITE_RES * 2;
		position.y = bombPos->y;
		break;
	case Explosion::EExplosionDirection::FAR_TOP:
		position.x = bombPos->x;
		position.y = bombPos->y - SPRITE_RES * 2;
		break;
	case Explosion::EExplosionDirection::FAR_RIGHT:
		position.x = bombPos->x + SPRITE_RES * 2;
		position.y = bombPos->y;
		break;
	case Explosion::EExplosionDirection::FAR_DOWN:
		position.x = bombPos->x;
		position.y = bombPos->y + SPRITE_RES * 2;
		break;
	default:
		break;
	}
}

void Explosion::UpdateSprite(float time)
{
	/*if (dir != EDirection::NONE) frameCount++;

	if (FPS / frameCount <= 4)
	{
		frameCount = 0;
		frame.x += frame.w;
		if (frame.x >= frame.w * lastCol)
			frame.x = frame.w * initCol;
	}*/
	if ((time > 3.f && time <= 3.1f) || (time > 3.9f && time < 4.f))
	{
		frame.x = 0 * SPRITE_RES;
	}
	else if ((time > 3.1f && time <= 3.2f) || (time > 3.8f && time <= 3.9f))
	{
		frame.x = 1 * SPRITE_RES;
	}
	else if ((time > 3.2f && time <= 3.3f) || (time > 3.7f && time <= 3.8f))
	{
		frame.x = 2 * SPRITE_RES;
	}
	else if (time > 3.3f && time <= 3.7f)
	{
		frame.x = 3 * SPRITE_RES;
	}

	switch (dir)
	{
	case EExplosionDirection::CENTER:
		frame.y = (initRow + 0) * frame.h;
		break;
	case EExplosionDirection::MID_LEFT:
	case EExplosionDirection::MID_RIGHT:
		frame.y = (initRow + 5) * frame.h;
		break;
	case EExplosionDirection::MID_TOP:
	case EExplosionDirection::MID_DOWN:
		frame.y = (initRow + 6) * frame.h;
		break;
	case EExplosionDirection::FAR_LEFT:
		frame.y = (initRow + 1) * frame.h;
		break;
	case EExplosionDirection::FAR_TOP:
		frame.y = (initRow + 3) * frame.h;
		break;
	case EExplosionDirection::FAR_RIGHT:
		frame.y = (initRow + 2) * frame.h;
		break;
	case EExplosionDirection::FAR_DOWN:
		frame.y = (initRow + 4) * frame.h;
		break;
	default:
		break;
	}
}