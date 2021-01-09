#include "Player.h"

Player::Player() : position({ 1, 1, SPRITE_RES, SPRITE_RES}), frame({ 0, 0, 20, 20 }), type(EPlayerType::NONE), speed(1.f), score(0), movementCheck(true), bombPlanted(false), colocateBomb(false) {}

Player::~Player()
{
	
}

void Player::Update(InputManager* input)
{
	Move(input);
	UpdateSprite();
}

void Player::Move(InputManager* input)
{
	dir = EDirection::NONE;
	newPosition = { position.x, position.y };
	lastPosition = { position.x, position.y };

	switch (type)
	{
	case Player::EPlayerType::PL1:
		if (input->isPressed(InputKeys::W)) {
			newPosition.y -= SPRITE_RES; dir = EDirection::UP;
		}
		else if (input->isPressed(InputKeys::S)) {
			newPosition.y += SPRITE_RES; dir = EDirection::DOWN;
		}
		else if (input->isPressed(InputKeys::A)) {
			newPosition.x -= SPRITE_RES; dir = EDirection::LEFT;
		}
		else if (input->isPressed(InputKeys::D)) {
			newPosition.x += SPRITE_RES; dir = EDirection::RIGHT;
		}
		if (input->JustPressed(InputKeys::SPACE) && !bombPlanted)
		{
			colocateBomb = true;
		}
		break;
	case Player::EPlayerType::PL2:
		if (input->isPressed(InputKeys::UP)) {
			newPosition.y -= SPRITE_RES; dir = EDirection::UP;
		}
		else if (input->isPressed(InputKeys::DOWN)) {
			newPosition.y += SPRITE_RES; dir = EDirection::DOWN;
		}
		else if (input->isPressed(InputKeys::LEFT)) {
			newPosition.x -= SPRITE_RES; dir = EDirection::LEFT;
		}
		else if (input->isPressed(InputKeys::RIGHT)) {
			newPosition.x += SPRITE_RES; dir = EDirection::RIGHT;
		}
		if (input->JustPressed(InputKeys::RIGHT_CTRL) && !bombPlanted)
		{
			colocateBomb = true;
		}
		break;
	default:
		break;
	}
	if (input->itsFrameTime)
	{
		position.x = newPosition.x;
		position.y = newPosition.y;
	}
}

void Player::UpdateCheck(InputManager* input)
{
	// Check player collisions
	if (newPosition.x > (input->GetScreenSize()->x - frame.w) - SPRITE_RES || newPosition.x < SPRITE_RES) newPosition.x = lastPosition.x;
	if (newPosition.y > (input->GetScreenSize()->y - frame.h) - SPRITE_RES || newPosition.y < SPRITE_RES + SPRITE_HUD_HEIGHT) newPosition.y = lastPosition.y;

	if (!movementCheck)
	{
		position.x = lastPosition.x;
		position.y = lastPosition.y;
		newPosition.x = position.x;
		newPosition.y = position.y;
		movementCheck = !movementCheck;
	}
	//Update Positions
	else if ((newPosition.x != position.x || newPosition.y != position.y) && input->itsFrameTime) {
		position.x = newPosition.x;
		position.y = newPosition.y;
	}
}

void Player::UpdateSprite()
{
	if (dir != EDirection::NONE) frameCount++;

	if (FPS / frameCount <= 4)
	{
		frameCount = 0;
		frame.x += frame.w;
		if (frame.x >= frame.w * lastCol)
			frame.x = frame.w * initCol;
	}

	switch (dir)
	{
	case EDirection::DOWN:
		frame.y = (initRow + 2) * frame.h;
		break;
	case EDirection::LEFT:
		frame.y = (initRow + 1) * frame.h;
		break;
	case EDirection::RIGHT:
		frame.y = (initRow + 3) * frame.h;
		break;
	case EDirection::UP:
		frame.y = (initRow + 0) * frame.h;
		break;
	case EDirection::NONE:
		frame.y = (initRow + 2) * frame.h;
		break;
	default:
		frame.y = (initRow + 2) * frame.h;
		break;
	}
}
void Player::SetPlayerValues(VEC2 pos, EPlayerType _type)
{
	type = _type;

	switch (type)
	{
		case EPlayerType::PL1:
			frame.w = Renderer::GetInstance()->GetTextureSize(T_PLAYER1).x / SPRITE_PL_COLS;
			frame.h = Renderer::GetInstance()->GetTextureSize(T_PLAYER1).y / SPRITE_PL_ROWS;
			break;
		case EPlayerType::PL2:
			frame.w = Renderer::GetInstance()->GetTextureSize(T_PLAYER2).x / SPRITE_PL_COLS;
			frame.h = Renderer::GetInstance()->GetTextureSize(T_PLAYER2).y / SPRITE_PL_ROWS;
			break;
	}

	initCol = 0;
	lastCol = initCol + SPRITE_PL_COLS;
	initRow = 0;
	lastRow = initRow + SPRITE_PL_ROWS;
	
	frame.x = frame.w * initCol;
	frame.y = frame.h * initRow;

	position.x = pos.x;
	position.y = pos.y;
}

void Player::Reset()
{
	switch (type)
	{
	case Player::EPlayerType::PL1:
		position.x = 100;
		position.y = 250;
		speed = 1.f;
		score = 0;
		break;
	case Player::EPlayerType::PL2:
		position.x = 650;
		position.y = 250;
		speed = 1.f;
		score = 0;
		break;
	default:
		break;
	}
}