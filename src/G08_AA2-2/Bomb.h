#pragma once

#include "Constants.h"
#include "InputManager.h"
#include "Renderer.h"

class Bomb
{
public:

	enum class EBombState { NONE = -1, NORMAL, FLICKERING, EXPLODING, DISSAPEAR, COUNT };

	bool planted, flickering, exploded;

private:
	clock_t bombTickingCheckpoint;
	float deltaBombTick;

	RECT position;
	RECT frame;
	EBombState state;
	

	int initCol, lastCol;
	int initRow, lastRow;

public:
	Bomb();
	~Bomb();

	inline const void SetPosition(RECT _position) { position = _position; };
	inline const RECT* GetPosition() { return &position; };
	inline const RECT* GetFrame() const { return &frame; };
	inline const EBombState GetState() { return state; };
	void SetState(EBombState _state) { state = _state; };
	 float GetDeltaBombTick() { return deltaBombTick; };
	void SetValues(VEC2);
	void SetBomb(VEC2);

	void Update();


};

