#pragma once

#include "Constants.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Bomb.h"
#include "PowerUp.h"

class Player
{
public:
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };

	bool movementCheck, bombPlanted, colocateBomb;
	bool immunity;
	
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
	
	clock_t powerUpTick, powerUpInit;

public:
	Player();
	~Player();
	
	void Update(InputManager*);

	void UpdateCheck(InputManager*);

	void SetPlayerValues(VEC2 pos, EPlayerType _type);

	void ResetPos(VEC2);

	void AddScore(int _score) {  score += _score; };
	void RestLives(int _lives) {  lives -= _lives; };

	inline const EPlayerType GetPlayerType() { return type; };

	inline const RECT* GetPosition() { return &position; };
	inline const void SetPosition(RECT _position) { position = _position; };
	
	inline const RECT* GetFrame() const { return &frame; };
	inline const int GetScore() const { return score; };

	void SetScore(int _score) { score = _score; };

	int GetLives() { return lives; };
	void SetLive(int _lives) { lives = _lives; };
	
	void SetBuff(PowerUp::EPowerUpType);

	//Bomb GetBomb() { return bomb; };
	//void SetBomb(Bomb _bomb) { bomb = _bomb; };

private:
	void Move(InputManager*);
	void UpdateSprite();
};