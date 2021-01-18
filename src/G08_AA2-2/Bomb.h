#pragma once

#include "Constants.h"
#include "InputManager.h"
#include "Renderer.h"

class Bomb
{
public:

	//enum class EBombState { NONE = -1, NORMAL, FLICKERING, EXPLODING, DISSAPEAR, COUNT };

	bool planted, flickering, exploded;
	//struct Explosion explosion[EXPLOSION_SPRITES] = {};

private:
	clock_t bombTickingCheckpoint;
	float deltaBombTick;

	RECT position;
	RECT frame;
	//EBombState state;

	int initCol, lastCol;
	int initRow, lastRow;

public:
	Bomb();
	~Bomb();

	inline const void SetPosition(RECT _position) { position = _position; };
	inline const RECT* GetPosition() { return &position; };
	inline const RECT* GetFrame() const { return &frame; };
	//inline const EBombState GetState() { return state; };
	//void SetState(EBombState _state) { state = _state; };
	 float GetDeltaBombTick() { return deltaBombTick; };
	void SetValues(VEC2);
	void SetBomb(VEC2);

	void Update();


};

class Explosion
{
public:
	enum class EExplosionDirection { NONE = -1, CENTER, MID_LEFT, MID_TOP, MID_RIGHT, MID_DOWN, FAR_LEFT, FAR_TOP, FAR_RIGHT, FAR_DOWN, COUNT };
	bool exploding, edgeExplodes;
private:
	EExplosionDirection dir;
	RECT position;
	RECT frame;

	int initCol = 0, lastCol = 3;
	int initRow = 0, lastRow = 6;

public:
	Explosion();
	~Explosion();
	
	inline const void SetPosition(RECT _position) { position = _position; };
	inline const RECT* GetPosition() { return &position; };
	inline const RECT* GetFrame() const { return &frame; };
	inline const EExplosionDirection GetExplosionType() { return dir; };
	void SetState(bool bombState) { exploding = bombState; };

	void SetValues(VEC2, int);
	void SetExplosionPosition(const RECT*, EExplosionDirection);
	void UpdateSprite(float);
};