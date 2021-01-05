#include "Player.h"

Player::Player() : position({ 1, 1, SPRITE_RES, SPRITE_RES}), frame({ 0, 0, 20, 20 }), type(EPlayerType::NONE), speed(1.f), score(0) 
{
	//Renderer::GetInstance()->LoadTexture(T_PLAYERS, P_PLAYER1);
	//Renderer::GetInstance()->LoadTexture(T_PLAYERS, P_PLAYER2);
}

Player::~Player()
{
	
}

void Player::Update(InputManager* input)
{
	Move(input);
	UpdateSprite();
}

bool Player::Move(InputManager* input)
{
	dir = EDirection::NONE;
	VEC2 newPosition = { position.x, position.y };

	switch (type)
	{
	case Player::EPlayerType::PL1:
		if (input->isPressed(InputKeys::W)) {
			newPosition.y -= speed; dir = EDirection::UP;
		}
		if (input->isPressed(InputKeys::S)) {
			newPosition.y += speed; dir = EDirection::DOWN;
		}
		if (input->isPressed(InputKeys::A)) {
			newPosition.x -= speed; dir = EDirection::LEFT;
		}
		if (input->isPressed(InputKeys::D)) {
			newPosition.x += speed; dir = EDirection::RIGHT;
		}
		break;
	case Player::EPlayerType::PL2:
		if (input->isPressed(InputKeys::UP)) {
			newPosition.y -= speed; dir = EDirection::UP;
		}
		if (input->isPressed(InputKeys::DOWN)) {
			newPosition.y += speed; dir = EDirection::DOWN;
		}
		if (input->isPressed(InputKeys::LEFT)) {
			newPosition.x -= speed; dir = EDirection::LEFT;
		}
		if (input->isPressed(InputKeys::RIGHT)) {
			newPosition.x += speed; dir = EDirection::RIGHT;
		}
		break;
	default:
		break;
	}

	// Check player collisions
	//if (newPosition.x > input->GetScreenSize()->x - frame.w || newPosition.x < 0) newPosition.x = position.x;
	//if (newPosition.y > input->GetScreenSize()->y - frame.h || newPosition.y < 0 + input->GetScreenSize()->y / 4) newPosition.y = position.y;

	//Update Positions
	if (newPosition.x != position.x || newPosition.y != position.y) {
		position.x = newPosition.x;
		position.y = newPosition.y;
		return true;
	}

	return false;
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
void Player::SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, VEC2 pos, EPlayerType _type)
{
	type = _type;

	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	initCol = 0;
	lastCol = initCol + 3;
	initRow = 0;
	lastRow = initRow + 4;
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