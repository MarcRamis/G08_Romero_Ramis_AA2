#pragma once

#include "Constants.h"
#include "InputManager.h"
#include "Renderer.h"

class Player
{
public:
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };

	bool movementCheck;

private:
	RECT position;
	RECT frame;
	EPlayerType type;
	EDirection dir = EDirection::NONE;
	VEC2 newPosition;
	VEC2 lastPosition;

	int initCol, lastCol;
	int initRow, lastRow;
	float frameCount = 0;
	
	float speed;
	int score;

	int lives;

public:
	Player();
	~Player();
	
	void Update(InputManager*);

	void secondUpdate(InputManager*);

	void SetPlayerValues(VEC2 pos, EPlayerType _type);

	void Reset();

	int AddScore() { return score++; };

	inline const EPlayerType GetPlayerType() { return type; };

	inline const RECT* GetPosition() { return &position; };
	inline const void SetPosition(RECT _position) { position = _position; };
	
	inline const RECT* GetFrame() const { return &frame; };
	inline const int GetScore() const { return score; };

	void SetScore(int _score) { score = _score; };

	int GetLives() { return lives; };
	void SetLive(int _lives) { lives = _lives; };

private:
	void Move(InputManager*);
	void UpdateSprite();
};