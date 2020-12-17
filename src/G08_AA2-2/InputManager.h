#pragma once

#include <time.h>

#include "Types.h"
#include <iostream>

enum class InputKeys {
	NONE, LEFT, RIGHT, UP, DOWN, SPACE, A, D, W, S, P, ESC, MOUSE_LEFT, MOUSE_RIGHT, QUIT, COUNT
};

class InputManager {

private:
	InputManager();
	~InputManager();

	static InputManager* input;

	bool keyboardPressed[(int)InputKeys::COUNT] = {};
	bool keyboardKeyDown[(int)InputKeys::COUNT] = {};
	VEC2 mouseCoords;
	VEC2 screenSize;

	// Timecontrol
	clock_t lastTime = clock();
	float deltaTime = 0.f;

public:

	static InputManager* GetInstance()
	{
		if (input == nullptr) { input = new InputManager; }
		return input;
	};

	void UpdateDeltaTime();

	const float* GetDeltaTime() const;

	void SetScreenSize(VEC2 sSize);
	const VEC2* GetScreenSize() const;

	VEC2 GetMouseCoords();
	void SetMouseCoords(VEC2 coords);
	void SetMouseCoords(int x, int y);

	bool isPressed(InputKeys key);

	bool JustPressed(InputKeys key);

	void SetKeyValue(InputKeys key, bool value);

	void SetFalseKeyDown();
};

enum class EDirection { NONE = -1, LEFT, RIGHT, DOWN, UP, COUNT };